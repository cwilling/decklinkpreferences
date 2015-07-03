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


INCLUDEPATH += /usr/include/decklink

SOURCES += main.cpp \
        /usr/include/decklink/DeckLinkAPIDispatch.cpp

HEADERS +=

LIBS += -ldl
