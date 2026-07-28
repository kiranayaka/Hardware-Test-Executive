#ifndef BASETEST_H
#define BASETEST_H

#include <QString>
class basetest
{
public:
    basetest();
    basetest(QString name);
    virtual ~basetest();
    QString getTestName() const;

    virtual bool execute() = 0;


protected:
    QString m_testName;
};

#endif // BASETEST_H