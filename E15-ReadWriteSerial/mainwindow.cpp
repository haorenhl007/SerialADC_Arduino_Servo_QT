#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

int cont=0;

void MainWindow::fTimer(){
  if(hw_is_available){
      if(hw->isWritable()){
          hw->write("a");
          if(hw->isReadable()){
              QByteArray datosLeidos = hw->read(2);
              int ADC_Digital = datosLeidos.toHex().toInt(0,16);
              float ADC_Flotante = ((float)ADC_Digital);
              ui->progressBar->setValue(ADC_Digital);
              ui->lcdNumber->display(ADC_Flotante);
              ui->lcdTemp->display(cont++);

          }
      }
  }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *cronometro=new QTimer(this);
     connect(cronometro, SIGNAL(timeout()), this, SLOT(fTimer()));
     cronometro->start(1000);

    hw_is_available = false;
    hw_port_name = "";
    hw = new QSerialPort;
    ui->lineEdit3->setText("9600");
    ui->lineEdit1->setText(QString::number(QSerialPortInfo::availablePorts().length()));
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            ui->lineEdit2->setText(QString::number(serialPortInfo.vendorIdentifier()));
            ui->lineEdit5->setText(QString::number(serialPortInfo.productIdentifier()));
            hw_port_name = serialPortInfo.portName();
            hw_is_available = true;
        }
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
        ui->comboBox1->addItem(serialPortInfo.portName());
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_7_clicked()
{
    QString bauds = ui->lineEdit3->text();
    int vbauds = bauds.toInt();
    if(vbauds == 9600){
        hw ->setBaudRate(QSerialPort::Baud9600);
        ui->lineEdit4->setText(bauds);
    }
    else{
    }

    if(hw_is_available){
        hw ->setPortName(hw_port_name);
        hw->open(QIODevice::ReadWrite);
        hw->setDataBits(QSerialPort::Data8);
        hw->setParity(QSerialPort::NoParity);
        hw->setStopBits(QSerialPort::OneStop);
        hw->setFlowControl(QSerialPort::NoFlowControl);
    }
    else{
        QMessageBox::information(this,"Error","Serial port not available");
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    hw->close();
    QMessageBox::information(this,"End of connection","Serial communication finished!");
    close();
}
