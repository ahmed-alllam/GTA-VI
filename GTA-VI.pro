QT       += core gui
QT += widgets
#QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Drunk.cpp \
    bullet.cpp \
    enemy1.cpp \
    enemy2.cpp \
    gamemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    franklin.cpp \
    pellet.cpp

HEADERS += \
    Drunk.h \
    bullet.h \
    enemy1.h \
    enemy2.h \
    gamemanager.h \
    mainwindow.h \
    franklin.h \
    pellet.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
