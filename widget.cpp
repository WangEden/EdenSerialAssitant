#include "widget.h"
#include <qpushbutton.h>
#include <vector>
#include <QDebug>
#include <sstream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口属性
    resize(this->WIDTH, this->HEIGHT);
    this->setWindowTitle("甸哥串口调试助手");
    // 创建控件
    this->btnPortSwitch = new QPushButton ("打开串口", this);
    this->btnClearMessage = new QPushButton ("清除消息", this);
    this->btnClearEdit = new QPushButton ("清除编辑", this);
    this->btnSendMessage = new QPushButton ("发送信息", this);
    this->labelPortName = new QLabel("串口号",this);
    this->labelBaudrate = new QLabel("波特率",this);
    this->labelDatabits = new QLabel("数据位",this);
    this->labelStopbits = new QLabel("停止位",this);
    this->labelParitybits = new QLabel("校验位",this);
    this->boxPortName = new QComboBox(this);
    this->boxBaudrate = new QComboBox(this);
    this->boxDatabits = new QComboBox(this);
    this->boxStopbits = new QComboBox(this);
    this->boxParitybits = new QComboBox(this);
    this->textBrowser = new QTextBrowser(this);
    this->lineEdit = new QLineEdit(this);
    this->btnFlashPortName = new QPushButton("刷新设备", this);
    
    this->labelProtocol = new QLabel("通信协议", this);
    this->boxProtocol = new QComboBox(this);

    // 调整控件位置 900 600
    this->textBrowser->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.05),
                             int(this->WIDTH * 0.9), int(this->HEIGHT * 0.40));

    // 左边一列标签
    this->labelPortName->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));
    this->labelBaudrate->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.6), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));
    this->labelDatabits->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.7), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));
    this->labelStopbits->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.8), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));
    this->labelParitybits->setGeometry(int(this->WIDTH * 0.05), int(this->HEIGHT * 0.9), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));

    // 右边一列标签
    this->labelProtocol->setGeometry(int(this->WIDTH * 0.3), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.10), int(this->HEIGHT * 0.05));

    // 左边一列复选框
    this->boxPortName->setGeometry(int(this->WIDTH * 0.15), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.12), int(this->HEIGHT * 0.05));
    this->boxBaudrate->setGeometry(int(this->WIDTH * 0.15), int(this->HEIGHT * 0.6), int(this->WIDTH * 0.12), int(this->HEIGHT * 0.05));
    this->boxDatabits->setGeometry(int(this->WIDTH * 0.15), int(this->HEIGHT * 0.7), int(this->WIDTH * 0.12), int(this->HEIGHT * 0.05));
    this->boxStopbits->setGeometry(int(this->WIDTH * 0.15), int(this->HEIGHT * 0.8), int(this->WIDTH * 0.12), int(this->HEIGHT * 0.05));
    this->boxParitybits->setGeometry(int(this->WIDTH * 0.15), int(this->HEIGHT * 0.9), int(this->WIDTH * 0.12), int(this->HEIGHT * 0.05));

    // 右边一列复选框
    this->boxProtocol->setGeometry(int(this->WIDTH * 0.4), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));

    this->btnPortSwitch->setGeometry(int(this->WIDTH * 0.60), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));
    this->btnClearMessage->setGeometry(int(this->WIDTH * 0.80), int(this->HEIGHT * 0.5), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));
    this->btnFlashPortName->setGeometry(int(this->WIDTH * 0.60), int(this->HEIGHT * 0.6), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));

    this->lineEdit->setGeometry(int(this->WIDTH * 0.60), int(this->HEIGHT * 0.7), int(this->WIDTH * 0.35), int(this->HEIGHT * 0.05));
    this->btnClearEdit->setGeometry(int(this->WIDTH * 0.60), int(this->HEIGHT * 0.85), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));
    this->btnSendMessage->setGeometry(int(this->WIDTH * 0.80), int(this->HEIGHT * 0.85), int(this->WIDTH * 0.15), int(this->HEIGHT * 0.05));
    

    // 修改复选框信息
    QStringList list1 = {"9600", "19200", "38400", "57600", "115200"};
    this->boxBaudrate->addItems(list1);
    QStringList list2 = {"8位", "7位", "6位", "5位"};
    this->boxDatabits->addItems(list2);
    QStringList list3 = {"无", "1位", "2位"};
    this->boxStopbits->addItems(list3);
    QStringList list4 = {"无", "奇校验", "偶校验"};
    this->boxParitybits->addItems(list4);
    QStringList list5 = {"自定义协议", "ModbusRTU"};
    this->boxProtocol->addItems(list5);

    // 绑定Pushbutton点击事件
    connect(this->btnPortSwitch, &QPushButton::clicked, this, &Widget::switchSerialPortStatus);
    connect(this->btnFlashPortName, &QPushButton::clicked, this, &Widget::flashSerialPortDevice);
    connect(this->btnClearMessage, &QPushButton::clicked, this, &Widget::clearMessage);
    connect(this->btnClearEdit, &QPushButton::clicked, this, &Widget::clearEdit);
    connect(this->btnSendMessage, &QPushButton::clicked, this, &Widget::sendMessage);
    
    // 绑定复选框信号
    connect(this->boxBaudrate, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Widget::getBaudrate);
    connect(this->boxDatabits, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Widget::getDataBits);
    connect(this->boxParitybits, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Widget::getParity);
    connect(this->boxStopbits, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Widget::getStopbits);
    // connect() // RS485切换

    // 扫描一次串口设备
    this->serialport = new SerialPort();
    this->boxPortName->addItems(serialport->scanPortName());
    // 从复选框中获取信息
    getBaudrate(0);
    getDataBits(0);
    getStopbits(0);
    getParity(0);
    QString portname = this->boxPortName->currentText();
    this->serialport->serialPortInit(
        portname, 
        this->baudrate, 
        this->dataBits, 
        this->parity, 
        this->stopbits);
}

Widget::~Widget() 
{
    delete [] this->serialport;
}

void Widget::switchSerialPortStatus()
{
    // 打开串口的按钮按下时触发
    if (!this->btnPortSwitch->text().compare("打开串口")) {
        this->btnPortSwitch->setText("关闭串口");
        // 使复选框失能
        this->boxPortName->setEnabled(false);
        this->boxBaudrate->setEnabled(false);
        this->boxDatabits->setEnabled(false);
        this->boxStopbits->setEnabled(false);
        this->boxParitybits->setEnabled(false);
        this->boxProtocol->setEnabled(false);
        // 初始化串口设备
        QString portname = this->boxPortName->currentText();
        this->serialport->serialPortInit(
            portname, 
            this->baudrate, 
            this->dataBits, 
            this->parity, 
            this->stopbits);
        this->serialport->openPort(); // 打开串口
        connect(this->serialport->getQSerialPort(), &QSerialPort::readyRead, this, &Widget::showMessage);
    } 
    else {
        this->btnPortSwitch->setText("打开串口");
        // 使复选框使能
        this->boxPortName->setEnabled(true);
        this->boxBaudrate->setEnabled(true);
        this->boxDatabits->setEnabled(true);
        this->boxStopbits->setEnabled(true);
        this->boxParitybits->setEnabled(true);
        this->boxProtocol->setEnabled(true);
        // 删除串口设备对象
        this->serialport->closePort(); // 关闭串口
    }
}

void Widget::flashSerialPortDevice()
{
    // 扫描串口设备
    this->boxPortName->clear();   
    this->boxPortName->addItems(serialport->scanPortName());
}

void Widget::clearMessage()
{
    this->textBrowser->clear();
}

void Widget::sendMessage()
{
    // 获取lineEdit中的内容
    QString data = this->lineEdit->text();
    // 发送
    // 发送字符串
    // this->serialport->sendMessage(data);
    // 发送字节流
    QByteArray sendData;


    // 假设这是要转换的字符串
    // QString hexString = "14 5A 6E 87 4F";
    // 使用空白字符分割字符串
    QStringList hexList = data.split(" ");

    QByteArray byteArray;
    bool ok;
    for (const QString &hex : hexList) {
        // 将十六进制字符串转换为字节
        byteArray.append(static_cast<char>(hex.toInt(&ok, 16)));
    }
    this->serialport->sendMessage(byteArray);
    // 清空编辑框
    clearEdit();
    this->textBrowser->append("<span style='color: red;'>Send: " +data + "</span>");
}

void Widget::getBaudrate(int index)
{
    // QStringList list1 = {"9600", "19200", "38400", "57600", "115200"};
    std::vector<QSerialPort::BaudRate> l = {
        QSerialPort::Baud9600, 
        QSerialPort::Baud19200,
        QSerialPort::Baud38400,
        QSerialPort::Baud57600,
        QSerialPort::Baud115200
    };
    this->baudrate = l.at(this->boxBaudrate->currentIndex());
    // qDebug() << "当前波特率:" << this->baudrate;
}

void Widget::getDataBits(int index)
{
    std::vector<QSerialPort::DataBits> l = {
        QSerialPort::Data8, 
        QSerialPort::Data7,
        QSerialPort::Data6,
        QSerialPort::Data5,
    };
    this->dataBits = l.at(this->boxDatabits->currentIndex());
}

void Widget::getParity(int index)
{
    std::vector<QSerialPort::Parity> l = {
        QSerialPort::NoParity, 
        QSerialPort::OddParity,
        QSerialPort::EvenParity
    };
    this->parity = l.at(this->boxParitybits->currentIndex());
}

void Widget::getStopbits(int index)
{
    std::vector<QSerialPort::StopBits> l = {
        QSerialPort::UnknownStopBits, 
        QSerialPort::OneStop,
        QSerialPort::TwoStop
    };
    this->stopbits = l.at(this->boxStopbits->currentIndex());
}

void Widget::clearEdit()
{
    this->lineEdit->setText("");
}

void Widget::showMessage()
{
    QByteArray data = this->serialport->getQSerialPort()->readAll();
    this->textBrowser->append("Recv: "+data);
}

void Widget::Utils::splitString(const std::string & in_, std::vector<std::string> & out, char split_ = ' ')
{
    std::istringstream iss(in_);
    std::string token;
    while (std::getline(iss, token, split_)) {
        out.push_back(token);
    }
}
