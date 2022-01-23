#include "utils.h"

#include <QMutex>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

utils::utils()
{

}

void outputMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type){
        case QtDebugMsg:        text = QString("QDebug:"); break;
        case QtWarningMsg:      text = QString("QWarning:");break;
        case QtInfoMsg:         text = QString("QInfo:");break;
        case QtCriticalMsg:     text = QString("QCritical:");break;
        case QtFatalMsg:        text = QString("QFatal:");break;
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file("log.txt");

    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";

    file.flush();
    file.close();

    mutex.unlock();
}
