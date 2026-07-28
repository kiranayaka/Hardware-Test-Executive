#include "basetest.h"

basetest::basetest() {}


basetest::basetest(QString name)
{
    m_testName = name;
}

basetest::~basetest()
{
}

QString basetest::getTestName() const
{
    return m_testName;
}