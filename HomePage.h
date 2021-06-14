#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>

class MainWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

class HomePage : public QMainWindow {
  Q_OBJECT
public:
  HomePage(QWidget *parent = nullptr);
  ~HomePage();

  void setMainWindow(MainWindow* window);

  void onLogoutClicked();
  void goToLoginPage();

private:
  Ui::HomePage *ui;

  MainWindow* m_mainWindow;
};

#endif // HOMEPAGE_H
