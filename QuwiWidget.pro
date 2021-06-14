QT += core gui widgets network

CONFIG += c++14

SOURCES += \
    HomePage.cpp \
    LinkLabel.cpp \
    NetworkManager.cpp \
    QtWaitingSpinner/waitingspinnerwidget.cpp \
    main.cpp \
    MainWindow.cpp \
    DataLayer/Project.cpp

HEADERS += \
    HomePage.h \
    LinkLabel.h \
    MainWindow.h \
    NetworkManager.h \
    DataLayer/Project.h \
    QtWaitingSpinner/waitingspinnerwidget.h

FORMS += \
    HomePage.ui \
    MainWindow.ui

RESOURCES += \
    images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
