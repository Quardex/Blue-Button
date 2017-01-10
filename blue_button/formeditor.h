#ifndef FORMEDITOR_H
#define FORMEDITOR_H

#include <QWidget>
#include <controller.h>

namespace Ui {
class FormEditor;
}

class FormEditor : public QWidget
{
    Q_OBJECT

public:
    int getCurButtonIndex() const {return curButtonIndex;}
    explicit FormEditor(QWidget *parent = 0);
    ~FormEditor();

    void loadButton(int i);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::FormEditor *ui;
    int curButtonIndex;

signals:
    void buttonsChanged();

};

#endif // FORMEDITOR_H
