#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new Model),
    thread(new QThread)
{
  ui->setupUi(this);

  model->moveToThread(thread);
  connect(this, &MainWindow::command, model, &Model::command,
          Qt::DirectConnection);
  connect(model, &Model::displayUpdate, this, &MainWindow::update);
  connect(thread, &QThread::started, model, &Model::update);

  connect(this, &MainWindow::command, model, &Model::command);
  connect(ui->pushButtonUp, &QPushButton::clicked, [&](){
    emit command(Up);
  });
  connect(ui->pushButtonDown, &QPushButton::clicked, [&](){
    emit command(Down);
  });
  connect(ui->pushButtonEnter, &QPushButton::clicked, [&](){
    emit command(Enter);
  });
  connect(ui->pushButtonOnOff, &QPushButton::clicked, [&](){
    emit command(Enable);
  });

  thread->start();
}

void MainWindow::update(Display &display) {
  ui->lcd1->display(display.valueAt(0));
  ui->lcd2->display(display.valueAt(1));
  ui->lcd3->display(display.valueAt(2));
  ui->lcd4->display(display.valueAt(3));
  ui->dot->setText("");
  if (display.isDotted()) {
    static auto yellow = QString("background-color: green;"
                                 "width: 18px;"
                                 "color:yellow;"
                                 "border-radius: 9px;");
    ui->dot->setStyleSheet(yellow);
  }
  else ui->dot->setStyleSheet("");
}

MainWindow::~MainWindow()
{
  delete ui;
}

