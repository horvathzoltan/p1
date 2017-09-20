#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T08:35:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT           += sql
QT += webenginewidgets

TARGET = p1
TEMPLATE = app


SOURCES += main.cpp \
    zAbstractModel.cpp \
    zsql.cpp \
    zentity.cpp \
    zfield.cpp \
    ztipus.cpp \
    mainwindow.cpp \
    zproperty.cpp \
    masterdataform.cpp \
    propertysheet.cpp \
    zstringhelper.cpp \
    zexception.cpp \
    zspinbox.cpp \
    zitemeditorfactory.cpp \
    globals.cpp \
    helpform.cpp \
    zoperation.cpp \
    zadminnode.cpp \
    masterdata.cpp \
    zuser.cpp

HEADERS  += \
    zAbstractModel.h \
    zentity.h \
    zsql.h \
    zfield.h \
    zvalidation.h \
    zexception.h \
    ztipus.h \
    mainwindow.h \
    masterdata.h \
    zproperty.h \
    zlistitem.h \
    masterdataform.h \
    propertysheet.h \
    zstringhelper.h \
    zglobal.h \
    zalgorithms.h \
    zspinbox.h \
    zitemeditorfactory.h \
    globals.h \
    helpform.h \
    zoperation.h \
    zadminnode.h \
    zuser.h

FORMS    += mainwindow.ui \
    propertysheet.ui \
    helpform.ui \
    masterdataform.ui

DISTFILES += \
    ToDo.txt \
    Entity.txt


LIBS += -L$$PWD/../../mysql/lib/ -lmysqlcppconn

INCLUDEPATH += $$PWD/../../mysql/include
DEPENDPATH += $$PWD/../../mysql/include

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wall
# QMAKE_CXXFLAGS += -Wno-missing-field-initializers

RESOURCES += \
    resource1.qrc

