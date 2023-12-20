#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleF;
    styleF.setFileName("../KLibrary/style.qss");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    qApp->setStyleSheet(qssStr);

//     QTranslator translator;
//     if(translator.load("../KLibrary/KLibrary_ru_RU.qm"))
//     {
//         a.installTranslator(&translator);
//     }
    MainWindow w;
    w.show();
    return a.exec();
}
