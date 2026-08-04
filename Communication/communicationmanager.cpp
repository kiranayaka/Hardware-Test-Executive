#include "communicationmanager.h"

#include <QDebug>
#include <QThread>


communicationmanager::communicationmanager()
{

}

bool communicationmanager::openPort(const QString &portName, int baudRate)
{
    serial.setPortName(portName);

    serial.setBaudRate(baudRate);

    serial.setDataBits(QSerialPort::Data8);

    serial.setParity(QSerialPort::NoParity);

    serial.setStopBits(QSerialPort::OneStop);

    serial.setFlowControl(QSerialPort::NoFlowControl);

    if(serial.open(QIODevice::ReadWrite))
    {
        qDebug() << "Port Opened Successfully";

        return true;
    }

    qDebug() << serial.errorString();

    return false;
}

bool communicationmanager::sendPacket(const QByteArray &packet)
{
    if(!serial.isOpen())
    {
        qDebug() << "Serial Port is not open!";
        return false;
    }

    qint64 bytesWritten = serial.write(packet);

    if(bytesWritten == -1)
    {
        qDebug() << "Failed to write packet!";
        return false;
    }

    serial.waitForBytesWritten(1000);

    qDebug() << "Packet Sent:" << packet.toHex(' ');

    return true;
}



QByteArray communicationmanager::receivePacket(int timeout)
{
    QByteArray receivedData;

    if(!serial.isOpen())
    {
        qDebug() << "Serial Port is not open!";
        return receivedData;
    }

    if(serial.waitForReadyRead(timeout))
    {
        receivedData = serial.readAll();

        while(serial.waitForReadyRead(50))
        {
            receivedData += serial.readAll();
        }

        qDebug() << "Packet Received:" << receivedData.toHex(' ');

        return receivedData;
    }

    qDebug() << "Receive Timeout!";

    return receivedData;
}

void communicationmanager::closePort()
{
    if(serial.isOpen())
    {
        serial.close();
        qDebug() << "Port Closed";
    }
}