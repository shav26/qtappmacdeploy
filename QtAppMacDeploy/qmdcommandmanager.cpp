#include "qmdcommandmanager.h"

QmdCommandManager::QmdCommandManager(QObject *parent) :
    QObject(parent)
{
}

void QmdCommandManager::runFirstCommand()
{
    QmdCommand* cmd = m_commands.first();
    cmd->exec();
}

void QmdCommandManager::runCommands()
{
    if(!m_commands.isEmpty())
    {
        runFirstCommand();
    }
}

void QmdCommandManager::addCommand(QmdCommand* cmd)
{
    connect(cmd,SIGNAL(finished(QmdCommand*,QProcess::ExitStatus,QByteArray)), SLOT(onFinished(QmdCommand*,QProcess::ExitStatus,QByteArray)));
    m_commands.append(cmd);
    emit commandsChanged(m_commands);
}

void QmdCommandManager::onFinished(QmdCommand *cmd, QProcess::ExitStatus exitStatus, QByteArray content)
{
    Q_UNUSED(exitStatus);

    m_commands.removeOne(cmd);  //Remove the current command.
    emit commandsChanged(m_commands);
    emit commandDidFinish(cmd, content);

    if(!m_commands.isEmpty())
    {
        runFirstCommand();  //Call next command.
    }
}
