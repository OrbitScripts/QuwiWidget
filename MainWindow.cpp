#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->loginButton, &QPushButton::pressed,
          this, &MainWindow::onLoginButtonClicked);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onLoginButtonClicked() {
  qDebug() << "onLoginButtonClicked";
}

