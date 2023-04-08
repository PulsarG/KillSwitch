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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("KillSwith");
//  ui->exeName->setPlaceholderText("Name exe file for kill without .exe");

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
  --sec;
  QString s = QString::number(sec);
  ui->lbl1->setText("Update " + s);

  if (sec == 0) {
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

  if (ui->timerSet->value() == 0) {
    sec = 15;
    timerUpdate->start(1000);
  } else {
    sec = ui->timerSet->value() * 60;
    timerUpdate->start(1000);
  } // end if
  qDebug() << ui->exeName->text();
}

void MainWindow::on_pushButton_clicked() {
  ui->pushButton->setStyleSheet("background-color: green");
  int time = ui->timerSet->value();
  if (time == 0) {
    sec = 15;
    timerUpdate->start(1000);
    timer->start(15000);
  } else {
    sec = ui->timerSet->value() * 60;
    timerUpdate->start(1000);
    timer->start(time * 1000 * 60);
  }
}

void MainWindow::on_btnStop_clicked() {
  timer->stop();
  ui->pushButton->setStyleSheet("background-color: none");
}

void MainWindow::on_btnOpenFile_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, "Выбрать программу для закрытия", "C:\\", "EXE (*.exe)");
  QFileInfo fileInfo(filePath);
  QString fileName = fileInfo.fileName();
  ui->exeName->setText(fileName);
}
