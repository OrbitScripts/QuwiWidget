#include "HomePage.h"
#include "ui_HomePage.h"

#include "MainWindow.h"

HomePage::HomePage(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::HomePage)
{
  ui->setupUi(this);

  connect(ui->logoutButton, &QPushButton::pressed,
          this, &HomePage::onLogoutClicked);
}

HomePage::~HomePage()
{
  delete ui;
}

void HomePage::setMainWindow(MainWindow* window) {
  m_mainWindow = window;
}

void HomePage::onLogoutClicked() {
  m_mainWindow->logout();
  goToLoginPage();
}

void HomePage::goToLoginPage() {
  hide();
  m_mainWindow->show();
}
