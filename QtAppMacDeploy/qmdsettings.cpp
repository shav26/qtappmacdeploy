#include "qmdsettings.h"

QmdSettings::QmdSettings(QObject *parent) :
    QObject(parent)
{
    m_certificate.clear();
    m_installCertificate.clear();
    m_appPath.clear();
    m_qmlFilesPath.clear();
    m_qtFolder.clear();
}

QmdSettings::QmdSettings(const QmdSettings& obj)
{
    m_certificate = obj.m_certificate;
    m_installCertificate = obj.m_installCertificate;
    m_appPath = obj.m_appPath;
    m_qmlFilesPath = obj.m_qmlFilesPath;
    m_qtFolder = obj.m_qtFolder;
}

const QmdSettings& QmdSettings::operator =(const QmdSettings& obj)
{
    m_certificate = obj.m_certificate;
    m_installCertificate = obj.m_installCertificate;
    m_appPath = obj.m_appPath;
    m_qmlFilesPath = obj.m_qmlFilesPath;
    m_qtFolder = obj.m_qtFolder;

    return *this;
}

QVariant QmdSettings::toVariant()
{
    QVariantMap map;
    map.clear();
    map["certificate"] = m_certificate;
    map["installCertificate"] = m_installCertificate;
    map["appPath"] = m_appPath;
    map["qmlFilesPath"] = m_qmlFilesPath;
    map["qtFolder"] = m_qtFolder;

    return QVariant(map);
}

