#include "csv.h"
#include <QDebug>
Csv::Csv()
{
    file = new QFile;
    dir = new QDir(QDir::currentPath()+"//instance");
    if(dir->exists())
        dir->removeRecursively();
    dir->mkdir(QDir::currentPath()+"//instance");
}

bool Csv::isFileExit(QString fileName)
{
    file->setFileName(fileName);
    return file->open(QIODevice::ReadOnly);
}

void Csv::addRow(QStringList s,QString id)
{
    if(isFileExit(id))
    {
        file->close();
        file->open(QIODevice::Append);
    }
    else
    {
        file->close();
        file->open(QIODevice::WriteOnly);
    }
    QTextStream in(file);
    QString row=in.readAll();
    for(int i=0;i<s.length();i++)
    {
        if(i!=s.length()-1)
            row = row + s.at(i) + ",";
        else
            row = row + s.at(i) + "\n";
    }
    in<<row;
    qDebug()<<"csv called!";
    file->close();
}

QStringList Csv::readAll(QString id)
{
    QStringList buff;
    if(isFileExit(id))
    {
        file->close();
        file->open(QIODevice::ReadOnly);
    }
    else
        return buff;
    QTextStream out(file);
    buff = out.readAll().split("\n");
    return buff;
}
