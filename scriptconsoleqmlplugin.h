#ifndef SCRIPTCONSOLEQMLPLUGIN_H
#define SCRIPTCONSOLEQMLPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class ScriptConsoleQmlPlugin: public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri);
};

#endif // SCRIPTCONSOLEQMLPLUGIN_H
