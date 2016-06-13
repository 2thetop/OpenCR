#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class QTimer;
class QextSerialPort;
class QextSerialEnumerator;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_LoadFirmware_clicked();
    void onPortNameChanged(const QString &name);
    void onBaudRateChanged(int idx);
    void onParityChanged(int idx);
    void onDataBitsChanged(int idx);
    void onStopBitsChanged(int idx);
    void onQueryModeChanged(int idx);
    void onTimeoutChanged(int val);
    void onOpenCloseButtonClicked();
    void onSendButtonClicked();
    void onReadyRead();
    void onClockLabelUpdate();
    void onTextBoxLogPrint(QString str);
    void onPortAddedOrRemoved();
    void on_sendButton_clicked();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    QTimer *timer_colck;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

public:

};

#endif // DIALOG_H
