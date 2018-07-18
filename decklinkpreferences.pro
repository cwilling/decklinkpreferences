#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T09:37:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = decklinkpreferences
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += $HOME/pixelizator/bmdtools/Linux/include

SOURCES += main.cpp \
        $HOME/pixelizator/bmdtools/Linux/include/DeckLinkAPIDispatch.cpp

HEADERS +=

LIBS += -ldl
