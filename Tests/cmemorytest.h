#ifndef CMEMORYTEST_H
#define CMEMORYTEST_H


#include "testresult.h"
#include "basetest.h"

class CMemorytest : public basetest
{
public:
    CMemorytest();
   TestResult execute();
};

#endif // CMEMORYTEST_H
