QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base/SchTasks.cpp \
    base/SysBasic.cpp \
    base/TskExec.cpp \
    main.cpp \
    ui/DlgAbout.cpp \
    ui/mainwindow.cpp \
    ui/preui.cpp \
    ui/showlicence.cpp

HEADERS += \
    hppframe.h \
    ui/DlgAbout.h \
    ui/mainwindow.h \
    ui/preui.h \
    ui/showlicence.h

FORMS += \
    ui/DlgAbout.ui \
    ui/mainwindow.ui \
    ui/preui.ui \
    ui/showlicence.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
