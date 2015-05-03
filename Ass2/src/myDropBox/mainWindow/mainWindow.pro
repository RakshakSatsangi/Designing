#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T18:08:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainWindow
TEMPLATE = app

LIBS += -lssl -lcrypto

SOURCES += main.cpp\
        mainwindow.cpp \
    loginsuccesswindow.cpp \
    global.cpp \
    enternamedialog.cpp \
    sharedialog.cpp

HEADERS  += mainwindow.h \
    loginsuccesswindow.h \
    global.h \
    enternamedialog.h \
    sharedialog.h

FORMS    += mainwindow.ui \
    loginsuccesswindow.ui \
    enternamedialog.ui \
    sharedialog.ui
