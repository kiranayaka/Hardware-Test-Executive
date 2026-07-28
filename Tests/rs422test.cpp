#include "rs422test.h"
#include "testresult.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>


RS422Test::RS422Test() //: basetest("RS422 Test")
{
}

TestResult RS422Test::execute()
{
    QElapsedTimer timer;
    timer.start();
    TestResult result;
    // Send packet
    // Receive packet
    // Process response
    timer.start();

    // Simulate hardware communication
    QThread::msleep(2000);

    result.executionTimeMs = timer.elapsed();


    result.Status = true;
    result.executionTimeMs = timer.elapsed();

    return result;
}