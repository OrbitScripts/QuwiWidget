#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "HomePage.h"

#include "QtWaitingSpinner/waitingspinnerwidget.h"
#include "NetworkManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void setHomePage(HomePage* page);

  void logout();

private:
  void showEmailError(const QString& message);
  void hideEmailError();

  void showPasswordError(const QString& message);
  void hidePasswordError();

  void startBusyIndicator();
  void stopBusyIndicator();

  void onEmailOrPasswordTextChanged();

  void goToHomePage();

  void onLoginButtonClicked();
  void onFinishRequest(const QString& url, const QString& error);

private:
  Ui::MainWindow *ui;
  HomePage* m_homePage;

  WaitingSpinnerWidget* m_spinner;
  QLabel* m_emailError;
  QLabel* m_passwordError;
  NetworkManager m_networkManager;
};
#endif // MAINWINDOW_H
