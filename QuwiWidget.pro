QT += core gui widgets network

CONFIG += c++14

SOURCES += \
    LinkLabel.cpp \
    NetworkManager.cpp \
    QtWaitingSpinner/waitingspinnerwidget.cpp \
    main.cpp \
    MainWindow.cpp \
    DataLayer/Project.cpp

HEADERS += \
    LinkLabel.h \
    MainWindow.h \
    NetworkManager.h \
    DataLayer/Project.h \
    QtWaitingSpinner/waitingspinnerwidget.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
