#include "cethernet.h"

#include "testresult.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

CEthernet::CEthernet() {}



TestResult CEthernet::execute()
{
    QElapsedTimer timer;
    timer.start();
    TestResult result;
    // Send packet
    // Receive packet
    // Process response


    // Simulate hardware communication
    QThread::msleep(2000);



    result.Status = true;
    result.executionTimeMs = timer.elapsed();

    return result;
}