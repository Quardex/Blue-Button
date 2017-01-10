#include "filemanager.h"
#include "controller.h"
#include <QFile>
#include <QTextStream>

extern Controller controller;

//Класс отвечает за формирование и загрузку файла с конфигурацией клавиш

bool FileManager::saved = false;
QString FileManager::error = "";
QString FileManager::filePath = "";

bool FileManager::save(QString filePath) //сохраняет в файл конфигурацию клавиш
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        error = "Не удалось открыть файл";
        return false;
    }
    QTextStream out(&file);
    for(int i=0;i<controller.getButtons().size();i++) {
        out << controller.getFileCodeFromButton(i) << "\n";
    }
    file.close();
    return true;
}

bool FileManager::load(QString filePath) //загружает из файла конфигурацию клавиш
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = "Не удалось открыть файл";
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        controller.getButtons().push_back(controller.getButtonFromFileCode(in.readLine()));
    }
    file.close();
    return true;
}

