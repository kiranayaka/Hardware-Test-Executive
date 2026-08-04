#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tests/testresult.h"
#include <QDateTime>
#include <QThread>
#include <QTimer>

#include "Tests/rs422test.h"
#include "Tests/cmemorytest.h"
#include "Tests/cethernet.h"
#include "Tests/basetest.h"




/*-----Global variable-----*/
float G_PB_Value = 0.0;//Global Progress Bar Value
int G_pass_Count = 0;//Global Pass Count
int G_Fail_Count = 0;//Global Fail Count


int Num_of_Tests = 0 ;
//bool result =true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Run_Btn_clicked()
{

    ui->Conn_Status->setText("🟢 Connected");
    /*cleanup Previous Activities*/
    {
        G_PB_Value = 0.0;
        G_pass_Count = 0;
        G_Fail_Count = 0;
        Num_of_Tests = 0;

        ui->TS_Passed_L->setNum(0);
        ui->TS_Failed_L->setNum(0);
        ui->OverallProgress_PB->setValue(0);
    }



    QVector<basetest*> selectedTests;

    if(ui->RS_422_ChkBox->isChecked())
        selectedTests.append(new RS422Test());

    if(ui->Memory_ChkBox->isChecked())
        selectedTests.append(new CMemorytest());

    if(ui->Ethernet_ChkBox->isChecked())
        selectedTests.append(new CEthernet());

    Num_of_Tests = selectedTests.size();

    for(basetest* test : selectedTests)
    {
        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing [%2] test ")
                                                    .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                                    .arg(test->getTestName()));

        ui->Current_Test->setText(test->getTestName());

        int row = ui->tableWidgetResults->rowCount();
        ui->tableWidgetResults->insertRow(row);

        TestResult result = test->execute();

       // ui->OverallProgress_PB->setValue(100);
        G_PB_Value = G_PB_Value + (100.0/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(
            row,
            0,
            new QTableWidgetItem(test->getTestName()));

        UpdateTestUI(test->getTestName(), result, row);
    }

    qDeleteAll(selectedTests);
    selectedTests.clear();
}

void MainWindow::UpdateTestUI(const QString& testName,const TestResult& result,int row)
{
    ui->tableWidgetResults->setItem(row,0,new QTableWidgetItem(QString("%1").arg(testName)));
    ui->tableWidgetResults->setItem(row,1,new QTableWidgetItem("Completed"));

    if(result.Status)
    {
        ui->tableWidgetResults->setItem(row,2,new QTableWidgetItem("🟢 PASS"));


        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] %2 Passed")
                .arg(QTime::currentTime().toString("hh:mm:ss"))
                .arg(testName));
        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    }
    else
    {
        ui->tableWidgetResults->setItem(row,2,new QTableWidgetItem("🔴 FAIL"));


        ui->PTE_ApplicationLog->appendPlainText(
            QString("[%1] %2 Failed")
                .arg(QTime::currentTime().toString("hh:mm:ss"))
                .arg(testName));
        G_Fail_Count++;
        ui->TS_Failed_L->setNum(G_Fail_Count);
    }

    QTime time(0,0,0);
    time = time.addMSecs(result.executionTimeMs);

    ui->tableWidgetResults->setItem(row,3,new QTableWidgetItem(time.toString("hh:mm:ss")));

    ui->Elapsed_Time->setText(time.toString("hh:mm:ss"));

    ui->tableWidgetResults->setItem(row,4,new QTableWidgetItem(result.failReason));

}


void MainWindow::on_BTN_ClearLog_clicked()
{
    ui->PTE_ApplicationLog->clear();
}
