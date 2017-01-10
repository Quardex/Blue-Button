#ifndef QLINEEDITEXTFORKEY_H
#define QLINEEDITEXTFORKEY_H

#include <QLineEdit>
#include <formeditor.h>

class QLineEditExtForKey : public QLineEdit
{
    Q_OBJECT
public:
    int buttonKey;
    QString buttonName;
    explicit QLineEditExtForKey(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent * event);

signals:

public slots:

};

#endif // QLINEEDITEXTFORKEY_H
