#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class utils
{
public:
    utils();
};

#endif // UTILS_H

void outputMsg(QtMsgType type, const QMessageLogContext &content, const QString & msg);
