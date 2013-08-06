TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

DESTDIR = com/nokia/ScriptConsole
TARGET = qmlmediaflowplugin

HEADERS += \
    scripteditor.h \
    scriptconsoleqmlplugin.h \
    consolewindow.h

SOURCES += \
    scripteditor.cpp \
    scriptconsoleqmlplugin.cpp \
    consolewindow.cpp
