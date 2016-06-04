/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTableWidget *tb_hexview;
    QProgressBar *progressBar_Status;
    QTextEdit *textEdit_log;
    QPushButton *pushButton_LoadFirmware;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(844, 671);
        tb_hexview = new QTableWidget(Dialog);
        tb_hexview->setObjectName(QStringLiteral("tb_hexview"));
        tb_hexview->setGeometry(QRect(380, 10, 451, 431));
        progressBar_Status = new QProgressBar(Dialog);
        progressBar_Status->setObjectName(QStringLiteral("progressBar_Status"));
        progressBar_Status->setGeometry(QRect(10, 640, 821, 23));
        progressBar_Status->setValue(24);
        textEdit_log = new QTextEdit(Dialog);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        textEdit_log->setGeometry(QRect(10, 450, 821, 181));
        pushButton_LoadFirmware = new QPushButton(Dialog);
        pushButton_LoadFirmware->setObjectName(QStringLiteral("pushButton_LoadFirmware"));
        pushButton_LoadFirmware->setGeometry(QRect(254, 402, 101, 21));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        pushButton_LoadFirmware->setText(QApplication::translate("Dialog", "LoadFirmware", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
