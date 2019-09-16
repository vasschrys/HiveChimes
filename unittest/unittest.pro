TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \

### add the following lines

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread

SOURCES += ../gtest/googletest/src/gtest-all.cc

INCLUDEPATH +=  ../gtest                                   \
                ../gtest/googletest                        \
                ../gtest/googletest/include                \
                ../gtest/googletest/include/gtest


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


HEADERS += ../Data/beegeneration.h
SOURCES += ../Data/beegeneration.cpp

HEADERS += ../Data/datagenerator.h
SOURCES += ../Data/datagenerator.cpp

HEADERS += ../Data/datadecoder.h
SOURCES += ../Data/datadecoder.cpp

HEADERS += ../Data/datacontainer.h
SOURCES += ../Data/datacontainer.cpp
