#ifndef QMDMANAGER_H
#define QMDMANAGER_H

#include <QtCore>
#include <QtQuick>
#include "qmdsettings.h"
#include "qmdcommandmanager.h"



/** @class QmdManager
 *  @brief The class of manager.
 *  @author Andrew Shapovalov*/
class QmdManager : public QQuickItem
{
        Q_OBJECT

        Q_PROPERTY(QmdSettings* settings READ getSettings WRITE setSettings NOTIFY settingsChanged)

    private:
        /** The message to console.*/
        QString m_consoleMessage;

        /** The settings of preference.*/
        QmdSettings* m_settings;

        /** The command manager.*/
        QmdCommandManager* m_cmdManager;

    public:
        /** @brief Create a new object
         *  @param parent The parent object.
         *  @author Andrew Shapovalov*/
        explicit QmdManager(QQuickItem *parent = 0);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        QmdManager(const QmdManager& obj);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        const QmdManager& operator =(const QmdManager& obj);


        //Getters
        /** @brief Get settings.
         *  @return The settings object.
         *  @author Andrew Shapovalov*/
        inline QmdSettings* getSettings(){return m_settings;}

        /** @brief The start to deploy of application.
         *  @brief saveDeployScript The flag to turn on save script to deploy.
         *  @author Andrew Shapovalov*/
        Q_INVOKABLE void startDeploy(bool saveDeployScript = false);


        //Setters
        /** @brief Set settings
         *  @param value The settings
         *  @author Andrew Shapovalov*/
        inline void setSettings(QmdSettings* value){m_settings = value; emit settingsChanged(m_settings);}

    signals:
        /** @brief Vcalled when settings was changed
         *  @param value The settings
         *  @author Andrew Shapovalov*/
        void settingsChanged(QmdSettings* value);

        /** @brief Called when console message was updated.
         *  @param msg The console message.
         *  @author Andrew Shapovalov*/
        void consoleMessageDidChange(QString msg);

        /** @brief Called when deploy is finished.
         *  @author Andrew Shapovalov*/
        void deployDidFinish();

    public slots:

};
Q_DECLARE_METATYPE(QmdManager)

#endif // QMDMANAGER_H
