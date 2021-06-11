#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_networkManager(parent)
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
  QString email = ui->emailField->text();
  QString password = ui->passwordField->text();

  //m_networkManager.loginRequest(email, password);
}

