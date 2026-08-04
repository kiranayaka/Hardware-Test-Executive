#include "TestManager.h"

QVector<TestExecution>

TestManager::TestManager()
{
}

void TestManager::addTest(basetest *test)
{
    m_tests.append(test);
}

QVector<TestResult> TestManager::runAll()
{
    QVector<TestResult> results;

    for(basetest *test : m_tests)
    {
        results.append(test->execute());
    }

    return results;
}

QVector<TestExecution> TestManager::runAll()
{
    QVector<TestExecution> executions;

    for(BaseTest* test : m_tests)
    {
        TestExecution execution;
        execution.test = test;
        execution.result = test->execute();

        executions.append(execution);
    }

    return executions;
}