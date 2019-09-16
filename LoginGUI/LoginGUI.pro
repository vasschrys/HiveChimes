#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T11:24:51
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoginGUI
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
        main.cpp \
        mainwindow.cpp \
    secondwindow.cpp \
    secondwindowresearcher.cpp \
    createmodel.cpp \
    userselectmodel.cpp \
    generatedmodel.cpp \
    #linegraph.cpp \
   # bargraph.cpp \
    ../Graphics/mainwindowanimate.cpp \
    ../Graphics/animatedbee.cpp\
    ../Graphics/animationboard.cpp \
    ../Graphics/framework.cpp \
    intro.cpp  \
    ../RealTimeStream/mainwindowrt.cpp \
    ../GUI/bees.cpp \
    ../GUI/chart.cpp \
    ../GUI/chartview.cpp


HEADERS += \
        mainwindow.h \
    secondwindow.h \
    secondwindowresearcher.h \
    createmodel.h \
    userselectmodel.h \
    generatedmodel.h \
   # linegraph.h \
   # bargraph.h \
    ../Graphics/mainwindowanimate.h \
    ../Graphics/animatedbee.h\
    ../Graphics/animationboard.h \
    ../Graphics/framework.h \
    intro.h \
    ../RealTimeStream/mainwindowrt.h \
    ../GUI/bees.h \
    ../GUI/chart.h \
    ../GUI/chartview.h




FORMS += \
        mainwindow.ui \
    secondwindow.ui \
    secondwindowresearcher.ui \
    createmodel.ui \
    selectmodel.ui \
    userselectmodel.ui \
    generatedmodel.ui \
   # linegraph.ui \
   # bargraph.ui \
    ../Graphics/mainwindowanimate.ui \
    intro.ui \
    ../RealTimeStream/mainwindowrt.ui \
    ../GUI/bees.ui



HEADERS += ../Data/beegeneration.h
SOURCES += ../Data/beegeneration.cpp

HEADERS += ../Data/datadecoder.h
SOURCES += ../Data/datadecoder.cpp

HEADERS += ../Data/datacontainer.h
SOURCES += ../Data/datacontainer.cpp

HEADERS += ../Database/dbtable.h
SOURCES += ../Database/dbtable.cpp

HEADERS += ../Database/tool.h
SOURCES += ../Database/tool.cpp

HEADERS += ../Database/dbhivetable.h
SOURCES += ../Database/dbhivetable.cpp

HEADERS += ../Database/dbmodeltable.h
SOURCES += ../Database/dbmodeltable.cpp

HEADERS += ../Database/dbbeelog.h
SOURCES += ../Database/dbbeelog.cpp
LIBS += -lsqlite3

RESOURCES += \
    ../Graphics/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
