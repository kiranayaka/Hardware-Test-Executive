#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QThread>
#include <QTimer>




/*-----Global variable-----*/
QString cur_time , cur_time2 ;
float G_PB_Value = 0.0;//Global Progress Bar Value
int G_pass_Count = 0;//Global Pass Count
int G_Fail_Count = 0;//Global Fail Count
QTime T1 , T2 ;//Time 1 , Time 2
QTime elapsed(0,0);//Time taken / Difference in time
qint64 diffSeconds =0;   // difference in seconds
qint64 diffMillis =0;  // difference in milliseconds
int Num_of_Tests = 0 ;


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
    ui->OverallProgress_PB->setValue(G_PB_Value);
    ui->TS_Passed_L->setNum(G_pass_Count);
    ui->Conn_Status->setText("🟢 Connected");
   // ui->PTE_ApplicationLog->clear();
   /*   ui->Conn_Status->setText("🟢 Connected");

        ui->Current_Test->setText("RS422 Loopback");

        ui->OverallProgress_PB->setValue(10);

        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->PTE_ApplicationLog->appendPlainText(QString("[%1] Starting test execution...").arg(time));
    */



        if(ui->RS_422_ChkBox->isChecked())
        {
            RunRS422Test();
        }

        if(ui->Memory_ChkBox->isChecked())
        {
            RunMemoryTest();
        }

        if(ui->Ethernet_ChkBox->isChecked())
        {
            RunEthernetTest();
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



void MainWindow::RunRS422Test()
{
    T1 = QTime::currentTime();
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
    QTimer::singleShot(2000, this, [=]() {
        T2 = QTime::currentTime();
        int diffSeconds = T1.secsTo(T2);
        int diffMillis  = T1.msecsTo(T2);

        QTime elapsed(0,0);
        elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


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
    T1 = QTime::currentTime();
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
        T2 = QTime::currentTime();
        int diffSeconds = T1.secsTo(T2);
        int diffMillis  = T1.msecsTo(T2);

        QTime elapsed(0,0);
        elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


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

    T1 = QTime::currentTime();
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
        T2 = QTime::currentTime();
        int diffSeconds = T1.secsTo(T2);
        int diffMillis  = T1.msecsTo(T2);

        QTime elapsed(0,0);
        elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


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
    T1 = QTime::currentTime();
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
        T2 = QTime::currentTime();
        int diffSeconds = T1.secsTo(T2);
        int diffMillis  = T1.msecsTo(T2);

        QTime elapsed(0,0);
        elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


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
    T1 = QTime::currentTime();
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
        T2 = QTime::currentTime();
        int diffSeconds = T1.secsTo(T2);
        int diffMillis  = T1.msecsTo(T2);

        QTime elapsed(0,0);
        elapsed = elapsed.addSecs(diffSeconds).addMSecs(diffMillis);


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

}


void MainWindow::on_Memory_ChkBox_stateChanged(int arg1)
{
    if(ui->Memory_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
}


void MainWindow::on_Ethernet_ChkBox_stateChanged(int arg1)
{
    if(ui->Ethernet_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
}


void MainWindow::on_GPIO_ChkBox_stateChanged(int arg1)
{
    if(ui->GPIO_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
}


void MainWindow::on_ADC_ChkBox_stateChanged(int arg1)
{
    if(ui->ADC_ChkBox->isChecked()== true)
    {
        Num_of_Tests ++;
    }
}

