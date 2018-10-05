#include "greeterutil.h"

using namespace QLightDM;


GreeterUtil::GreeterUtil(QGuiApplication *app) :
    greeter(),
    power(app),
    sessionsModel(),
    userModel()
{

    if (!greeter.connectSync())
    {
        app->exit(0);
    }

    // add sessions
    for(int sessionIndex = 0; sessionIndex < sessionsModel.rowCount(QModelIndex()); sessionIndex++)
    {
        sessions << sessionsModel.data(sessionsModel.index(sessionIndex,0),SessionsModel::KeyRole).toString();
    }

    // add users
    for(int userIndex = 0; userIndex < userModel.rowCount(QModelIndex()); userIndex++)
    {
        usernames << userModel.data(userModel.index(userIndex,0),UsersModel::NameRole).toString();
    }

    this->connect(&greeter, SIGNAL(showPrompt(QString, QLightDM::Greeter::PromptType)), this, SLOT(onPrompt(QString, QLightDM::Greeter::PromptType)));
    this->connect(&greeter, SIGNAL(authenticationComplete()), this, SLOT(authenticationComplete()));
}

void GreeterUtil::authenticateUser(QString username)
{
    if(greeter.inAuthentication())
    {
        greeter.cancelAuthentication();
    }

    if (!username.isEmpty())
    {
        this->user = username;
        greeter.authenticate(username);
    }
}

void GreeterUtil::response(QString password)
{
    if (!password.isEmpty())
    {
        greeter.respond(password.trimmed());
    }
}

void GreeterUtil::authenticationComplete()
{
    if(greeter.isAuthenticated())
    {
        greeter.startSessionSync(this->session);
    }
    else
    {
        this->clearPassword();
    }
}

void GreeterUtil::onPrompt(QString,QLightDM::Greeter::PromptType)
{
    QMetaObject::invokeMethod(this->obj, "clearPassword");
}

void GreeterUtil::clearPassword()
{
    QMetaObject::invokeMethod(this->obj, "clearPassword");
}

void GreeterUtil::shutdown()
{
    if (this->power.canShutdown()) this->power.shutdown();
}
