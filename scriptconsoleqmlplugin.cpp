#include "scripteditor.h"
#include "scriptconsoleqmlplugin.h"

Q_EXPORT_PLUGIN2(qmlscriptconsoleqmlplugin, ScriptConsoleQmlPlugin);

void ScriptConsoleQmlPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == "com.nokia.ScriptConsole");
    qmlRegisterType<ScriptEditor>(uri, 1, 0, "ScriptEditor");
}
