#include "context.h"


void Context::power()
{
    this->util->shutdown();
}

QStringList Context::sessions()
{
    return this->util->sessions;
}

QStringList Context::users()
{
    return this->util->usernames;
}

QString Context::time()
{
    QString data = dateTime.currentDateTime().toString(Qt::SystemLocaleLongDate);
    QStringList lista = data.split(",");
    QStringList tlista = lista[2].split(" ");

    if (tlista.length() >= 4)
    {
        return tlista[2] + "-" + tlista[3];
    }

    return tlista[2] + "-";
}

QString Context::date()
{
    QString data = dateTime.currentDateTime().toString(Qt::SystemLocaleLongDate);
    QStringList lista = data.split(",");
    QStringList tlista = lista[2].split(" ");
    return lista[0] + " " + lista[1] + " " + tlista[1];
}

void Context::userChange(QString username)
{
    //Why I need this?
    QFile r("/etc/lightdm/emmi-greeter.conf");
    QString all;

    if (r.open(QFile::ReadOnly))
    {
        QTextStream stream(&r);
        all = stream.readAll();
    }

    r.close();

    QFile w("/etc/lightdm/emmi-greeter.conf");

    if (w.open(QFile::WriteOnly))
    {
        for (QString line : all.split("\n"))
        {
            if ("last-user" == line.split("=")[0])
            {
                w.write(all.replace(line, line.split("=")[0] + "=" + username).toUtf8());
                break;
            }
        }
    }

    w.close();

    this->util->authenticateUser(username);
    //this->util->settings->setLastUser(username);
}

void Context::passwordRespond(QString password)
{
    this->util->response(password);
}

void Context::session(QString session)
{
    //Why I need this?
    QFile r("/etc/lightdm/emmi-greeter.conf");
    QString all;

    if (r.open(QFile::ReadOnly))
    {
        QTextStream stream(&r);
        all = stream.readAll();
    }

    r.close();

    QFile w("/etc/lightdm/emmi-greeter.conf");

    if (w.open(QFile::WriteOnly))
    {
        for (QString line : all.split("\n"))
        {
            if ("last-session" == line.split("=")[0])
            {
                w.write(all.replace(line, line.split("=")[0] + "=" + session).toUtf8());
                break;
            }
        }
    }

    w.close();

    this->util->session = session;
    //this->util->settings->setLastSession(session);
}

QString Context::lastSession()
{
    return this->settings->lastSession;
}

QString Context::lastUser()
{
    return this->settings->lastUser;
}

QString Context::background()
{
    return this->settings->backgroundImage;
}

QString Context::userImage()
{
    return this->settings->userImage;
}

