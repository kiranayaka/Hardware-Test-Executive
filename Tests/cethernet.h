#ifndef CETHERNET_H
#define CETHERNET_H

#include "testresult.h"
#include "basetest.h"

class CEthernet : public basetest
{
public:
    CEthernet();
    TestResult execute();
};

#endif // CETHERNET_H
