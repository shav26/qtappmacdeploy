#include "qmdcommand.h"

QmdCommand::QmdCommand(QObject *parent) :
    QProcess(parent)
{
    m_nameId = QString("Command_%1").arg(QDateTime::currentDateTime().toTime_t() + 1);
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), SLOT(onFinished(int,QProcess::ExitStatus)));
}

QmdCommand::QmdCommand(const QmdCommand& obj)
{
    m_nameId = obj.m_nameId;
    m_cmdName = obj.m_cmdName;
    m_params = obj.m_params;
}

const QmdCommand& QmdCommand::operator =(const QmdCommand& obj)
{
    m_nameId = obj.m_nameId;
    m_cmdName = obj.m_cmdName;
    m_params = obj.m_params;

    return *this;
}

void QmdCommand::exec(QProcess::OpenMode mode)
{
    if(!m_cmdName.isEmpty() && !m_params.isEmpty())
    {
        start(m_cmdName, m_params, mode);
    }
}

QVariant QmdCommand::toVariant()
{
    QVariantMap map;
    map.clear();
    map["nameId"] = m_nameId;
    map["cmdName"] = m_cmdName;
    map["params"] = m_params;

    return QVariant(map);
}

void QmdCommand::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);

    emit finished(this, exitStatus, readAll());
    this->deleteLater();    //Auto remove from memory
}
