#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include "utils.h"

QT_BEGIN_NAMESPACE

class Console;
class PlatformCore;
class PlatfromConfig;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void print(QString data);
    void start();
    void stop();

signals:

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    Console *console;
    PlatformCore *platformCore;
    PlatfromConfig *plConfig;
};

#endif // MAINWINDOW_H
