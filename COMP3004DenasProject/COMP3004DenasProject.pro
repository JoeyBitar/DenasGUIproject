#-------------------------------------------------
#
# Project created by QtCreator 2021-03-19T03:09:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = COMP3004DenasProject
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
        allergy.cpp \
        controller.cpp \
        head.cpp \
        hypotonia.cpp \
        main.cpp \
        mainwindow.cpp \
        recording.cpp \
        seventysevenhz.cpp \
        sixtyhz.cpp \
        tenhz.cpp \
        throat.cpp \
        treatment.cpp \
        twentyhz.cpp

HEADERS += \
        allergy.h \
        controller.h \
        head.h \
        hypotonia.h \
        mainwindow.h \
        recording.h \
        seventysevenhz.h \
        sixtyhz.h \
        tenhz.h \
        throat.h \
        treatment.h \
        twentyhz.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
