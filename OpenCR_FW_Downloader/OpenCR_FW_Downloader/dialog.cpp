#include "dialog.h"
#include "ui_dialog.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QtCore>
#include <QFileDialog>
#include <QTextCodec>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //! [0]
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);
    //make sure user can input their own port name!
    ui->portBox->setEditable(true);

    ui->baudRateBox->addItem("1200", BAUD1200);
    ui->baudRateBox->addItem("2400", BAUD2400);
    ui->baudRateBox->addItem("4800", BAUD4800);
    ui->baudRateBox->addItem("9600", BAUD9600);
    ui->baudRateBox->addItem("19200", BAUD19200);
    ui->baudRateBox->addItem("115200", BAUD115200);
    ui->baudRateBox->setCurrentIndex(5);

    ui->parityBox->addItem("NONE", PAR_NONE);
    ui->parityBox->addItem("ODD", PAR_ODD);
    ui->parityBox->addItem("EVEN", PAR_EVEN);

    ui->dataBitsBox->addItem("5", DATA_5);
    ui->dataBitsBox->addItem("6", DATA_6);
    ui->dataBitsBox->addItem("7", DATA_7);
    ui->dataBitsBox->addItem("8", DATA_8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->stopBitsBox->addItem("1", STOP_1);
    ui->stopBitsBox->addItem("2", STOP_2);

    ui->queryModeBox->addItem("Polling", QextSerialPort::Polling);
    ui->queryModeBox->addItem("EventDriven", QextSerialPort::EventDriven);
    //! [0]

    ui->led_SerialOnOff->turnOff();
    ui->led_MavlinkStatus->turnOff();
    ui->led_Tx->turnOff();
    ui->led_Rx->turnOff();

    timer = new QTimer(this);
    timer->setInterval(40);

    timer_colck = new QTimer(this);
    connect(timer_colck, SIGNAL(timeout()), this, SLOT(onClockLabelUpdate()));
    timer_colck->start(1000);

    //! [1]
    PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(ui->portBox->currentText(), settings, QextSerialPort::Polling);
    //! [1]

    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();

    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)), SLOT(onBaudRateChanged(int)));
    connect(ui->parityBox, SIGNAL(currentIndexChanged(int)), SLOT(onParityChanged(int)));
    connect(ui->dataBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onDataBitsChanged(int)));
    connect(ui->stopBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onStopBitsChanged(int)));
    connect(ui->queryModeBox, SIGNAL(currentIndexChanged(int)), SLOT(onQueryModeChanged(int)));
    connect(ui->timeoutBox, SIGNAL(valueChanged(int)), SLOT(onTimeoutChanged(int)));
    connect(ui->portBox, SIGNAL(editTextChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->openCloseButton, SIGNAL(clicked()), SLOT(onOpenCloseButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), SLOT(onSendButtonClicked()));
    connect(timer, SIGNAL(timeout()), SLOT(onReadyRead()));
    connect(port, SIGNAL(readyRead()), SLOT(onReadyRead()));

    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)), SLOT(onPortAddedOrRemoved()));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), SLOT(onPortAddedOrRemoved()));

    ui->tb_hexview->setRowCount(1);
    ui->tb_hexview->setColumnCount(1);
    ui->tb_hexview->setItem(0, 0, new QTableWidgetItem(" "));

    QDateTime local(QDateTime::currentDateTime());
    ui->label_13->setText(local.toString());

    setWindowTitle("OpenCR Firmware Downloader v1.0");
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::onPortNameChanged(const QString & /*name*/)
{
    if (port->isOpen()) {
        port->close();
        ui->led_SerialOnOff->turnOff();
    }
}
//! [2]
void Dialog::onBaudRateChanged(int idx)
{
    port->setBaudRate((BaudRateType)ui->baudRateBox->itemData(idx).toInt());
}

void Dialog::onParityChanged(int idx)
{
    port->setParity((ParityType)ui->parityBox->itemData(idx).toInt());
}

void Dialog::onDataBitsChanged(int idx)
{
    port->setDataBits((DataBitsType)ui->dataBitsBox->itemData(idx).toInt());
}

void Dialog::onStopBitsChanged(int idx)
{
    port->setStopBits((StopBitsType)ui->stopBitsBox->itemData(idx).toInt());
}

void Dialog::onQueryModeChanged(int idx)
{
    port->setQueryMode((QextSerialPort::QueryMode)ui->queryModeBox->itemData(idx).toInt());
}

void Dialog::onTimeoutChanged(int val)
{
    port->setTimeout(val);
}
//! [2]
//! [3]
void Dialog::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        port->setPortName(ui->portBox->currentText());
        port->open(QIODevice::ReadWrite);
    }
    else {
        port->close();
    }

    //If using polling mode, we need a QTimer
    if (port->isOpen() && port->queryMode() == QextSerialPort::Polling)
        timer->start();
    else
        timer->stop();

    //update led's status
    ui->led_SerialOnOff->turnOn(port->isOpen());
}
//! [3]
//! [4]
void Dialog::onSendButtonClicked()
{
    //todo:program으로 변경
    //if (port->isOpen() && !ui->sendEdit->toPlainText().isEmpty())
    //    port->write(ui->sendEdit->toPlainText().toLatin1());
}

void Dialog::onReadyRead()
{
    if (port->bytesAvailable()) {
        ui->textEdit_Log->moveCursor(QTextCursor::End);
        ui->textEdit_Log->insertPlainText(QString::fromLatin1(port->readAll()));
    }
}

void Dialog::onClockLabelUpdate()
{
    QDateTime local(QDateTime::currentDateTime());
    ui->label_13->setText(local.toString("hh:mm:ss A"));

    //onTextBoxLogPrint("test\r\n");
}

void Dialog::onPortAddedOrRemoved()
{
    QString current = ui->portBox->currentText();

    ui->portBox->blockSignals(true);
    ui->portBox->clear();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);

    ui->portBox->setCurrentIndex(ui->portBox->findText(current));

    ui->portBox->blockSignals(false);
}

void Dialog::on_pushButton_LoadFirmware_clicked()
{
    QFileDialog fileDialog(this,tr("Open File"),
            QCoreApplication::applicationDirPath(),
            tr("Img(*.hex *.bin)"));

    QStringList fileNames;
    if(fileDialog.exec()){
        fileNames = fileDialog.selectedFiles();
    }

    QString selectedFile;
    for(int nIndex=0; nIndex < fileNames.size(); nIndex++){
        selectedFile.append(fileNames.at(nIndex).toLocal8Bit().constData());
    }

    //QTextCodec *textCodec = QTextCodec::codecForName("eucKR");
   // ui->textEdit_Log->setText(selectedFile.toUtf8());
    onTextBoxLogPrint(selectedFile.toUtf8());

    QFile file(selectedFile.toUtf8());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0,"error",file.errorString());
    }


    QByteArray ba;
    //QDataStream dataStreamReader(&file);
    //dataStreamReader >> ba;

    ba = file.readAll();

    QString s2 = ba.toHex();
    qDebug() << s2;

       // ui->progressBar_Status->setValue(100*line.count()*line.size());
   // }

    int n = file.size();
    ui->tb_hexview->setRowCount((n/32) +1);
    ui->tb_hexview->setColumnCount(8);

   // QString DataAsString = line.data()[0];//QTextCodec::codecForMib("eucKR")->toUnicode(line.data()[0]);
   // ui->tb_hexview->setItem(0, 1, new QTableWidgetItem(DataAsString));

    file.close();
}

void Dialog::onTextBoxLogPrint(QString str)
{
    QDateTime local(QDateTime::currentDateTime());

    ui->textEdit_Log->setTextColor(QColor(0x00,0x00,0x97));
    ui->textEdit_Log->insertPlainText("\r\n"+local.toString()+" : ");

//ui->textEdit_Log->textCursor().deletePreviousChar();
    ui->textEdit_Log->moveCursor (QTextCursor::End);
    ui->textEdit_Log->setTextColor(QColor(0x00,0x00,0x00));
    ui->textEdit_Log->insertPlainText(str);
    ui->textEdit_Log->moveCursor (QTextCursor::End);


  //  ui->textEdit_Log->append(str);

}
