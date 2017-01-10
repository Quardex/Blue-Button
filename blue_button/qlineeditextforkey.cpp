#include "qlineeditextforkey.h"
#include <QKeyEvent>

//Класс расширенного QLineEdit для окна настроек клавиши

QLineEditExtForKey::QLineEditExtForKey(QWidget *parent) :
    QLineEdit(parent)
{
}

void QLineEditExtForKey::keyPressEvent(QKeyEvent *event)
{
    buttonKey = event->nativeVirtualKey(); //сохраняет код клавиши в свойстве
    buttonName = event->text();
    setText(buttonName);
    if (event->nativeVirtualKey()==8) clear();
}
