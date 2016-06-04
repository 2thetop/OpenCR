#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QCoreApplication>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("OpenCR Firmware Downloader v1.0");
}

Dialog::~Dialog()
{
    delete ui;
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

    QTextCodec *textCodec = QTextCodec::codecForName("eucKR");
    ui->textEdit_log->setText(selectedFile.toUtf8());

    QFile file(selectedFile.toUtf8());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0,"error",file.errorString());
    }

    while(!file.atEnd()){
        QByteArray line = file.readLine();
        ui->progressBar_Status->setValue(100*line.count()*line.size());
    }

    file.close();
}
