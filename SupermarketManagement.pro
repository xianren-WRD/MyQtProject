#-------------------------------------------------
#
# Project created by QtCreator 2020-07-20T09:57:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SupermarketManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Sources/administratorwindow.cpp \
    Sources/cargomanagementwindow.cpp \
    Sources/cargowindow.cpp \
    Sources/commodity.cpp \
    Sources/dataprocessing.cpp \
    Sources/employee.cpp \
    Sources/loginwindow.cpp \
    Sources/main.cpp \
    Sources/registrationwindow.cpp \
    Sources/shoppingwindow.cpp \
    Sources/staffmanagementwindow.cpp \
    Sources/staffwindow.cpp \
    Sources/supermarketmanagement.cpp

HEADERS += \
    Headers/administratorwindow.h \
    Headers/cargomanagementwindow.h \
    Headers/cargowindow.h \
    Headers/commodity.h \
    Headers/dataprocessing.h \
    Headers/employee.h \
    Headers/loginwindow.h \
    Headers/registrationwindow.h \
    Headers/shoppingwindow.h \
    Headers/staffmanagementwindow.h \
    Headers/staffwindow.h \
    Headers/supermarketmanagement.h

FORMS += \
    Forms/administratorwindow.ui \
    Forms/cargomanagementwindow.ui \
    Forms/cargowindow.ui \
    Forms/loginwindow.ui \
    Forms/registrationwindow.ui \
    Forms/shoppingwindow.ui \
    Forms/staffmanagementwindow.ui \
    Forms/staffwindow.ui \
    Forms/supermarketmanagement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
