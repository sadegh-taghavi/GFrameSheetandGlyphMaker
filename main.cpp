#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QDate>
#include <QtGlobal>
#include <QString>
#include <QGridLayout>
#include <QStyleFactory>
#include <qglobal.h>
#include <QFile>
#include <time.h>
#include <QDebug>
#include <QtMessageHandler>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDate date;
    QTime ti;
    QString message;
     switch (type) {
     case QtDebugMsg:
         message = "Debug";
         break;
     case QtWarningMsg:
         message = "Warning";
         break;
     case QtCriticalMsg:
         message = "Critical";
         break;
     case QtFatalMsg:
         message = "Fatal";
         abort();
     }
     message += "<" + date.currentDate().toString() + "><" + ti.currentTime().toString() + ">:";
     QByteArray localMsg = msg.toLocal8Bit();
     message += localMsg.constData();
     message += "(";
     message += context.file;
     message += ":" + QString::number(context.line) + ", ";
     message += context.function;
     message += ")\r\n";
     QFile outFile("log.txt");
     outFile.open(QIODevice::WriteOnly | QIODevice::Append);
     outFile.write(message.toLatin1());
     outFile.close();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
