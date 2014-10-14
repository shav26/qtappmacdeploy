#include "qmdmanager.h"

QmdManager::QmdManager(QQuickItem *parent) :
    QQuickItem(parent)
{
    m_settings = NULL;
    m_cmdManager = new QmdCommandManager();
    m_cmdManager->setParent(this);
}

QmdManager::QmdManager(const QmdManager& obj)
{
    m_settings = obj.m_settings;
}

const QmdManager& QmdManager::operator =(const QmdManager& obj)
{
    m_settings = obj.m_settings;

    return *this;
}

void QmdManager::startDeploy(bool saveDeployScript)
{
    if(m_settings && !m_settings->getAppPath().isEmpty() && !m_settings->getCertificate().isEmpty() && !m_settings->getInstallCertificate().isEmpty() &&
            !m_settings->getQtFolder().isEmpty() && !m_settings->getEntitlements().isEmpty())
    {
        QString deployScript;
        deployScript.clear();
        m_consoleMessage.clear();
        m_consoleMessage.append("Start working....");
        QString appName = m_settings->getAppPath().split("/").last().split(".").at(0);
        QString appPath = m_settings->getAppPath().replace("/"+appName+".app", "");

        ///macqtdeploy
        if(m_settings->getQmlFilesPath().isEmpty())
        {
            deployScript.append(QString("%1/bin/macdeployqt %2 -verbose=1 -executable=%3\n").arg(m_settings->getQtFolder()).arg(m_settings->getAppPath()).arg(m_settings->getAppPath()+"/Contents/MacOS/"+appName));
            QmdCommand* cmd = new QmdCommand();
            cmd->setCmdName(m_settings->getQtFolder()+"/bin/macdeployqt");
            cmd->setParams(QStringList()<<m_settings->getAppPath()<<"-verbose=1"<<"-executable="+m_settings->getAppPath()+"/Contents/MacOS/"+appName);
            connect(cmd, &QmdCommand::finished, [this](QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content){
                Q_UNUSED(cmd);
                Q_UNUSED(exitStatus);
                m_consoleMessage.append("Call "+cmd->getCmdName() + " with result: {" + QString(content)+"}\n");
                emit consoleMessageDidChange(m_consoleMessage);
            });
            m_cmdManager->addCommand(cmd);

            deployScript.append(QString("rm -rf %1").arg(m_settings->getAppPath()+"/Contents/Resources/qml/com\n"));
            QmdCommand* cmd1 = new QmdCommand();
            cmd1->setCmdName("rm");
            cmd1->setParams(QStringList()<<"-rf"<<m_settings->getAppPath()+"/Contents/Resources/qml/com");
            m_cmdManager->addCommand(cmd1);

            QmdCommand* cmd2 = new QmdCommand();
            cmd2->setCmdName("ls");
            cmd2->setParams(QStringList()<<"-al"<<m_settings->getAppPath()+"/Contents/Frameworks/");
            connect(cmd2, &QmdCommand::finished, [this, appName, appPath, deployScript, saveDeployScript](QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content){
                Q_UNUSED(cmd);
                Q_UNUSED(exitStatus);

                m_consoleMessage.append("Call "+cmd->getCmdName() + " with result: {" + QString(content)+"}\n");
                emit consoleMessageDidChange(m_consoleMessage);
                QString str(content);
                QStringList strList = str.split("\n");
                QString script;
                script.clear();
                foreach(QString item, strList)
                {
                    QString framework = item.split(" ").last();
                    if(framework.startsWith("Q"))
                    {
                        script.append(QString("cp %1 %2\n").arg(m_settings->getQtFolder()+"/lib/"+framework+"/Contents/Info.plist").
                                      arg(m_settings->getAppPath()+"/Contents/Frameworks/"+framework+"/Resources"));
                    }
                }

                script.append(QString("dsymutil %1 -o %2\n").arg(m_settings->getAppPath()+"/Contents/MacOS/"+appName).arg(m_settings->getAppPath()+"/../"+appName+".app.dSYM"));
                script.append(QString("find %1 -name *.dylib | xargs -I $ codesign -vvvv --force --verify --deep --verbose --sign \"%2\" $\n").arg(m_settings->getAppPath()+"/Contents").
                              arg(m_settings->getCertificate()));
                script.append(QString("find %1 -name Qt* -type f | xargs -I $ codesign -vvvv --force --verify --deep --verbose --sign \"%2\" $\n").arg(m_settings->getAppPath()+"/Contents").
                              arg(m_settings->getCertificate()));
                script.append(QString("codesign -vvvv --force --verify --deep --verbose --entitlements %1 --sign \"%2\" %3\n").arg(m_settings->getEntitlements()).
                              arg(m_settings->getCertificate()).arg(m_settings->getAppPath()));
                script.append(QString("productbuild --component \"%1\" /Applications --sign \"%2\" --product \"%3/Contents/Info.plist\" %4.pkg\n").arg(m_settings->getAppPath()).
                              arg(m_settings->getInstallCertificate()).arg(m_settings->getAppPath()).arg(m_settings->getAppPath()+"/../"+appName));

                QFile file(appPath+"/script.sh");
                if(file.open(QIODevice::WriteOnly))
                {
                    QTextStream st(&file);
                    st<<script;
                    file.close();
                }

                QString deployScriptContent;
                deployScriptContent.clear();
                deployScriptContent.append(deployScript);
                deployScriptContent.append(script);

                if(saveDeployScript && !deployScriptContent.isEmpty())
                {
                    QFile f(appPath+"/deploy_"+appName+"_script.sh");
                    if(f.open(QIODevice::WriteOnly))
                    {
                        QTextStream st(&f);
                        st<<deployScriptContent;
                        f.close();
                    }
                }

                QmdCommand* cmd4 = new QmdCommand();
                cmd4->setCmdName("chmod");
                cmd4->setParams(QStringList()<<"+x"<<appPath+"/script.sh");
                connect(cmd4, &QmdCommand::finished, [this, appPath](QmdCommand* cmd1, QProcess::ExitStatus exitStatus1, QByteArray content1){

                    Q_UNUSED(cmd1);
                    Q_UNUSED(exitStatus1);
                    Q_UNUSED(content1);
                    QmdCommand* cmd5 = new QmdCommand();
                    cmd5->setCmdName("sh");
                    cmd5->setParams(QStringList()<<appPath+"/script.sh");
                    connect(cmd5, &QmdCommand::finished, [this, appPath](QmdCommand* cmd2, QProcess::ExitStatus exitStatus2, QByteArray content2){

                        Q_UNUSED(cmd2);
                        Q_UNUSED(exitStatus2);
                        m_consoleMessage.append("Call "+cmd2->getCmdName() + " with result: {" + QString(content2)+"}\n");
                        emit consoleMessageDidChange(m_consoleMessage);

//                        QmdCommand* cmd6 = new QmdCommand();
//                        cmd6->setCmdName("rm");
//                        cmd6->setParams(QStringList()<<"-rf"<<appPath+"/script.sh");
//                        m_cmdManager->addCommand(cmd6);
                    });

                    m_cmdManager->addCommand(cmd5);
                });

                m_cmdManager->addCommand(cmd4);
            });
            m_cmdManager->addCommand(cmd2);
        }
        else
        {
            deployScript.append(QString("%1/bin/macdeployqt %2 -verbose=1 -executable=%3\n").arg(m_settings->getQtFolder()).arg(m_settings->getAppPath()).
                                arg(m_settings->getAppPath()+"/Contents/MacOS/"+appName));
            QStringList params = QStringList()<<m_settings->getAppPath()<<"-verbose=1"<<"-qmldir="+m_settings->getQmlFilesPath()<<"-executable="+m_settings->getAppPath()+"/Contents/MacOS/"+appName;
            QmdCommand* cmd = new QmdCommand();
            cmd->setCmdName(m_settings->getQtFolder()+"/bin/macdeployqt");
            cmd->setParams(params);
            connect(cmd, &QmdCommand::finished, [this](QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content){
                Q_UNUSED(cmd);
                Q_UNUSED(exitStatus);
                m_consoleMessage.append("Call "+cmd->getCmdName() + " with result: {" + QString(content)+"}\n");
                emit consoleMessageDidChange(m_consoleMessage);
            });
            m_cmdManager->addCommand(cmd);

            deployScript.append(QString("rm -rf %1\n").arg(m_settings->getAppPath()+"/Contents/Resources/qml/com"));
            QmdCommand* cmd1 = new QmdCommand();
            cmd1->setCmdName("rm");
            cmd1->setParams(QStringList()<<"-rf"<<m_settings->getAppPath()+"/Contents/Resources/qml/com");
            m_cmdManager->addCommand(cmd1);

            QmdCommand* cmd2 = new QmdCommand();
            cmd2->setCmdName("ls");
            cmd2->setParams(QStringList()<<"-al"<<m_settings->getAppPath()+"/Contents/Frameworks/");
            connect(cmd2, &QmdCommand::finished, [this, appName, appPath, deployScript, saveDeployScript](QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content){
                Q_UNUSED(cmd);
                Q_UNUSED(exitStatus);

                QString str(content);
                QStringList strList = str.split("\n");
                QString script;
                script.clear();
                foreach(QString item, strList)
                {
                    QString framework = item.split(" ").last();
                    if(framework.startsWith("Q"))
                    {
                        script.append(QString("cp %1 %2\n").arg(m_settings->getQtFolder()+"/lib/"+framework+"/Contents/Info.plist").
                                      arg(m_settings->getAppPath()+"/Contents/Frameworks/"+framework+"/Resources"));
                    }
                }

                script.append(QString("dsymutil %1 -o %2\n").arg(m_settings->getAppPath()+"/Contents/MacOS/"+appName).arg(m_settings->getAppPath()+"/../"+appName+".app.dSYM"));
                script.append(QString("find %1 -name *.dylib | xargs -I $ codesign -vvvv --force --verify --deep --verbose --sign \"%2\" $\n").arg(m_settings->getAppPath()+"/Contents").
                              arg(m_settings->getCertificate()));
                script.append(QString("find %1 -name Qt* -type f | xargs -I $ codesign -vvvv --force --verify --deep --verbose --sign \"%2\" $\n").arg(m_settings->getAppPath()+"/Contents").
                              arg(m_settings->getCertificate()));
                script.append(QString("codesign -vvvv --force --verify --deep --verbose --entitlements %1 --sign \"%2\" %3\n").arg(m_settings->getEntitlements()).
                              arg(m_settings->getCertificate()).arg(m_settings->getAppPath()));
                script.append(QString("productbuild --component \"%1\" /Applications --sign \"%2\" --product \"%3/Contents/Info.plist\" %4.pkg\n").arg(m_settings->getAppPath()).
                              arg(m_settings->getInstallCertificate()).arg(m_settings->getAppPath()).arg(m_settings->getAppPath()+"/../"+appName));
                script.append(QString("codesign -vvvv \"%1\"\n").arg(m_settings->getAppPath()));

                QFile file(appPath+"/script.sh");
                if(file.open(QIODevice::WriteOnly))
                {
                    QTextStream st(&file);
                    st<<script;
                    file.close();
                }

                QString deployScriptContent;
                deployScriptContent.clear();
                deployScriptContent.append(deployScript);
                deployScriptContent.append(script);

                if(saveDeployScript && !deployScriptContent.isEmpty())
                {
                    QFile f(appPath+"/deploy_"+appName+"_script.sh");
                    if(f.open(QIODevice::WriteOnly))
                    {
                        QTextStream st(&f);
                        st<<deployScriptContent;
                        f.close();
                    }
                }

                QmdCommand* cmd4 = new QmdCommand();
                cmd4->setCmdName("chmod");
                cmd4->setParams(QStringList()<<"+x"<<appPath+"/script.sh");
                connect(cmd4, &QmdCommand::finished, [this, appPath](QmdCommand* cmd1, QProcess::ExitStatus exitStatus1, QByteArray content1){
                    Q_UNUSED(cmd1);
                    Q_UNUSED(exitStatus1);
                    Q_UNUSED(content1);

                    QmdCommand* cmd5 = new QmdCommand();
                    cmd5->setCmdName("sh");
                    cmd5->setParams(QStringList()<<appPath+"/script.sh");
                    connect(cmd5, &QmdCommand::finished, [this, appPath](QmdCommand* cmd2, QProcess::ExitStatus exitStatus2, QByteArray content2){
                        Q_UNUSED(cmd2);
                        Q_UNUSED(exitStatus2);

                        m_consoleMessage.append("Call "+cmd2->getCmdName() + " with result: {" + QString(content2)+"}\n");
                        emit consoleMessageDidChange(m_consoleMessage);

                        QmdCommand* cmd6 = new QmdCommand();
                        cmd6->setCmdName("rm");
                        cmd6->setParams(QStringList()<<"-rf"<<appPath+"/script.sh");
                        m_cmdManager->addCommand(cmd6);

                        emit deployDidFinish();
                    });

                    m_cmdManager->addCommand(cmd5);
                });

                m_cmdManager->addCommand(cmd4);
            });
            m_cmdManager->addCommand(cmd2);
        }

        m_cmdManager->runCommands();
    }
}

