#ifndef BASETEST_H
#define BASETEST_H

#include <QString>

#include "testresult.h"

#include <QSerialPort>
#include <QSerialPortInfo>

class basetest
{
    public:
    basetest(const QString& name);
    virtual ~basetest();
    QString getTestName() const;

    virtual TestResult execute() = 0;

  //   = send_Packet( )

    protected:
    QString m_testName;

};

#endif // BASETEST_H