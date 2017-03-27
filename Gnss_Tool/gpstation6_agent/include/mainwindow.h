#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include "gnssdata.h"
#include "gpstationserver.h"
#include "utils.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;
class TimeGraph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void printToConsole(const QByteArray &data);
    void seansStart();
    void seansStop();
    void errorNotification(QString message);
    void handleError(QSerialPort::SerialPortError error);

signals:
    void sendLog(const QByteArray &timeLog);

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;
    ElapsedTime timer;
    TransmittableServer *server;

};

#endif // MAINWINDOW_H
