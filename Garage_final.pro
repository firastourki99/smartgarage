QT       += core gui sql printsupport network
QT       += sql
QT       += core gui charts
QT       += core gui  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    carte.cpp \
    client.cpp \
    connection.cpp \
    dialog.cpp \
    dialog2.cpp \
    dialog_email.cpp \
    employe.cpp \
    mailing_sercice.cpp \
    main.cpp \
    mainwindow.cpp \
    notifications.cpp \
    service.cpp \
    smtp.cpp \
    stat_combo.cpp \
    voiture.cpp

HEADERS += \
    arduino.h \
    carte.h \
    client.h \
    connection.h \
    dialog.h \
    dialog2.h \
    dialog_email.h \
    employe.h \
    mailing_sercice.h \
    mainwindow.h \
    notifications.h \
    service.h \
    smtp.h \
    stat_combo.h \
    voiture.h

FORMS += \
    dialog.ui \
    dialog2.ui \
    dialog_email.ui \
    mailing_sercice.ui \
    mainwindow.ui \
    stat_combo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
