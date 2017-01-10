#include "controller.h"
#include "connector.h"
#include "libloader.h"

extern Connector connector;
extern LibLoader libLoader;

//Класс отвечает за управление контроллером

std::deque<Button> &Controller::getButtons() //список клавиш
{
    return buttons;
}

QString Controller::getFileCodeFromButton(int index) //получить настройки определенной клавиши в формате файла конфигурации
{
    Button* button = &buttons[index];
    return button->name+"|"+
           QString::number(button->code)+"|"+
           QString::number(button->controller)+"|"+
           QString::number(button->motor)+"|"+
           QString::number(button->speed)+"|"+
           QString::number(button->direction?1:0);
}

Button Controller::getButtonFromFileCode(QString fileCode) //получить объект определенной клавиши с конфигурациями из файла
{
    Button newButton;
    QStringList params = fileCode.split("|");
    newButton.name = params.at(0);
    newButton.code = params.at(1).toInt();
    newButton.controller = params.at(2).toInt();
    newButton.motor = params.at(3).toInt();
    newButton.speed = params.at(4).toInt();
    newButton.direction = (params.at(5)=="1"?true:false);
    return newButton;
}

void Controller::exec(int buttonKey, bool pressed) //установить на контроллере состояние мотора в зависимости от конфигурации клавиши
{
    if (connector.getStarted()) {                  //если Трансфер Арея запущена
        for (int i=0;i<getButtons().size();i++) {  //перебираем список клавиш
            if (buttonKey==getButtons()[i].code) { //если текущая нажатая или отпущенная клавиша имеется в списке
                libLoader.setOutPwmValues(         //то посылаем конфигурацию мотора на контроллер, соответствующую этой клавиши и ее статусу нажатия (нажата или отпущена)
                    connector.fthdl,
                    getButtons()[i].controller,
                    getButtons()[i].motor * 2 + (getButtons()[i].direction ? 1 : 0),
                    getMemorySpeed(getButtons()[i], pressed)
                );
            }
        }
    }
}

int Controller::getMemorySpeed(Button button, bool pressed) //буффер нажатых клавиш
{                                                           //в случае, если несколько клавиш нацелены на один мотор с одинаковым направлением, но разной скоростью
    int speed;                                              //то создается очередь клавиш, при отпускании которых берется скорость последней в очереди
    int statusKey = button.controller * 8 + button.motor * 2 + (button.direction ? 1 : 0); //создаем ключ состояния, для группировки клавиш с одинаковыми конфигурациями
    if (pressed) {                                                                         //если клавиша нажимается
        memory[statusKey].append(button);                                                  //то добавляем ее в очередь, соответсвующую ключу состояния
        speed = button.speed;                                                              //т.к. теперь эта последняя нажатая клавиша, то ее скорость и устанавливается на мотор
    } else {                                                                               //если клавиша отжимается
        QList<Button>::iterator i = memory[statusKey].begin();                             //устанавливаем итератор определенной очереди в начало
        while (i != memory[statusKey].end()) {                                             //и идем до конца
            if ((*i).speed  == button.speed && (*i).code  == button.code) {                //в поисках кнопки, конфигурации которой (кроме скорости) равно отжатой
                i = memory[statusKey].erase(i);                                            //и удаляем из очереди, т.к. кнопка больше не нажата
                break;                                                                     //раз нашли, дальше смысла искать нет
            } else {
                ++i;
            }
        }
        if (!memory.contains(statusKey) || memory[statusKey].isEmpty()) {                  //если очередь текущего ключа состояния пуста или отсутсвует
            speed = 0;                                                                     //то это значит, что при отжатии текущей клавиши нужно остановить мотор, т.к. буффер пуст
        } else {                                                                           //если в очереди текущего ключа состояния имеются клавиши
            i = memory[statusKey].end();
            speed = (*--i).speed;                                                          //то просто берем скорость нажатой последней
        }
    }
    /*QList<Button>::const_iterator i = memory[statusKey].constBegin();
    while (i != memory[statusKey].constEnd()) {
      qDebug() << (*i).speed << ": "<< (*i).code << endl;
      ++i;
    }
    qDebug() << speed;*/
    return speed;
}
