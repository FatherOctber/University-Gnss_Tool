#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include "gnssdata.h"
#include "datahandler.h"
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
    void writeData(const QByteArray &data);
    void readData();
    void seansStart();
    void seansStop();
    void errorNotification(QString message);
    void handleError(QSerialPort::SerialPortError error);
    void transferDataToGraphics();

signals:
    void sendLog(const QByteArray &timeLog);
    void sendData(std::vector<double> dataT,std::vector<double> dataF, const StandardTime& timeStart, const StandardTime& timeStop);

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    Console *console;
    SettingsDialog *settings;
    TimeGraph *timeGraph;
    QSerialPort *serial;
    Abstracthandler *dataHandler;
    ITransmittableServer *server;
};

#endif // MAINWINDOW_H
