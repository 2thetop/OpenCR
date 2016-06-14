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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "hled.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTableWidget *tb_hexview;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *portBox;
    QLabel *label_2;
    QComboBox *baudRateBox;
    QLabel *label_3;
    QComboBox *dataBitsBox;
    QLabel *label_4;
    QComboBox *parityBox;
    QLabel *label_5;
    QComboBox *stopBitsBox;
    QLabel *label_7;
    QSpinBox *timeoutBox;
    QLabel *label_6;
    QComboBox *queryModeBox;
    QSpacerItem *verticalSpacer;
    QPushButton *openCloseButton;
    QLabel *label_12;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *textEdit_Log;
    QProgressBar *progressBar_Status;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    HLed *led_SerialOnOff;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    HLed *led_MavlinkStatus;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_3;
    HLed *led_Tx;
    QLabel *label_11;
    HLed *led_Rx;
    QLabel *label_10;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_LoadFirmware;
    QPushButton *sendButton_3;
    QPushButton *sendButton_2;
    QPushButton *sendButton;
    QLabel *label_13;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(844, 671);
        tb_hexview = new QTableWidget(Dialog);
        tb_hexview->setObjectName(QStringLiteral("tb_hexview"));
        tb_hexview->setGeometry(QRect(380, 10, 451, 431));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 161, 411));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        portBox = new QComboBox(layoutWidget);
        portBox->setObjectName(QStringLiteral("portBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, portBox);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        baudRateBox = new QComboBox(layoutWidget);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, baudRateBox);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        dataBitsBox = new QComboBox(layoutWidget);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, dataBitsBox);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        parityBox = new QComboBox(layoutWidget);
        parityBox->setObjectName(QStringLiteral("parityBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, parityBox);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        stopBitsBox = new QComboBox(layoutWidget);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, stopBitsBox);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        timeoutBox = new QSpinBox(layoutWidget);
        timeoutBox->setObjectName(QStringLiteral("timeoutBox"));
        timeoutBox->setMinimum(-1);
        timeoutBox->setMaximum(10000);
        timeoutBox->setSingleStep(10);
        timeoutBox->setValue(10);

        formLayout->setWidget(5, QFormLayout::FieldRole, timeoutBox);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        queryModeBox = new QComboBox(layoutWidget);
        queryModeBox->setObjectName(QStringLiteral("queryModeBox"));

        formLayout->setWidget(6, QFormLayout::FieldRole, queryModeBox);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        openCloseButton = new QPushButton(layoutWidget);
        openCloseButton->setObjectName(QStringLiteral("openCloseButton"));

        verticalLayout_2->addWidget(openCloseButton);

        label_12 = new QLabel(Dialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 430, 70, 20));
        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 450, 821, 220));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        textEdit_Log = new QTextEdit(layoutWidget1);
        textEdit_Log->setObjectName(QStringLiteral("textEdit_Log"));

        verticalLayout_4->addWidget(textEdit_Log);

        progressBar_Status = new QProgressBar(layoutWidget1);
        progressBar_Status->setObjectName(QStringLiteral("progressBar_Status"));
        progressBar_Status->setValue(24);

        verticalLayout_4->addWidget(progressBar_Status);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(180, 12, 191, 411));
        verticalLayout_5 = new QVBoxLayout(layoutWidget2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        led_SerialOnOff = new HLed(layoutWidget2);
        led_SerialOnOff->setObjectName(QStringLiteral("led_SerialOnOff"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(led_SerialOnOff->sizePolicy().hasHeightForWidth());
        led_SerialOnOff->setSizePolicy(sizePolicy);
        led_SerialOnOff->setMinimumSize(QSize(20, 20));
        led_SerialOnOff->setMaximumSize(QSize(25, 25));

        horizontalLayout->addWidget(led_SerialOnOff);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        led_MavlinkStatus = new HLed(layoutWidget2);
        led_MavlinkStatus->setObjectName(QStringLiteral("led_MavlinkStatus"));
        sizePolicy.setHeightForWidth(led_MavlinkStatus->sizePolicy().hasHeightForWidth());
        led_MavlinkStatus->setSizePolicy(sizePolicy);
        led_MavlinkStatus->setMinimumSize(QSize(20, 20));
        led_MavlinkStatus->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(led_MavlinkStatus);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        led_Tx = new HLed(layoutWidget2);
        led_Tx->setObjectName(QStringLiteral("led_Tx"));
        sizePolicy.setHeightForWidth(led_Tx->sizePolicy().hasHeightForWidth());
        led_Tx->setSizePolicy(sizePolicy);
        led_Tx->setMinimumSize(QSize(20, 20));
        led_Tx->setMaximumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(led_Tx);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_3->addWidget(label_11);

        led_Rx = new HLed(layoutWidget2);
        led_Rx->setObjectName(QStringLiteral("led_Rx"));
        sizePolicy.setHeightForWidth(led_Rx->sizePolicy().hasHeightForWidth());
        led_Rx->setSizePolicy(sizePolicy);
        led_Rx->setMinimumSize(QSize(20, 20));
        led_Rx->setMaximumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(led_Rx);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 148, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_LoadFirmware = new QPushButton(layoutWidget2);
        pushButton_LoadFirmware->setObjectName(QStringLiteral("pushButton_LoadFirmware"));

        verticalLayout_3->addWidget(pushButton_LoadFirmware);

        sendButton_3 = new QPushButton(layoutWidget2);
        sendButton_3->setObjectName(QStringLiteral("sendButton_3"));

        verticalLayout_3->addWidget(sendButton_3);

        sendButton_2 = new QPushButton(layoutWidget2);
        sendButton_2->setObjectName(QStringLiteral("sendButton_2"));

        verticalLayout_3->addWidget(sendButton_2);

        sendButton = new QPushButton(layoutWidget2);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        verticalLayout_3->addWidget(sendButton);


        verticalLayout_5->addLayout(verticalLayout_3);

        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(258, 427, 111, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        label->setText(QApplication::translate("Dialog", "Port:", 0));
        label_2->setText(QApplication::translate("Dialog", "BaudRate:", 0));
        label_3->setText(QApplication::translate("Dialog", "DataBits:", 0));
        label_4->setText(QApplication::translate("Dialog", "Parity:", 0));
        label_5->setText(QApplication::translate("Dialog", "StopBits:", 0));
        label_7->setText(QApplication::translate("Dialog", "Timeout:", 0));
        timeoutBox->setSuffix(QApplication::translate("Dialog", " ms", 0));
        label_6->setText(QApplication::translate("Dialog", "QueryMode:", 0));
        openCloseButton->setText(QApplication::translate("Dialog", "Open/Close", 0));
        label_12->setText(QApplication::translate("Dialog", "Status Log :", 0));
        label_8->setText(QApplication::translate("Dialog", "Port On/Off Status", 0));
        label_9->setText(QApplication::translate("Dialog", "Mavlink connection Status", 0));
        label_11->setText(QApplication::translate("Dialog", "TX", 0));
        label_10->setText(QApplication::translate("Dialog", "RX", 0));
        pushButton_LoadFirmware->setText(QApplication::translate("Dialog", "LoadFirmware", 0));
        sendButton_3->setText(QApplication::translate("Dialog", "Erase", 0));
        sendButton_2->setText(QApplication::translate("Dialog", "Verify", 0));
        sendButton->setText(QApplication::translate("Dialog", "Program", 0));
        label_13->setText(QApplication::translate("Dialog", "localTime", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
