QT       += core gui
QT += core
QT += widgets

QT += multimedia
QT += network
QT += uitools
QT += websockets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Drunk.cpp \
    bomb.cpp \
    bullet.cpp \
    dog.cpp \
    enemy1.cpp \
    flyingbullet.cpp \
    gamemanager.cpp \
    homepage.cpp \
    level.cpp \
    level1.cpp \
    level2.cpp \
    level3.cpp \
    log_in.cpp \
    main.cpp \
    mainwindow.cpp \
    franklin.cpp \
    onlineflyingbullet.cpp \
    onlinegamemanager.cpp \
    onlinelevel.cpp \
    onlineplayer.cpp \
    pellet.cpp \

HEADERS += \
    Drunk.h \
    bomb.h \
    bullet.h \
    dog.h \
    enemy1.h \
    flyingbullet.h \
    gamemanager.h \
    homepage.h \
    level.h \
    level1.h \
    level2.h \
    level3.h \
    log_in.h \
    mainwindow.h \
    franklin.h \
    onlineflyingbullet.h \
    onlinegamemanager.h \
    onlinelevel.h \
    onlineplayer.h \
    pellet.h

FORMS += \
    homepage.ui \
    log_in.ui \
    mainwindow.ui \
    onlinegameid.ui \
    onlinegamewaiting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    ui.qrc

