#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QString>

struct TestResult
{
    bool Status;
    QString failReason;
    int executionTimeMs;
};

#endif // TESTRESULT_H