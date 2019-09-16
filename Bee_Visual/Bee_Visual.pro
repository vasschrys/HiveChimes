TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp\
        engine.cpp \
    bees.cpp

HEADERS +=\
    engine.h \
    bees.h

QT += gui

QTPLUGIN += qjpeg \
    qgif \
    qtiff


