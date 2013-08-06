#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QDialog>

class QPlainTextEdit;
class QPushButton;

class ConsoleWindow: public QDialog
{
    Q_OBJECT

public:
    ConsoleWindow();

signals:
    void submitted(const QString &text);

public slots:
    void log(const QStringList &list);
    void clear();

private slots:
    void up();
    void down();
    void submit();

private:
    static QWidget* findParentWindow();
    void beautify(QPlainTextEdit *edit);
    QWidget *labeled(QWidget *widget, const QString &label);
    virtual void keyPressEvent(QKeyEvent *event);

    QPlainTextEdit *output;
    QPlainTextEdit *input;
    QStringList history;
    int historyPos;
};

#endif // CONSOLEWINDOW_H
