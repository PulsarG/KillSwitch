#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void delayedFunction();
    void showTimeLabel();

    void on_pushButton_clicked();
    void on_btnStop_clicked();

    void on_pushButton_2_clicked();

  private:
    Ui::MainWindow *ui;
//    int secInt;

    QTimer *timer;
    QTimer *timerUpdate;
};
#endif // MAINWINDOW_H
