#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QAction>
#include <QLayout>
#include <QDebug> // DEBUG
#include "consolewindow.h"

ConsoleWindow::ConsoleWindow()
    : QDialog(findParentWindow()),
      historyPos(0)
{
    output = new QPlainTextEdit;
    output->setReadOnly(true);
    input = new QPlainTextEdit;

    beautify(output);
    beautify(input);

    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(labeled(output, tr("Evaluation result")));
    splitter->addWidget(labeled(input, tr("Enter script code")));

    QToolButton *up = new QToolButton;
    QToolButton *down = new QToolButton;
    up->setText("^");
    down->setText("v");
    QPushButton *eval = new QPushButton(tr("Evaluate (Ctrl+ENTER)"));
    connect(up, SIGNAL(pressed()), this, SLOT(up()));
    connect(down, SIGNAL(pressed()), this, SLOT(down()));
    connect(eval, SIGNAL(pressed()), this, SLOT(submit()));

    QVBoxLayout *col = new QVBoxLayout;
    col->setMargin(0);
    col->setSpacing(0);
    col->addWidget(splitter);
    {
        QHBoxLayout *row = new QHBoxLayout;
        // eval->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        row->addWidget(down);
        row->addWidget(up);
        row->addWidget(eval);
        col->addLayout(row);
    }
    setLayout(col);

    input->setFocus();
    resize(300, 400);
}

void ConsoleWindow::log(const QStringList &list)
{
    output->appendPlainText(list.join(", "));
}

void ConsoleWindow::clear()
{
    output->clear();
}

void ConsoleWindow::up()
{
    if (historyPos == 0) return;
    --historyPos;
    input->setPlainText(history.at(historyPos));
}

void ConsoleWindow::down()
{
    if (historyPos >= history.length() - 1) return;
    ++historyPos;
    input->setPlainText(history.at(historyPos));
}

void ConsoleWindow::submit()
{
    QString text = input->toPlainText();
    if (text.contains("print")) text.replace("print", "log"); // quick HACK
    emit submitted(text);
    historyPos = history.length();
    history << text;
}

/** Find a suitable parent widget
  */
QWidget* ConsoleWindow::findParentWindow()
{
    QWidgetList topLevels = QApplication::topLevelWidgets();
    foreach(QWidget *w, topLevels) {
        if (qobject_cast<QMainWindow*>(w)) {
            if (w->findChild<QMenu*>())
                return w;
        }
    }
    foreach(QWidget *w, topLevels) {
        if (qobject_cast<QMainWindow*>(w))
            return w;
    }
    return 0;
}

void ConsoleWindow::beautify(QPlainTextEdit *edit)
{
    QFont font;
#ifdef Q_WS_MAC
    font = QFont("Monaco", 12);
    font.setPixelSize(12);
#else
    #ifndef Q_WS_WIN
        font = QFont("DejaVu Sans Mono", 10);
    #else
        font = QFont("Console", 10); // Courier
    #endif
    font.setPixelSize(13);
#endif
    edit->setFont(font);
}

QWidget *ConsoleWindow::labeled(QWidget *widget, const QString &label)
{
    QWidget *carrier = new QWidget;
    QVBoxLayout *col = new QVBoxLayout;
    col->setSpacing(0);
    col->setMargin(0);
    col->addWidget(new QLabel(label));
    col->addWidget(widget);
    carrier->setLayout(col);
    return carrier;
}

void ConsoleWindow::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if ((event->modifiers() & (Qt::ControlModifier|Qt::MetaModifier))) {
        if (event->key() == Qt::Key_Return)
            submit();
        else if (event->key() == Qt::Key_Up)
            up();
        else if (event->key() == Qt::Key_Down)
            down();
    }
}
