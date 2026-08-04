#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include <QSerialPort>

class communicationmanager
{
public:
    communicationmanager();

    bool openPort(const QString& portName,
                  int baudRate = 115200);

    void closePort();

    bool sendPacket(const QByteArray& packet);

    QByteArray receivePacket(int timeout = 1000);


private:
    QSerialPort serial;
};

#endif // COMMUNICATIONMANAGER_H
