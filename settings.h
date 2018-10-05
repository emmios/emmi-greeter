#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QDebug>
#include <QCoreApplication>


class Settings : public QSettings
{
public:
    Settings();
    QString backgroundImage;
    QString userImage;
    QString lastUser;
    QString lastSession;
    QString setLastSession(QString lastSession);
    QString setLastUser(QString lastUser);
};

#endif // SETTINGS_H
