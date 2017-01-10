#include "formabout.h"
#include "ui_formabout.h"
#include <mainwindow.h>
#include <QDesktopServices.h>
#include <QUrl.h>
#include <QString.h>
#include <QDebug.h>

extern QString version;

//Класс окна "О программе"

FormAbout::FormAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAbout)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    ui->label->setText(ui->label->text()+"<b>"+version+"</b>");
    ui->label_3->adjustSize();
    ui->label_4->move(ui->label_3->x()+ui->label_3->width(),ui->label_4->y());
    ui->label_4->adjustSize();
}

FormAbout::~FormAbout()
{
    delete ui;
}

void FormAbout::on_label_4_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl("http://andrew-quardex.com"));
}
