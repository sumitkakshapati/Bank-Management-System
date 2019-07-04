#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T09:40:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = finalfinalproject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        login.cpp \
    menu.cpp \
    account_open.cpp \
    enquiry.cpp \
    statement.cpp \
    password.cpp \
    maintenance.cpp \
    ratelimit.cpp \
    deposit.cpp \
    account.cpp \
    onedaylist.cpp \
    twodaylist.cpp \
    multipleentry.cpp

HEADERS  += login.h \
    menu.h \
    account_open.h \
    enquiry.h \
    statement.h \
    password.h \
    maintenance.h \
    ratelimit.h \
    deposit.h \
    account.h \
    onedaylist.h \
    twodaylist.h \
    multipleentry.h

FORMS    += login.ui \
    menu.ui \
    account_open.ui \
    enquiry.ui \
    statement.ui \
    password.ui \
    maintenance.ui \
    ratelimit.ui \
    deposit.ui \
    onedaylist.ui \
    twodaylist.ui \
    multipleentry.ui

RESOURCES += \
    resource.qrc
