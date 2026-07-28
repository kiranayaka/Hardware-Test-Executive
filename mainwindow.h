#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Tests/testresult.h"

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


private:
    Ui::MainWindow *ui;

    void UpdateTestUI(const QString& testName,
                      const TestResult& result,
                      int row);
};
#endif // MAINWINDOW_H
