#ifndef QMDCOMMAND_H
#define QMDCOMMAND_H

#include <QtCore>



/** @class QmdCommand
 *  @brief The class to run command.
 *  @author Andrew Shapovalov*/
class QmdCommand : public QProcess
{
        Q_OBJECT

    private:
        /** The name of command.*/
        QString m_nameId;

        /** The name of command.*/
        QString m_cmdName;

        /** The command's params.*/
        QStringList m_params;

    public:
        /** @brief Create a new object.
         *  @param parent The parent object.
         *  @author Andrew Shapovalov*/
        explicit QmdCommand(QObject *parent = 0);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        QmdCommand(const QmdCommand& obj);

        /** @brief Copy object
         *  @param obj The source object.
         *  @author Andrew Shapovalov*/
        const QmdCommand& operator =(const QmdCommand& obj);



        //Getters
        /** @brief Get command id.
         *  @return The command id.
         *  @author Andrew Shapovalov*/
        inline QString getNameId(){return m_nameId;}

        /** @brief Get name of command.
         *  @return The command name.
         *  @author Andrew Shapovalov*/
        inline QString getCmdName(){return m_cmdName;}

        /** @brief Get command params.
         *  @return The command params.
         *  @author Andrew Shapovalov*/
        inline QStringList getParams(){return m_params;}

        /** @brief Execute command.
         *  @param mode The mode of command.
         *  @author Andrew Shapovalov*/
        void exec(QProcess::OpenMode mode = QProcess::ReadWrite);

        /** @brief Convert to variant object.
         *  @return The variant object.
         *  @author Andrew Shapovalov*/
        QVariant toVariant();



        //Setters
        /** @brief Set name of command.
         *  @param value The command name.
         *  @author Andrew Shapovalov*/
        inline void setCmdName(QString value){m_cmdName = value; m_nameId = m_nameId.replace("Command", m_cmdName);}

        /** @brief Set command params.
         *  @param value The command params.
         *  @author Andrew Shapovalov*/
        inline void setParams(QStringList value){m_params = value;}

    signals:
        /** @brief The command is finithed.
         *  @param cmd The command object.
         *  @param exitStatus The exit status.
         *  @param content The result of command.
         *  @author Andrew Shapovalov*/
        void finished(QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content);

    public slots:

    private slots:
        /** @brief Called when curren command was finished.
         *  @param exitCode The code of exit.
         *  @param exitStatus The exit status.
         *  @author Andrew Shapovalov*/
        void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

        /** @brief Called when curren command was error.
         *  @param error The code of error.
         *  @author Andrew Shapovalov*/
        void onError(QProcess::ProcessError error);
};
Q_DECLARE_METATYPE(QmdCommand)



/** @typedef QmdCommandList
 *  @brief The list of commands.
 *  @author Andrew Shapovalov*/
typedef QList<QmdCommand*> QmdCommandList;
Q_DECLARE_METATYPE(QmdCommandList)

#endif // QMDCOMMAND_H
