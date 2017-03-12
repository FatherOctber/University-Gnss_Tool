/****************************************************************************
** Main gui app for run the gnss platform.
** Author: FatherOctber (https://github.com/FatherOctber)
****************************************************************************/
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSettings>
#include "mainwindow.h"

#define GUI_APP_VERSION "0.0.1"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Gnss platform app");
    app.setOrganizationName("VECTOR");
    app.setApplicationVersion(GUI_APP_VERSION);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
