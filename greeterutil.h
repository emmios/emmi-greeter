#ifndef GREETERUTIL_H
#define GREETERUTIL_H

#include <QDebug>
#include <QObject>
#include <QGuiApplication>
#include <QModelIndex>
#include <QString>
#include <QStringList>
#include <QMetaObject>
#include <QLightDM/greeter.h>
#include <QLightDM/power.h>
#include <QLightDM/sessionsmodel.h>
#include <QLightDM/usersmodel.h>

#include "abstractutil.h"
#include "settings.h"


class GreeterUtil : public AbstractUtil
{

    Q_OBJECT

private:
    QLightDM::Greeter greeter;
    QLightDM::PowerInterface power;
    QLightDM::SessionsModel sessionsModel;
    QLightDM::UsersModel userModel;
    void clearPassword();

private slots:
    void authenticationComplete();
    void onPrompt(QString, QLightDM::Greeter::PromptType);

public:
    GreeterUtil(QGuiApplication *app);
    Settings *settings;
    QString session;
    QString user;
    QStringList sessions;
    QStringList usernames;
    void authenticateUser(QString username);
    void response(QString password);
    void shutdown();
    QObject *obj;
};

#endif // GREETERUTIL_H
