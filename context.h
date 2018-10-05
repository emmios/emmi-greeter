#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "greeterutil.h"
#include "settings.h"


class Context : public QObject
{

   Q_OBJECT

private:
    QTimer * timer;
    QDateTime dateTime;

public:
    GreeterUtil *util;
    Settings *settings;
    Q_INVOKABLE void power();
    Q_INVOKABLE QStringList sessions();
    Q_INVOKABLE void session(QString session);
    Q_INVOKABLE QStringList users();
    Q_INVOKABLE QString time();
    Q_INVOKABLE QString date();
    Q_INVOKABLE QString lastSession();
    Q_INVOKABLE QString lastUser();
    Q_INVOKABLE QString background();
    Q_INVOKABLE QString userImage();
    Q_INVOKABLE void userChange(QString username);
    Q_INVOKABLE void passwordRespond(QString password);
};

#endif // CONTEXT_H
