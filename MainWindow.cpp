#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_networkManager(parent)
{
  ui->setupUi(this);

  m_emailError = new QLabel(this);
  m_emailError->setStyleSheet("color: red; background-color: transparent;");
  m_emailError->setIndent(16);

  m_passwordError = new QLabel(this);
  m_passwordError->setStyleSheet(m_emailError->styleSheet());
  m_passwordError->setIndent(16);

  m_spinner = new WaitingSpinnerWidget(this);
  m_spinner->setParent(ui->loginButton);
  m_spinner->setInnerRadius(5);
  m_spinner->setLineWidth(1);

  connect(ui->loginButton, &QPushButton::pressed,
          this, &MainWindow::onLoginButtonClicked);

  connect(&m_networkManager, &NetworkManager::finishRequest,
          this, &MainWindow::onFinishRequest);

  connect(ui->emailField, &QLineEdit::textChanged,
          this, &MainWindow::onEmailOrPasswordTextChanged);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setHomePage(HomePage* page) {
  m_homePage = page;
}

void MainWindow::logout() {
  m_networkManager.logoutRequest();
}

void MainWindow::showEmailError(const QString& message) {
  m_emailError->setGeometry(ui->emailField->x(),
                            ui->emailField->y() - 6,
                            ui->emailField->width(),
                            m_emailError->height());

  m_emailError->setText(message);
  QString style = ui->emailField->styleSheet();
  style += "\n border: 1px solid red;";
  ui->emailField->setStyleSheet(style);
}

void MainWindow::hideEmailError() {
  m_emailError->setText("");
  QString style = ui->emailField->styleSheet();
  style.replace("\n border: 1px solid red;", "");
  ui->emailField->setStyleSheet(style);
}

void MainWindow::showPasswordError(const QString& message) {
  m_passwordError->setGeometry(ui->passwordField->x(),
                               ui->passwordField->y() - 6,
                               ui->passwordField->width(),
                               m_passwordError->height());

  m_passwordError->setText(message);
  QString style = ui->passwordField->styleSheet();
  style += "\n border: 1px solid red;";
  ui->passwordField->setStyleSheet(style);
}

void MainWindow::hidePasswordError() {
  m_passwordError->setText("");
  QString style = ui->passwordField->styleSheet();
  style.replace("\n border: 1px solid red;", "");
  ui->passwordField->setStyleSheet(style);
}

void MainWindow::startBusyIndicator() {
  ui->loginButton->setText("");
  m_spinner->start();
}

void MainWindow::stopBusyIndicator() {
  ui->loginButton->setText("Login");
  m_spinner->stop();
}

void MainWindow::onEmailOrPasswordTextChanged() {
  hideEmailError();
  hidePasswordError();
}

void MainWindow::goToHomePage() {
  hide();
  m_homePage->show();
}

void MainWindow::onLoginButtonClicked() {
  QRegExp mailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
  mailRegEx.setCaseSensitivity(Qt::CaseInsensitive);

  QString email = ui->emailField->text();
  if (email.isEmpty() || !mailRegEx.exactMatch(email)) {
    showEmailError("Email is not a valid email address.");
    return;
  }

  QString password = ui->passwordField->text();
  if (password.isEmpty()) {
    showPasswordError("Password can not be blank.");
    return;
  }

  startBusyIndicator();
  m_networkManager.loginRequest(email, password);
}

void MainWindow::onFinishRequest(const QString& url, const QString& error) {
  if (url == m_networkManager.loginUrl()) {
    if (!error.isEmpty()) {
      showEmailError(error);
    } else {
      goToHomePage();
    }

    stopBusyIndicator();
  }
}

