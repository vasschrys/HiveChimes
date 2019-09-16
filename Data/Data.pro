TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    datadecoder.cpp \
    datacontainer.cpp \
    #datagenerator.cpp \
    beegeneration.cpp

HEADERS += \
    datadecoder.h \
    datacontainer.h \
   # datagenerator.h \
    beegeneration.h

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
