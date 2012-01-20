#-------------------------------------------------
#
# Project created by QtCreator 2012-01-19T20:22:18
#
#-------------------------------------------------

QT       += core gui

TARGET = ClientGui
TEMPLATE = app

INCLUDEPATH += . \
            /usr/include/boost

LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -lboost_thread

SOURCES += ../src/main.cpp\
            ../src/mainwindow.cpp\
            ../src/Room.cpp\
            ../src/Server.cpp\
            ../src/Session.cpp\
            ../src/Message.cpp\
            ../src/Client.cpp\
            ../src/SocketSingleton.cpp

HEADERS  += ../include/mainwindow.h
