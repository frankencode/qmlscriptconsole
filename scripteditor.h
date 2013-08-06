#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QDeclarativeItem>
#include <QPointer>

class ConsoleWindow;

class ScriptEditor: public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    ScriptEditor(QDeclarativeItem *parent = 0);
    ~ScriptEditor();

    QString title() const;
    void setTitle(const QString &title);

signals:
    void submitted(const QString &text);
    void titleChanged(const QString &);
    void logList(const QStringList &list);
    void clear();

private:
    QPointer<ConsoleWindow> window_;
    QString title_;
};

#endif // SCRIPTEDITOR_H
