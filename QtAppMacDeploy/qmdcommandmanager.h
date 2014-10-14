#ifndef QMDCOMMANDMANAGER_H
#define QMDCOMMANDMANAGER_H

#include <QtCore>
#include "qmdcommand.h"



/** @class QmdCommandManager
 *  @brief The manager to work with commands.
 *  @author Andrew Shapovalov*/
class QmdCommandManager : public QObject
{
        Q_OBJECT

    private:
        /** The list of commands.*/
        QmdCommandList m_commands;



        /** @brief Call the first command from list.
         *  @author Andrew Shapovalov*/
        void runFirstCommand();

    public:
        /** @brief Create a new object.
         *  @param parent The parent object.
         *  @author Andrew Shapovalov*/
        explicit QmdCommandManager(QObject *parent = 0);



        //Getters
        /** @brief Get list of commands.
         *  @return The list of commands.
         *  @author Andrew Shapovalov*/
        inline QmdCommandList getCommands(){return m_commands;}

        /** @brief Execute commands from list.
         *  @author Andrew Shapovalov*/
        void runCommands();



        //Setters
        /** @brief Set list of commands.
         *  @param value The list of commands.
         *  @author Andrew Shapovalov*/
        inline void getCommands(QmdCommandList value){m_commands = value; emit commandsChanged(m_commands);}

        /** @brief Add a new command to list.
         *  @param cmd The new command.
         *  @author Andrew Shapovalov*/
        void addCommand(QmdCommand* cmd);

    signals:
        /** @brief Called when list of commands was changed.
         *  @param value The list of commands.
         *  @author Andrew Shapovalov*/
        void commandsChanged(QmdCommandList value);

        /** @brief Called when some command did finish work.
         *  @param cmd The command which was finished.
         *  @param resultString The result string.
         *  @author Andrew Shapovalov*/
        void commandDidFinish(QmdCommand* cmd, QByteArray resultString);

    public slots:

    private slots:
        /** @brief Called when command is finished.
         *  @param cmd The command object.
         *  @param exitStatus The exit status.
         *  @param content The result of command.
         *  @author Andrew Shapovalov*/
        void onFinished(QmdCommand* cmd, QProcess::ExitStatus exitStatus, QByteArray content);

};

#endif // QMDCOMMANDMANAGER_H
