#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tests/testresult.h"
#include <QDateTime>
#include <QThread>
#include <QTimer>

#include "Tests/rs422test.h"
#include "Tests/cmemorytest.h"
#include "Tests/cethernet.h"




/*-----Global variable-----*/
QString cur_time , cur_time2 ;
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
    /*----- Cleanups Previous Activities-----*/
    G_PB_Value = 0;
    G_pass_Count =0;
    G_Fail_Count =0;
    ui->OverallProgress_PB->setValue(G_PB_Value);
    ui->TS_Passed_L->setNum(G_pass_Count);
    ui->TS_Failed_L->setNum(G_Fail_Count);
    ui->Conn_Status->setText("🟢 Connected");



        TestResult TestResult_Obj;


        if(ui->RS_422_ChkBox->isChecked())
        {
            RS422Test rs422;
            ui->Current_Test->setText("RS 422 Test");

            int Row_Count = ui->tableWidgetResults->rowCount();
            ui->tableWidgetResults->insertRow(Row_Count);

            ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing RS422 test ").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

            G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
            ui->OverallProgress_PB->setValue(G_PB_Value);

            //RunRS422Test();
            TestResult_Obj = rs422.execute();

            UpdateTestUI("RS422 Test", TestResult_Obj, Row_Count);

        }

        if(ui->Memory_ChkBox->isChecked())
        {
            CMemorytest cmemorytest_Obj;
            ui->Current_Test->setText("Memory Test");

            int Row_Count = ui->tableWidgetResults->rowCount();
            ui->tableWidgetResults->insertRow(Row_Count);

            ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing Memory test ").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

            G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
            ui->OverallProgress_PB->setValue(G_PB_Value);

            TestResult_Obj = cmemorytest_Obj.execute();

            UpdateTestUI("Memory Test", TestResult_Obj, Row_Count);
        }

        if(ui->Ethernet_ChkBox->isChecked())
        {
            CEthernet CEthernet_obj;
            ui->Current_Test->setText("Ethernet Test");

            int Row_Count = ui->tableWidgetResults->rowCount();
            ui->tableWidgetResults->insertRow(Row_Count);

            ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing Ethernet test ").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

            G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
            ui->OverallProgress_PB->setValue(G_PB_Value);

            TestResult_Obj = CEthernet_obj.execute();

            UpdateTestUI("Ethernet Test", TestResult_Obj, Row_Count);
        }

        if(ui->GPIO_ChkBox->isChecked())
        {
            RunGPIOTest();
        }

        if(ui->ADC_ChkBox->isChecked())
        {
            RunADCTest();
        }

       // ui->OverallProgress_PB->setValue(100);
        G_PB_Value = 0 ;
        G_pass_Count = 0;
}

void MainWindow::UpdateTestUI(const QString& testName,const TestResult& result,int row)
{
    ui->tableWidgetResults->setItem(row,0,new QTableWidgetItem(QString("%1").arg(testName)));
    ui->tableWidgetResults->setItem(row,1,new QTableWidgetItem("Completed"));

    if(result.Status)
    {
        ui->tableWidgetResults->setItem(row,2,new QTableWidgetItem("🟢 PASS"));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] %2 Passed")
                .arg(QTime::currentTime().toString("hh:mm:ss"))
                .arg(testName));
    }
    else
    {
        ui->tableWidgetResults->setItem(row,2,new QTableWidgetItem("🔴 FAIL"));

        G_Fail_Count++;
        ui->TS_Failed_L->setNum(G_Fail_Count);

        ui->PTE_ApplicationLog->appendPlainText(
            QString("[%1] %2 Failed")
                .arg(QTime::currentTime().toString("hh:mm:ss"))
                .arg(testName));
    }

    QTime time(0,0,0);
    time = time.addMSecs(result.executionTimeMs);

    ui->tableWidgetResults->setItem(row,3,new QTableWidgetItem(time.toString("hh:mm:ss")));

    ui->Elapsed_Time->setText(time.toString("hh:mm:ss"));

    ui->tableWidgetResults->setItem(row,4,new QTableWidgetItem(result.failReason));

}

void MainWindow::RunRS422Test()
{

    ui->Current_Test->setText("RS 422 Test");

    cur_time = QDateTime::currentDateTime().toString("hh:mm:ss");

    int Row_Count = ui->tableWidgetResults->rowCount();
    ui->tableWidgetResults->insertRow(Row_Count);

    ui->tableWidgetResults->setItem(Row_Count,0,new QTableWidgetItem("RS422 Test"));
    ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Running.."));
    ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("..."));
    ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem("00:00:00"));
    ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("..."));

    ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing RS422 test ").arg(cur_time));

    // Let the UI update, then schedule the completion after 2 seconds
    QTimer::singleShot(2000, this, [=]()
    {
        QTime elapsed(0,0);

        G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Completed"));
        ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("🟢 PASS"));//🔴 FAIL
        ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem(elapsed.toString("hh:mm:ss")));
        ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("None"));

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] RS422 Test Passed").arg(QTime::currentTime().toString("hh:mm:ss")));
        ui->Elapsed_Time->setText((elapsed.toString("hh:mm:ss")));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    });
}


void MainWindow::RunMemoryTest()
{

    ui->Current_Test->setText("Memory Test");

    cur_time = QDateTime::currentDateTime().toString("hh:mm:ss");
    int Row_Count = ui->tableWidgetResults->rowCount();
    ui->tableWidgetResults->insertRow(Row_Count);

    ui->tableWidgetResults->setItem(Row_Count,0,new QTableWidgetItem("Memory Test"));
    ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Running.."));
    ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("..."));
    ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem("00:00:00"));
    ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("..."));

    ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing Memory test ").arg(cur_time));

    // Let the UI update, then schedule the completion after 2 seconds
    QTimer::singleShot(2000, this, [=]() {


        QTime elapsed(0,0);
       // elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


        G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Completed"));
        ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("🟢 PASS"));
        ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem(elapsed.toString("hh:mm:ss")));
        ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("None"));

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Memory Test Passed").arg(QTime::currentTime().toString("hh:mm:ss")));
        ui->Elapsed_Time->setText((elapsed.toString("hh:mm:ss")));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    });
}

void MainWindow::RunEthernetTest()
{

   // T1 = QTime::currentTime();
    ui->Current_Test->setText("Ethernet Test");

    cur_time = QDateTime::currentDateTime().toString("hh:mm:ss");
    int Row_Count = ui->tableWidgetResults->rowCount();
    ui->tableWidgetResults->insertRow(Row_Count);

    ui->tableWidgetResults->setItem(Row_Count,0,new QTableWidgetItem("Ethernet Test"));
    ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Running.."));
    ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("..."));
    ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem("00:00:00"));
    ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("..."));

    ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing Ethernet test ").arg(cur_time));

    // Let the UI update, then schedule the completion after 2 seconds
    QTimer::singleShot(2000, this, [=]() {

        QTime elapsed(0,0);


        G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Completed"));
        ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("🟢 PASS"));
        ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem(elapsed.toString("hh:mm:ss")));
        ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("None"));

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Ethernet Test Passed").arg(QTime::currentTime().toString("hh:mm:ss")));
        ui->Elapsed_Time->setText((elapsed.toString("hh:mm:ss")));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    });

}

void MainWindow::RunGPIOTest()
{

    ui->Current_Test->setText("GPIO Test");

    cur_time = QDateTime::currentDateTime().toString("hh:mm:ss");
    int Row_Count = ui->tableWidgetResults->rowCount();
    ui->tableWidgetResults->insertRow(Row_Count);

    ui->tableWidgetResults->setItem(Row_Count,0,new QTableWidgetItem("GPIO Test"));
    ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Running.."));
    ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("..."));
    ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem("00:00:00"));
    ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("..."));

    ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing GPIO test ").arg(cur_time));

    // Let the UI update, then schedule the completion after 2 seconds
    QTimer::singleShot(2000, this, [=]() {


        QTime elapsed(0,0);


        G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Completed"));
        ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("🟢 PASS"));
        ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem(elapsed.toString("hh:mm:ss")));
        ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("None"));

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] GPIO Test Passed").arg(QTime::currentTime().toString("hh:mm:ss")));
        ui->Elapsed_Time->setText((elapsed.toString("hh:mm:ss")));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    });
}

void MainWindow::RunADCTest()
{

    ui->Current_Test->setText("ADC Test");

    cur_time = QDateTime::currentDateTime().toString("hh:mm:ss");
    int Row_Count = ui->tableWidgetResults->rowCount();
    ui->tableWidgetResults->insertRow(Row_Count);

    ui->tableWidgetResults->setItem(Row_Count,0,new QTableWidgetItem("ADC Test"));
    ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Running.."));
    ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("..."));
    ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem("00:00:00"));
    ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("..."));

    ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Executing ADC test ").arg(cur_time));

    // Let the UI update, then schedule the completion after 2 seconds
    QTimer::singleShot(2000, this, [=]() {

        QTime elapsed(0,0);

        G_PB_Value = G_PB_Value + (100/ Num_of_Tests);
        ui->OverallProgress_PB->setValue(G_PB_Value);

        ui->tableWidgetResults->setItem(Row_Count,1,new QTableWidgetItem("Completed"));
        ui->tableWidgetResults->setItem(Row_Count,2,new QTableWidgetItem("🟢 PASS"));
        ui->tableWidgetResults->setItem(Row_Count,3,new QTableWidgetItem(elapsed.toString("hh:mm:ss")));
        ui->tableWidgetResults->setItem(Row_Count,4,new QTableWidgetItem("None"));

        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] ADC Test Passed").arg(QTime::currentTime().toString("hh:mm:ss")));
        ui->Elapsed_Time->setText((elapsed.toString("hh:mm:ss")));

        G_pass_Count++;
        ui->TS_Passed_L->setNum(G_pass_Count);
    });
}

void MainWindow::on_BTN_ClearLog_clicked()
{
    ui->PTE_ApplicationLog->clear();
}



void MainWindow::on_RS_422_ChkBox_stateChanged(int arg1)
{
    if(ui->RS_422_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
    else
    {
        Num_of_Tests --;
    }

}


void MainWindow::on_Memory_ChkBox_stateChanged(int arg1)
{
    if(ui->Memory_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
    else
    {
        Num_of_Tests --;
    }
}


void MainWindow::on_Ethernet_ChkBox_stateChanged(int arg1)
{
    if(ui->Ethernet_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
    else
    {
        Num_of_Tests --;
    }
}


void MainWindow::on_GPIO_ChkBox_stateChanged(int arg1)
{
    if(ui->GPIO_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
    else
    {
        Num_of_Tests --;
    }
}


void MainWindow::on_ADC_ChkBox_stateChanged(int arg1)
{
    if(ui->ADC_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
    else
    {
        Num_of_Tests --;
    }
}

