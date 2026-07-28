#ifndef RS422TEST_H
#define RS422TEST_H

#include "basetest.h"
#include "testresult.h"

class RS422Test
{
public:
    RS422Test();

   // bool execute() override;
    TestResult execute();
};

#endif // RS422TEST_H
