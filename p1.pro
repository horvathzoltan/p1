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
    TypeHelper.cpp \
    filenamehelper.cpp \
    filetypehelper.cpp \
    #isettings.cpp \
    inihelper.cpp \
    project.cpp \
    sqlhelper.cpp \
    zAbstractModel.cpp \
    zsettings.cpp \
    #zsettingshelper.cpp \
    ztablerow.cpp \
    mainwindow.cpp \
    zproperty.cpp \
    masterdataform.cpp \
    propertysheet.cpp \
    #zstringhelper.cpp \
    zexception.cpp \
    zspinbox.cpp \
    zitemeditorfactory.cpp \
    globals.cpp \
    helpform.cpp \
    zoperation.cpp \
    zadminnode.cpp \
    masterdata.cpp \
    zuser.cpp \
    ztable.cpp \
    #zlogicexception.cpp

HEADERS  += \
    TypeHelper.h \
    filenamehelper.h \
    filetypehelper.h \
    #isettings.h \
    inihelper.h \
    project.h \
    sqlhelper.h \
    zAbstractModel.h \
    zsettings.h \
    #zsettingshelper.h \
    ztablerow.h \
    zvalidation.h \
    zexception.h \
    mainwindow.h \
    masterdata.h \
    zproperty.h \
    zlistitem.h \
    masterdataform.h \
    propertysheet.h \
    #zstringhelper.h \
    zglobal.h \
    zalgorithms.h \
    zspinbox.h \
    zitemeditorfactory.h \
    globals.h \
    helpform.h \
    zoperation.h \
    zadminnode.h \
    zuser.h \
    ztable.h \
    #zmacro.h \
    #zlogicexception.h

FORMS    += mainwindow.ui \
    propertysheet.ui \
    helpform.ui \
    masterdataform.ui

DISTFILES += \
    ToDo.txt \
    Entity.txt \
    settings.ini

HOME = $$system(echo $HOME)
COMMON_LIBS = commonlib

LIBS += -L$$PWD/../../mysql/lib/ -lmysqlcppconn

INCLUDEPATH += $$PWD/../../mysql/include
DEPENDPATH += $$PWD/../../mysql/include

#unix:!macx: LIBS += -L/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper/ -lstringhelper
unix:!macx:
{   
LIBS += -L$$HOME/$$COMMON_LIBS/ -lstringhelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lfilehelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lzlog
LIBS += -L$$HOME/$$COMMON_LIBS/ -lmacrofactory
LIBS += -L$$HOME/$$COMMON_LIBS/ -lshortguid
LIBS += -L$$HOME/$$COMMON_LIBS/ -linihelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lsettingshelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lxmlhelper
}

QMAKE_LFLAGS += -Wl,-rpath,"/$$HOME/$$COMMON_LIBS"
#QMAKE_LFLAGS += -Wl,-rpath,"/$$HOME/$$INSTALLDIR/macrofactory"
#QMAKE_LFLAGS += -Wl,-rpath,"/home/zoli/build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"/home/zoli/build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/macrofactory"
#QMAKE_LFLAGS += -Wl,-rpath,"/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/macrofactory"
INCLUDEPATH += /$$HOME/common
DEPENDPATH += /$$HOME/common


QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wall
# QMAKE_CXXFLAGS += -Wno-missing-field-initializers

RESOURCES += \
    resource1.qrc

message($$OUT_PWD)

copydata.commands = $(COPY_DIR) $$PWD/settings.ini $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata





