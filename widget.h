#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QTextBrowser>
#include <QLineEdit>
#include "serialport.h"
#include <string>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void switchSerialPortStatus();
    void flashSerialPortDevice();
    void clearMessage();
    void sendMessage();
    void getBaudrate(int index);
    void getDataBits(int index);
    void getParity(int index);
    void getStopbits(int index);
    void clearEdit();
    void showMessage();

private:
    const int WIDTH = 900;
    const int HEIGHT = 600;
    QPushButton * btnPortSwitch;
    QPushButton * btnClearMessage;
    QPushButton * btnFlashPortName;
    QPushButton * btnClearEdit;
    QPushButton * btnSendMessage;
    QLabel * labelPortName;
    QLabel * labelBaudrate;
    QLabel * labelDatabits;
    QLabel * labelStopbits;
    QLabel * labelParitybits;
    QComboBox * boxPortName;
    QComboBox * boxBaudrate;
    QComboBox * boxDatabits;
    QComboBox * boxStopbits;
    QComboBox * boxParitybits;
    QTextBrowser * textBrowser;
    QLineEdit * lineEdit;
    QLabel * labelProtocol;
    QComboBox * boxProtocol;

    SerialPort * serialport;
    QSerialPort::BaudRate baudrate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopbits;

    class Utils {
        void splitString(const std::string & in_, std::vector<std::string> & out, char split_);
    };
};
#endif // WIDGET_H
