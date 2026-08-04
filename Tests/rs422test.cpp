#include "rs422test.h"
#include "testresult.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "../Communication/communicationmanager.h"
#include <QElapsedTimer>


RS422Test::RS422Test()  : basetest("RS422 Test")
{

}

TestResult RS422Test::execute()
{
    QElapsedTimer timer;
    timer.start();

    TestResult result;

    communicationmanager comm;

    //------------------------------------
    // Open Port
    //------------------------------------

    if(!comm.openPort("COM1"))
    {
        result.Status = false;
        result.failReason = "Unable to open COM Port";
        result.executionTimeMs = timer.elapsed();
        return result;
    }

    //------------------------------------
    // Send Packet
    //------------------------------------

    QByteArray txData = "HELLO";

    if(!comm.sendPacket(txData))
    {
        result.Status = false;
        result.failReason = "Write Failed";

        comm.closePort();

        result.executionTimeMs = timer.elapsed();
        return result;
    }

    //------------------------------------
    // Receive Packet
    //------------------------------------

    QByteArray rxData = comm.receivePacket(1000);

    if(rxData.isEmpty())
    {
        result.Status = false;
        result.failReason = "Read Timeout";

        comm.closePort();

        result.executionTimeMs = timer.elapsed();
        return result;
    }

    //------------------------------------
    // Compare
    //------------------------------------

    if(rxData == txData)
    {
        result.Status = true;
        result.failReason = "";
    }
    else
    {
        result.Status = false;
        result.failReason = "Loopback Failed";
    }

    comm.closePort();

    result.executionTimeMs = timer.elapsed();

    return result;
}