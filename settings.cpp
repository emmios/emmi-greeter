#include "settings.h"

Settings::Settings() : QSettings("/etc/lightdm/emmi-greeter.conf", QSettings::NativeFormat)
{
    beginGroup("Config");
    this->backgroundImage = value("greeter-background-image").toString();
    this->userImage = value("greeter-user-image").toString();
    this->lastSession = value("last-session").toString();
    this->lastUser = value("last-user").toString();
    endGroup();
}

QString Settings::setLastSession(QString lastSession)
{
    beginGroup("Config");
    setValue("last-session", lastSession);
    endGroup();
}

QString Settings::setLastUser(QString lastUser)
{
    beginGroup("Config");
    setValue("last-user", lastUser);
    endGroup();
}
