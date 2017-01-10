#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <connector.h>
#include <controller.h>
#include <formabout.h>
#include <formeditor.h>
#include <QTableWidget.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    FormAbout *formAbout;
    FormEditor *formEditor;
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void refreshButtonStatus();

    void switchButtonStatus(bool found,bool connected,bool started);

    void showButtonsList();

    void refreshMenu();

    void showError(QString title, QString text, int icon);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

private slots:

    void on_action_9_triggered();

    void on_action_11_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void closeEvent(QCloseEvent *event);

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_pushButton_7_clicked();

    void on_action_8_triggered();

    void on_action_6_triggered();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_5_triggered();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

public slots:

    void showPortsList();

    void buttonsChanged();

};


#endif // MAINWINDOW_H
