#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_networkManager(parent)
{
  ui->setupUi(this);

  m_emailError = new QLabel(this);
  m_emailError->setStyleSheet("color: red; background-color: transparent;");
  m_emailError->setIndent(16);

  m_spinner = new WaitingSpinnerWidget(this);
  m_spinner->setParent(ui->loginButton);
  m_spinner->setInnerRadius(5);
  m_spinner->setLineWidth(1);

  connect(ui->loginButton, &QPushButton::pressed,
          this, &MainWindow::onLoginButtonClicked);
  connect(&m_networkManager, &NetworkManager::finishRequest,
          this, &MainWindow::onFinishRequest);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showEmailError(const QString& message) {
  m_emailError->setGeometry(ui->emailField->x(),
                            ui->emailField->y() - 5,
                            m_emailError->width(),
                            m_emailError->height());

  m_emailError->setText(message);
  QString style = ui->emailField->styleSheet();
  style += "\n border: 1px solid red;}";
  ui->emailField->setStyleSheet(style);
}

void MainWindow::hideEmailError() {
  m_emailError->setText("");
  QString style = ui->emailField->styleSheet();
  style.replace("\n border: 1px solid red;}", "");
  ui->emailField->setStyleSheet(style);
}

void MainWindow::onLoginButtonClicked() {
  QString email = ui->emailField->text();
  QString password = ui->passwordField->text();

  ui->loginButton->setText("");
  m_spinner->start();
  m_networkManager.loginRequest(email, password);
}

void MainWindow::onFinishRequest(const QString& url, const QString& error) {
  if (url == m_networkManager.loginUrl()) {
    ui->loginButton->setText("Login");
    m_spinner->stop();
  }
}

