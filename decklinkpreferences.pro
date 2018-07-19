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


INCLUDEPATH += $${SDK_PATH}

SOURCES += main.cpp \
        $${SDK_PATH}/DeckLinkAPIDispatch.cpp

HEADERS +=

LIBS += -ldl
