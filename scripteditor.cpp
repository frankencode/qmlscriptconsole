#include "consolewindow.h"
#include "scripteditor.h"

ScriptEditor::ScriptEditor(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      window_(new ConsoleWindow)
{
    connect(this, SIGNAL(titleChanged(const QString &)), window_, SLOT(setWindowTitle(const QString &)));
    connect(window_, SIGNAL(submitted(const QString &)), this, SIGNAL(submitted(const QString &)));
    connect(this, SIGNAL(logList(const QStringList &)), window_, SLOT(log(const QStringList &)));
    connect(this, SIGNAL(clear()), window_, SLOT(clear()));
    window_->setAttribute(Qt::WA_DeleteOnClose);
    window_->show();
}

ScriptEditor::~ScriptEditor()
{
    if (window_)
        window_->close();
}

QString ScriptEditor::title() const
{
    return title_;
}

void ScriptEditor::setTitle(const QString &title)
{
    title_ = title;
    emit titleChanged(title_);
}
