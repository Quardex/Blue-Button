#include "formeditor.h"
#include "ui_formeditor.h"
#include <QMessageBox>

extern Controller controller;

//Класс окна найстройки клавиши

FormEditor::FormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditor)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
}

FormEditor::~FormEditor()
{
    delete ui;
}

void FormEditor::loadButton(int i) //загружает в форму конфигурацию клавиши
{
    if (i<0) {
        ui->lineEdit->setText("Введите...");
        ui->radioButton->setCheckable(false);
        ui->radioButton_2->setCheckable(false);
        ui->radioButton->setCheckable(true);
        ui->radioButton_2->setCheckable(true);
        ui->horizontalSlider->setValue(1);
    } else {
        ui->lineEdit->setText(controller.getButtons()[i].name);
        ui->lineEdit->buttonName = ui->lineEdit->text();
        ui->lineEdit->buttonKey = controller.getButtons()[i].code;
        ui->radioButton->setChecked(!controller.getButtons()[i].direction);
        ui->radioButton_2->setChecked(controller.getButtons()[i].direction);
        ui->horizontalSlider->setValue(controller.getButtons()[i].speed);
    }
    ui->lineEdit->setFocus();
    curButtonIndex = i;
}

void FormEditor::on_pushButton_2_clicked()
{
    close();
}

void FormEditor::on_pushButton_clicked() //сохраняет конфигурацию клавиши
{
    QString error = "";
    //if (ui->horizontalSlider->value()==0) error = "Скорость должна быть больше нуля";
    if (!ui->radioButton->isChecked()&&!ui->radioButton_2->isChecked()) error = "Выберите направление вращения";
    if (ui->lineEdit->text()==NULL||ui->lineEdit->text()=="Введите...") error = "Введите клавишу";
    if (error!="") {
        QMessageBox pmbx("Blue Button",
                        error,
                        QMessageBox::Warning,
                        QMessageBox::NoButton,
                        QMessageBox::NoButton,
                        QMessageBox::Ok | QMessageBox::Escape);
        pmbx.exec();
        return;
    } else {
        if (curButtonIndex<0) {
            Button newButton;
            newButton.code = ui->lineEdit->buttonKey;
            newButton.controller = ui->comboBox->currentIndex();
            newButton.direction = ui->radioButton_2->isChecked();
            newButton.motor = ui->comboBox_3->currentIndex();
            newButton.name = ui->lineEdit->buttonName;
            newButton.speed = ui->horizontalSlider->value();
            controller.getButtons().push_back(newButton);
        } else {
            controller.getButtons()[getCurButtonIndex()].code = ui->lineEdit->buttonKey;
            controller.getButtons()[getCurButtonIndex()].controller = ui->comboBox->currentIndex();
            controller.getButtons()[getCurButtonIndex()].direction = ui->radioButton_2->isChecked();
            controller.getButtons()[getCurButtonIndex()].motor = ui->comboBox_3->currentIndex();
            controller.getButtons()[getCurButtonIndex()].name = ui->lineEdit->buttonName;
            controller.getButtons()[getCurButtonIndex()].speed = ui->horizontalSlider->value();
        }
        close();
    }
    emit buttonsChanged();
}

void FormEditor::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
}

void FormEditor::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
}
