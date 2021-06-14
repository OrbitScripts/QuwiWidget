#include "MainWindow.h"
#include "HomePage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  HomePage homePage;

  MainWindow mainWindow;
  mainWindow.setHomePage(&homePage);
  mainWindow.show();

  homePage.setMainWindow(&mainWindow);

  return a.exec();
}
