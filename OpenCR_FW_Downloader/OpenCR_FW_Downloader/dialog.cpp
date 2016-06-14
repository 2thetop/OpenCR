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

#include "./msg/def.h"
//#include "./msg/msg.h"

#define FLASH_TX_BLOCK_LENGTH	(8*1024)
#define FLASH_RX_BLOCK_LENGTH	(128)
#define FLASH_PACKET_LENGTH   	128


uint32_t tx_buf[768*1024/4];
uint32_t rx_buf[768*1024/4];

static long iclock();
uint32_t crc_calc( uint32_t crc_in, uint8_t data_in );

err_code_t cmd_read_version( uint32_t *p_version, uint32_t *p_revision );
err_code_t cmd_read_board_name( uint8_t *p_str, uint8_t *p_len );
err_code_t cmd_flash_fw_erase( uint32_t length );
err_code_t cmd_flash_fw_write_begin( void );
err_code_t cmd_flash_fw_write_end( void );
err_code_t cmd_flash_fw_write_packet( uint16_t addr, uint8_t *p_data, uint8_t length );
err_code_t cmd_flash_fw_write_block( uint32_t addr, uint32_t length  );
err_code_t cmd_flash_fw_send_block_multi( uint8_t block_count );
err_code_t cmd_flash_fw_read_block( uint32_t addr, uint8_t *p_data, uint16_t length );
err_code_t cmd_flash_fw_verify( uint32_t length, uint32_t crc, uint32_t *p_crc_ret );
err_code_t cmd_jump_to_fw(void);


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



    //QDataStream dataStreamReader(&file);
    //dataStreamReader >> ba;

   // ba = file.readAll();

    //QString s2 = ba.toHex();
    //qDebug() << s2;
    //onTextBoxLogPrint(s2);
       // ui->progressBar_Status->setValue(100*line.count()*line.size());
   // }

    int file_size = file.size();
    onTextBoxLogPrint(QString("file size : %1 bytes").arg(QString::number(file_size)));
    ui->tb_hexview->setRowCount((file_size/16) +1);
    ui->tb_hexview->setColumnCount(4);

    for(int index=0; index < file_size; index = index+4)
    {
        QByteArray ba;
        QString tmpstr;

        char buf[4];
        file.seek(index);
        file.read(buf,4);

        ba = QByteArray::fromRawData(buf, 4);

        tmpstr = ba.mid(3,1).toHex().rightJustified(2,'0');
        tmpstr += ba.mid(2,1).toHex().rightJustified(2,'0');
        tmpstr += ba.mid(1,1).toHex().rightJustified(2,'0');
        tmpstr += ba.mid(0,1).toHex().rightJustified(2,'0');



        //tmpstr.append( QString::number(ba.at(3), 16).rightJustified(2, '0') );
        //tmpstr.append( QString::number(ba.at(2), 16).rightJustified(2, '0') );
        //tmpstr.append( QString::number(ba.at(1), 16).rightJustified(2, '0') );
        //tmpstr.append( QString::number(ba.at(0), 16).rightJustified(2, '0') );

        if(49152<index)
        {
            qDebug()<< index << tmpstr;
        }
        ui->tb_hexview->setItem((index/4)/4, (index/4)%4, new QTableWidgetItem(tmpstr.toUpper()));

    }


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

void Dialog::on_sendButton_clicked()
{
    int i;
    int j;
    int ret = 0;
    err_code_t err_code = OK;
    long t, dt;
    float calc_time;
    uint32_t fw_size = 256*1024*3;
    uint8_t  board_str[16];
    uint8_t  board_str_len;
    uint32_t board_version;
    uint32_t board_revision;
    uint32_t crc;
    uint32_t crc_ret = 0;
    uint8_t  *p_buf_crc;
    char *portname;
    uint32_t baud;
    uint8_t  block_buf[FLASH_TX_BLOCK_LENGTH];
    uint32_t addr;
    uint32_t len;

    onTextBoxLogPrint(">>\r\n");
    err_code = cmd_read_board_name( board_str, &board_str_len );
    if( err_code == OK )
    {
      onTextBoxLogPrint(QString::sprintf("Board Name : %c\r\n",board_str));
    }
    err_code = cmd_read_version( &board_version, &board_revision );
    if( err_code == OK )
    {
      onTextBoxLogPrint(QString::sprintf("Board Ver  : 0x%08x\r\n",board_version);
      onTextBoxLogPrint(QString::sprintf("Board Rev  : 0x%08x\r\n",board_revision);
    }
    onTextBoxLogPrint(">>\r\n");

    t = iclock();
    ret = opencr_ld_flash_erase(fw_size);
    dt = iclock() - t;
    onTextBoxLogPrint(QString::sprintf("flash_erase : %d : %f sec\r\n", ret, GET_CALC_TIME(dt)));
    if( ret < 0 )
    {
      ser_close( stm32_ser_id );
      fclose( opencr_fp );
      exit(1);
    }



  t = iclock();
  crc  = 0;
  addr = 0;
  while(1)
  {
    len = opencr_ld_file_read_data( block_buf, FLASH_TX_BLOCK_LENGTH);
    if( len == 0 ) break;

    for( i=0; i<len; i++ )
    {
      crc = crc_calc( crc,  block_buf[i] );
    }

    ret = opencr_ld_flash_write( addr, block_buf, len );
    if( ret < 0 ) break;
    addr += len;
  }
  dt = iclock() - t;

  printf("flash_write : %d : %f sec \r\n", ret,  GET_CALC_TIME(dt));
  if( ret < 0 )
  {
    ser_close( stm32_ser_id );
    fclose( opencr_fp );
    return -1;
  }

  t = iclock();
  err_code = cmd_flash_fw_verify( fw_size, crc, &crc_ret );
  dt = iclock() - t;
  if( err_code == OK )
  {
    printf("CRC OK %X %X %f sec\r\n", crc, crc_ret, GET_CALC_TIME(dt));
  }
  else
  {
    printf("CRC Fail : 0x%X : %X, %X %f sec\r\n", err_code, crc, crc_ret, GET_CALC_TIME(dt));
  }

  printf("jump_to_fw \r\n");
  cmd_jump_to_fw();

  ser_close( stm32_ser_id );
  fclose( opencr_fp );

}




/*---------------------------------------------------------------------------
     TITLE   : cmd_read_version
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_read_version( uint32_t *p_version, uint32_t *p_revision )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_read_version_pack(0, 0, &tx_msg, resp, param);
  msg_send(0, &tx_msg);

  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      //printf("BootVersion : 0x%08X\r\n", ack_msg.data[3]<<24|ack_msg.data[2]<<16|ack_msg.data[1]<<8|ack_msg.data[0]);
      *p_version  = ack_msg.data[3]<<24|ack_msg.data[2]<<16|ack_msg.data[1]<<8|ack_msg.data[0];
      *p_revision = ack_msg.data[7]<<24|ack_msg.data[6]<<16|ack_msg.data[5]<<8|ack_msg.data[4];
      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return OK;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_read_board_name
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_read_board_name( uint8_t *p_str, uint8_t *p_len )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_read_board_name_pack(0, 0, &tx_msg, resp, param);
  msg_send(0, &tx_msg);

  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      *p_len = ack_msg.length;
      memcpy(p_str, ack_msg.data, ack_msg.length);
      p_str[ack_msg.length] = 0;

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return OK;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_erase
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_erase( uint32_t length )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_flash_fw_erase_pack(0, 0, &tx_msg, resp, length, param);
  msg_send(0, &tx_msg);

  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 3000) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}

/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_write_begin
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_write_begin( void )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_flash_fw_write_begin_pack(0, 0, &tx_msg, resp, param);
  msg_send(0, &tx_msg);

  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_write_end
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_write_end( void )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_flash_fw_write_end_pack(0, 0, &tx_msg, resp, param);
  msg_send(0, &tx_msg);

  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      //printf("block_count  : %d\r\n", ack_msg.data[1]<<8|ack_msg.data[0]);
      //printf("block_length : %d\r\n", ack_msg.data[5]<<24|ack_msg.data[4]<<16|ack_msg.data[3]<<8|ack_msg.data[2]);


      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_write_packet
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_write_packet( uint16_t addr, uint8_t *p_data, uint8_t length )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t resp = 0;



  mavlink_msg_flash_fw_write_packet_pack(0, 0, &tx_msg, resp, addr, length, p_data);
  msg_send(0, &tx_msg);


  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_send_block_multi
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_send_block_multi( uint8_t block_count )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t buf[256];
  uint8_t tx_buf[16*1024];
  uint8_t resp = 0;
  uint8_t i;
  uint32_t len;


   len = 0;
  for( i=0; i<block_count; i++ )
  {
    mavlink_msg_flash_fw_write_packet_pack(0, 0, &tx_msg, resp, 0, 128, buf);
    len += mavlink_msg_to_send_buffer(&tx_buf[len], &tx_msg);
  }
  write_bytes((char *)tx_buf, len);

  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_write_block
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_write_block( uint32_t addr, uint32_t length  )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t buf[256];
  uint8_t resp = 1;


  mavlink_msg_flash_fw_write_block_pack(0, 0, &tx_msg, resp, addr, length);
  msg_send(0, &tx_msg);


  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_read_block
     WORK    :
---------------------------------------------------------------------------*/
#if 0
err_code_t cmd_flash_fw_read_block( uint32_t addr, uint8_t *p_data, uint16_t length )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_flash_fw_read_t  resp_msg;
  uint8_t resp = 1;
  uint16_t received_length;


  mavlink_msg_flash_fw_read_block_pack(0, 0, &tx_msg, resp, addr, length);
  msg_send(0, &tx_msg);



  if( resp == 1 )
  {
    received_length = 0;

    while(1)
    {
      if( msg_get_resp(0, &rx_msg, 3000) == TRUE )
      {
    mavlink_msg_flash_fw_read_decode( &rx_msg, &resp_msg);

    memcpy(&p_data[received_length], resp_msg.data, resp_msg.length);
    received_length += resp_msg.length;

    //printf("recv %d \r\n", received_length);

    if( received_length == length )
    {
      break;
    }
    else if( received_length > length )
    {
      err_code = ERR_SIZE_OVER;
      break;
    }
      }
      else
      {
    err_code = ERR_TIMEOUT;
    break;
      }
    }
  }

  return err_code;
}
#else
err_code_t cmd_flash_fw_read_block( uint32_t addr, uint8_t *p_data, uint16_t length )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_flash_fw_read_packet_t  resp_msg;
  uint8_t resp = 1;


  mavlink_msg_flash_fw_read_block_pack(0, 0, &tx_msg, resp, addr, length);
  msg_send(0, &tx_msg);



  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 100) == TRUE )
    {
      mavlink_msg_flash_fw_read_packet_decode( &rx_msg, &resp_msg);

      memcpy(p_data, resp_msg.data, resp_msg.length);

      if( resp_msg.length > length )
      {
    err_code = ERR_SIZE_OVER;
      }
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }

  return err_code;
}
#endif


/*---------------------------------------------------------------------------
     TITLE   : cmd_flash_fw_verify
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_flash_fw_verify( uint32_t length, uint32_t crc, uint32_t *p_crc_ret )
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 1;


  mavlink_msg_flash_fw_verify_pack(0, 0, &tx_msg, resp, length, crc, param);
  msg_send(0, &tx_msg);


  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      *p_crc_ret = ack_msg.data[3]<<24|ack_msg.data[2]<<16|ack_msg.data[1]<<8|ack_msg.data[0];

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }
  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : cmd_jump_to_fw
     WORK    :
---------------------------------------------------------------------------*/
err_code_t cmd_jump_to_fw(void)
{
  err_code_t err_code = OK;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t     ack_msg;
  uint8_t param[8];
  uint8_t resp = 0;


  mavlink_msg_jump_to_fw_pack(0, 0, &tx_msg, resp, param);
  msg_send(0, &tx_msg);


  if( resp == 1 )
  {
    if( msg_get_resp(0, &rx_msg, 500) == TRUE )
    {
      mavlink_msg_ack_decode( &rx_msg, &ack_msg);

      if( tx_msg.msgid == ack_msg.msg_id ) err_code = ack_msg.err_code;
      else                                 err_code = ERR_MISMATCH_ID;
    }
    else
    {
      err_code = ERR_TIMEOUT;
    }
  }
  return err_code;
}


/*---------------------------------------------------------------------------
     TITLE   : crc_calc
     WORK    :
---------------------------------------------------------------------------*/
uint32_t crc_calc( uint32_t crc_in, uint8_t data_in )
{

  crc_in  ^= data_in;
  crc_in  += data_in;

  return crc_in;
}

static long iclock()
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void Dialog::on_sendButton_3_clicked()
{

}
