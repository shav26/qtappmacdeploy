#ifndef QMDSETTINGS_H
#define QMDSETTINGS_H

#include <QtCore>



/** @class QmdSettings
 *  @brief The class of settings
 *  @author Andrew Shapovalov*/
class QmdSettings : public QObject
{
        Q_OBJECT

        Q_PROPERTY(QString certificate READ getCertificate WRITE setCertificate NOTIFY certificateChanged)
        Q_PROPERTY(QString installCertificate READ getInstallCertificate WRITE setInstallCertificate NOTIFY installCertificateChanged)
        Q_PROPERTY(QString entitlements READ getEntitlements WRITE setEntitlements NOTIFY entitlementsChanged)
        Q_PROPERTY(QString appPath READ getAppPath WRITE setAppPath NOTIFY appPathChanged)
        Q_PROPERTY(QString qmlFilesPath READ getQmlFilesPath WRITE setQmlFilesPath NOTIFY qmlFilesPathChanged)
        Q_PROPERTY(QString qtFolder READ getQtFolder WRITE setQtFolder NOTIFY qtFolderChanged)

    private:
        /** The Mac OS Distribution certificate.*/
        QString m_certificate;

        /** The Mac OS Install certificate.*/
        QString m_installCertificate;

        /** The path to Entitlements plist.*/
        QString m_entitlements;

        /** The application bundle path.*/
        QString m_appPath;

        /** The qml files if needs.*/
        QString m_qmlFilesPath;

        /** The Qt folder path where Qt is installed.*/
        QString m_qtFolder;

    public:
        /** @brief Create a new object
         *  @param parent The parent object.
         *  @author Andrew Shapovalov*/
        explicit QmdSettings(QObject *parent = 0);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        QmdSettings(const QmdSettings& obj);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        const QmdSettings& operator =(const QmdSettings& obj);



        //Getters
        /** @brief Get certificate name.
         *  @return The certificate.
         *  @author Andrew Shapovalov*/
        inline QString getCertificate(){return m_certificate;}

        /** @brief Get install certificate name.
         *  @return The certificate.
         *  @author Andrew Shapovalov*/
        inline QString getInstallCertificate(){return m_installCertificate;}

        /** @brief Get path to Entitlements plist.
         *  @return The path.
         *  @author Andrew Shapovalov*/
        inline QString getEntitlements(){return m_entitlements;}

        /** @brief Get application bundle path.
         *  @return The app bundle path.
         *  @author Andrew Shapovalov*/
        inline QString getAppPath(){return m_appPath;}

        /** @brief Get qml folder path.
         *  @return The folder path.
         *  @author Andrew Shapovalov*/
        inline QString getQmlFilesPath(){return m_qmlFilesPath;}

        /** @brief Get Qt install folder.
         *  @return The Qt install folder.
         *  @author Andrew Shapovalov*/
        inline QString getQtFolder(){return m_qtFolder;}

        /** @brief Convert to variant object.
         *  @return The variant object.
         *  @author Andrew Shapovalov*/
        Q_INVOKABLE QVariant toVariant();


        //Setters
        /** @brief Set the certificate name.
         *  @param value The certificate.
         *  @author Andrew Shapovalov*/
        inline void setCertificate(QString value){m_certificate = value; emit certificateChanged(m_certificate);}

        /** @brief Set install certificate name.
         *  @param value The certificate.
         *  @author Andrew Shapovalov*/
        inline void setInstallCertificate(QString value){m_installCertificate = value; emit installCertificateChanged(m_installCertificate);}

        /** @brief Set path to Entitlements plist.
         *  @param value The path.
         *  @author Andrew Shapovalov*/
        inline void setEntitlements(QString value){m_entitlements = value; emit entitlementsChanged(m_entitlements);}

        /** @brief Set application bundle path.
         *  @param value The app bundle path.
         *  @author Andrew Shapovalov*/
        inline void setAppPath(QString value){m_appPath = value; emit appPathChanged(m_appPath);}

        /** @brief Set qml folder path.
         *  @param value The folder path.
         *  @author Andrew Shapovalov*/
        inline void setQmlFilesPath(QString value){m_qmlFilesPath = value; emit qmlFilesPathChanged(m_qmlFilesPath);}

        /** @brief Set Qt install folder.
         *  @param value The Qt install folder.
         *  @author Andrew Shapovalov*/
        inline void setQtFolder(QString value){m_qtFolder = value; emit qtFolderChanged(m_qtFolder);}

    signals:
        /** @brief Called when certificate name was changed.
         *  @param value The certificate.
         *  @author Andrew Shapovalov*/
        void certificateChanged(QString value);

        /** @brief Called when install certificate name was changed.
         *  @param value The certificate.
         *  @author Andrew Shapovalov*/
        void installCertificateChanged(QString value);

        /** @brief Called when path to Entitlements plist was changed.
         *  @param value The path.
         *  @author Andrew Shapovalov*/
        void entitlementsChanged(QString value);

        /** @brief Called when application bundle path was changed.
         *  @param value The app bundle path.
         *  @author Andrew Shapovalov*/
        void appPathChanged(QString value);

        /** @brief Called when qml folder path was changed.
         *  @param value The folder path.
         *  @author Andrew Shapovalov*/
        void qmlFilesPathChanged(QString value);

        /** @brief Called when Qt install folder was changed.
         *  @param value The Qt install folder.
         *  @author Andrew Shapovalov*/
        void qtFolderChanged(QString value);

    public slots:

};
Q_DECLARE_METATYPE(QmdSettings)

#endif // QMDSETTINGS_H
