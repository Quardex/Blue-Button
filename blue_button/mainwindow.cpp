#include "mainwindow.h"
#include "formabout.h"
#include "connector.h"
#include "filemanager.h"
#include "ui_mainwindow.h"
#include "libloader.h"
#include "QStandardItemModel"
#include "QDesktopServices"
#include "QUrl"
#include <QFileDialog>
#include <QMessageBox>
#include "adds.h"
#include "libloader.h"
#include <QKeyEvent>

extern QString version;
extern Controller controller;
extern Connector connector;
extern LibLoader libLoader;

//Класс главного окна

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    formAbout = NULL;
    formEditor = new FormEditor();
    connect(formEditor,SIGNAL(buttonsChanged()),this,SLOT(buttonsChanged()));
    ui->pushButton->setEnabled(libLoader.loaded());
    QString title, text;
    int icon = 0;
    if (!libLoader.loaded() || !libLoader.ftxGetLibVersionStr || libLoader.ftxInitLib()!=FTLIB_ERR_SUCCESS) {
        title = "Ошибка";
        text = "Не удалось загрузить библиотеку \"ftMscLib\"";
        icon = QMessageBox::Critical;
    }
    if (icon==0) {
        char version[23];
        libLoader.ftxGetLibVersionStr(version,23);
        if (strcmp(version,"01.05.11  (2012/02/19)")!=0) {
            title = "Внимание";
            text = "Эта версия библиотеки может работать неккоректно";
            icon = QMessageBox::Warning;
        }
    }
    if (icon!=0) showError(title,text,icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_9_triggered()
{
    QDesktopServices::openUrl(QUrl("http://andrew-quardex.com/blue-button/?v="+version));
}

void MainWindow::on_action_11_triggered()
{
    if (formAbout==0) formAbout = new FormAbout();
    formAbout->show();
    formAbout->activateWindow();
}

void MainWindow::on_pushButton_clicked()
{
    if (connector.searchCom()) {
        showPortsList();
    } else {
        showError("Информация","COM порты не обнаружены",QMessageBox::Information);
    }
    refreshButtonStatus();
}

void MainWindow::on_pushButton_2_clicked()
{
    QRegExp rule(" .*");
    QString shortName = ui->comboBox->currentText().replace(rule,"");
    QByteArray comPortName = shortName.toLatin1();
    if (!connector.openCom(comPortName.data())) showError("Ошибка","Не удалось подключиться к контроллеру через \""+ui->comboBox->currentText()+"\"",QMessageBox::Critical);
    refreshButtonStatus();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!connector.closeCom()) showError("Ошибка","Не удалось отключиться от контроллера",QMessageBox::Critical);
    refreshButtonStatus();
}

void MainWindow::on_pushButton_4_clicked()
{
    if (!connector.startTA()) showError("Ошибка","Не удалось запустить Transfer Area",QMessageBox::Critical);
    refreshButtonStatus();
}

void MainWindow::on_pushButton_5_clicked()
{
     if (!connector.stopTA()) showError("Ошибка","Не удалось остановить Transfer Area",QMessageBox::Critical);
     refreshButtonStatus();
}

void MainWindow::refreshButtonStatus()
{
    switchButtonStatus(connector.getFound(),connector.getConnected(),connector.getStarted());
}

void MainWindow::switchButtonStatus(bool found,bool connected,bool started)
{
    ui->comboBox->setEnabled(found);
    ui->pushButton_2->setEnabled(found&&!connected);
    ui->pushButton_3->setEnabled(found&&connected);
    ui->pushButton_4->setEnabled(found&&!started&&connected);
    ui->pushButton_5->setEnabled(found&&started&&connected);
}

void MainWindow::showPortsList()
{
    ui->comboBox->clear();
    for(int i=0;i<connector.getPorts().size();i++) {
        ui->comboBox->addItem(connector.getPorts()[i]);
    }
}

void MainWindow::buttonsChanged()
{
    FileManager::saved = false;
    showButtonsList();
    refreshMenu();
}

void MainWindow::showButtonsList() //вывод списка клавиш
{
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            delete ui->tableWidget->item(i,j);
        }
    }
    ui->tableWidget->setRowCount(0);
    QString cell;
    for (int i=0;i<controller.getButtons().size();i++) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        int curRow = ui->tableWidget->rowCount()-1;
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(controller.getButtons()[i].name);
        ui->tableWidget->setItem(curRow,0,item);

        if (controller.getButtons()[i].controller==0) {
            cell = "Master";
        } else {
            cell = "Extension "+QString::number(controller.getButtons()[i].controller+1);
        }
        item = new QTableWidgetItem;
        item->setText(cell);
        ui->tableWidget->setItem(curRow,1,item);

        item = new QTableWidgetItem;
        item->setText("M"+QString::number(controller.getButtons()[i].motor+1));
        ui->tableWidget->setItem(curRow,2,item);

        if (controller.getButtons()[i].direction) {
            cell = "--->";
        } else {
            cell = "<---";
        }
        item = new QTableWidgetItem;
        item->setText(cell);
        ui->tableWidget->setItem(curRow,3,item);

        item = new QTableWidgetItem;
        item->setText(QString::number(controller.getButtons()[i].speed));
        ui->tableWidget->setItem(curRow,4,item);
        if (formEditor->getCurButtonIndex()<0) {
            ui->tableWidget->selectRow(ui->tableWidget->rowCount()-1);
        } else {
            ui->tableWidget->selectRow(formEditor->getCurButtonIndex());
        }
    }
}

void MainWindow::refreshMenu()
{
    ui->action_5->setEnabled(!FileManager::saved);
    ui->action_6->setEnabled(true);
}

void MainWindow::showError(QString title, QString text, int icon)
{
    QMessageBox errorMessage(title,text,
            QMessageBox::Icon(icon),
            QMessageBox::NoButton,
            QMessageBox::NoButton,
            QMessageBox::Ok | QMessageBox::Escape);
    errorMessage.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (formAbout) formAbout->close();
    formEditor->close();
}

void MainWindow::on_pushButton_6_clicked()
{
    formEditor->loadButton(-1);
    formEditor->show();
    formEditor->activateWindow();
}

void MainWindow::on_pushButton_8_clicked()
{
    QModelIndexList selected;
    for (int i=0;i<ui->tableWidget->selectionModel()->selectedRows().count();i++) {
        controller.getButtons().erase(controller.getButtons().begin()+ui->tableWidget->selectionModel()->selectedRows()[i].row()-i);
    }
    showButtonsList();
    ui->tableWidget->clearSelection();
    FileManager::saved = false;
    refreshMenu();
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    ui->pushButton_7->setEnabled(ui->tableWidget->selectedItems().count()>0);
    ui->pushButton_8->setEnabled(ui->pushButton_7->isEnabled());
}

void MainWindow::on_pushButton_7_clicked()
{
    formEditor->loadButton(ui->tableWidget->currentRow());
    formEditor->show();
    formEditor->activateWindow();
}

void MainWindow::on_action_8_triggered()
{
   close();
}

void MainWindow::on_action_6_triggered()
{
   QString filePath = QFileDialog::getSaveFileName(this,"Сохранить как...","","Blue Button List (*.bbl)");
   if (filePath!="") {
       FileManager::filePath = filePath;
       on_action_5_triggered();
   }
}

void MainWindow::on_action_2_triggered()
{
   QString filePath = QFileDialog::getOpenFileName(this,"Открыть...","","Blue Button List (*.bbl)");
   if (filePath!="") {
       FileManager::load(filePath);
       showButtonsList();
       FileManager::filePath = filePath;
       FileManager::saved = true;
       refreshMenu();
   }
}

void MainWindow::on_action_triggered()
{
    controller.getButtons().clear();
    showButtonsList();
    FileManager::saved = false;
    refreshMenu();
}

void MainWindow::on_action_5_triggered()
{
    if (FileManager::filePath=="") {
        on_action_6_triggered();
        return;
    }
    FileManager::save(FileManager::filePath);
    FileManager::saved = true;
    refreshMenu();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())  controller.exec(event->nativeVirtualKey(),true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())  controller.exec(event->nativeVirtualKey(),false);

}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    on_pushButton_7_clicked();
}
