#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <future>
#include <thread>

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

int sec;
int timerUpdateSec;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("KillSwith");

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(delayedFunction()));

  timerUpdate = new QTimer(this);
  connect(timerUpdate, SIGNAL(timeout()), this, SLOT(showTimeLabel()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete timer;
  delete timerUpdate;
}

void MainWindow::showTimeLabel() {
  --timerUpdateSec;
  QString s = QString::number(timerUpdateSec);
  ui->lbl1->setText("Update " + s);

  if (timerUpdateSec == 0) {
    timerUpdate->stop();
  }
}

void MainWindow::delayedFunction() {
  QString host = "8.8.8.8";
  QString program = "ping";
  QStringList arguments;
  arguments << host << "-n"
            << "1"
            << "-w"
            << "1000";
  QProcess process;
  process.start(program, arguments);
  process.waitForFinished();
  int exitCode = process.exitCode();

  if (exitCode == 0) { // * if
    ui->lbl1->setText("Internet connection is available");
  } else {
    if (ui->exeName->text() != "") { // ** if
      QString program = "taskkill";
      QStringList arguments;
      arguments << "/F"
                << "/IM" << ui->exeName->text();
      QProcess::execute(program, arguments);

      this->ui->lbl1->setText("INTERNET IS OFF");
      ui->pushButton->setStyleSheet("background-color: red");
    } // ** end  if
  }   // * end if

  timerUpdateSec = sec;
  timerUpdate->start(1000);
}

void MainWindow::on_pushButton_clicked() {
  ui->pushButton->setStyleSheet("background-color: green");
  int timeMinuts = ui->timerSet->value();
  int timeSeconds = ui->setSeconds->value();
  ui->setSeconds->setMaximum(59);

  if (timeMinuts == 0 && timeSeconds == 0) {
    sec = 15;
    timerUpdateSec = sec;
    timerUpdate->start(1000);
    timer->start(15000);
  } else {

    int finalTimer = (timeMinuts * 60) + timeSeconds;

    sec = finalTimer;
    timerUpdateSec = sec;
    timerUpdate->start(1000);
    timer->start(finalTimer * 1000);
  }
}

void MainWindow::on_btnStop_clicked() {
  timer->stop();
  timerUpdate->stop();
  ui->lbl1->setText("Stop");
  ui->pushButton->setStyleSheet("background-color: none");
}

void MainWindow::on_btnOpenFile_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, "Выбрать программу для закрытия", "C:\\", "EXE (*.exe)");
  QFileInfo fileInfo(filePath);
  QString fileName = fileInfo.fileName();
  ui->exeName->setText(fileName);
}
