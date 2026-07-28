#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;






private slots:
    void on_Run_Btn_clicked();

    void on_BTN_ClearLog_clicked();

    void on_RS_422_ChkBox_stateChanged(int arg1);

    void on_Memory_ChkBox_stateChanged(int arg1);

    void on_Ethernet_ChkBox_stateChanged(int arg1);

    void on_GPIO_ChkBox_stateChanged(int arg1);

    void on_ADC_ChkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void RunRS422Test();
    void RunMemoryTest();
    void RunEthernetTest();
    void RunGPIOTest();
    void RunADCTest();
};
#endif // MAINWINDOW_H
