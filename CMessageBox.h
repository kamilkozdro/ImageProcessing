#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QMessageBox>
#include <QString>

class CMessageBox
{
public:
    void showMessageBox(QString text, QString title, QMessageBox::Icon icon)
    {
        QMessageBox message;
        message.setWindowTitle(title);
        message.setText(text);
        message.setIcon(icon);
        message.exec();
    }
};

#endif // CMESSAGEBOX_H
