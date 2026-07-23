#ifndef TESTMANAGER_H
#define TESTMANAGER_H

class TestManager
{
public:
    TestManager();

private:
    void RunRS422Test();
    void RunMemoryTest();
    void RunEthernetTest();
    void RunGPIOTest();
    void RunADCTest();
};

#endif // TESTMANAGER_H
