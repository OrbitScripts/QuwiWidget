#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QtWaitingSpinner/waitingspinnerwidget.h"
#include "NetworkManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void onLoginButtonClicked();
  void onFinishRequest(const QString& url, const QString& error);

private:
  Ui::MainWindow *ui;
  WaitingSpinnerWidget* m_spinner;
  NetworkManager m_networkManager;
};
#endif // MAINWINDOW_H
