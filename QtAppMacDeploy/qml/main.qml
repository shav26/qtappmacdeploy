import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import com.shav.qtappmacdeploy 1.0
import "js/helpers.js" as Helpers

ApplicationWindow {
    id: appRoot
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    maximumWidth: 640
    maximumHeight: 480
    flags: Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.WindowCloseButtonHint
    title: qsTr("Qt App Mac Deploy")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: "Help"
            MenuItem {
                text: "About Qt App Mac Deploy"
                onTriggered: {
                    if(Helpers.createAboutWindow(appRoot, appRoot))
                    {
                        Helpers.aboutWindow.show();
                    }
                }
            }
        }
    }

    FileDialog {
        id: openPlist
        selectFolder: false
        nameFilters: ["*.plist"]

        property int type: 1

        onAccepted: {
            var path = null;
            switch(type)
            {
                case 1: {
                    path = openPlist.fileUrl.toString();
                    entitlementsField.text = path.replace("file://", "");
                    break;
                }
            }
        }
    }

    FileDialog {
        id: openDirectory
        selectFolder: false
        nameFilters: ["*.app"]

        property int type: 1

        onAccepted: {
            var path = null;
            switch(type)
            {
                case 2: {
                    path = openDirectory.fileUrl.toString();
                    appPathField.text = path.replace("file://", "");
                    break;
                }
                case 3: {
                    path = openDirectory.fileUrl.toString();
                    qmlFilesPathField.text = path.replace("file://", "");
                    break;
                }
                case 4: {
                    path = openDirectory.fileUrl.toString();
                    qtPathField.text = path.replace("file://", "");
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }


    function checkAllFields()
    {
        var bool = (appPathField.text.length > 0 && qtPathField.text.length > 0);
        btnDeploy.enabled = (bool === true);
    }



    Rectangle {
        id: contentView
        anchors {fill: parent; margins: 10}
        color: "transparent"
        clip: true

        Column {
            id: contentColumn
            width: parent.width
            height: parent.height - 10 - buttonsRow.height
            spacing: 10

            Component.onCompleted: {

                if(qmdManager !== null && qmdManager.settings !== null)
                {
                    qtPathField.text = qmdManager.settings.qtFolder;
                }
            }

            Row {
                id: certificateRow
                width: parent.width
                height: certificateField.height

                Label {
                    id: certificateLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "Mac Developer Certificate "
                }

                TextField {
                    id: certificateField
                    width: parent.width - certificateLabel.width
                    placeholderText: "3rd Party Mac Developer Application: <your ID>"

                    onTextChanged: {
                        checkAllFields();
                        installCertificateField.enabled = (certificateField.text.length > 0);
                        entitlementsField.enabled = (certificateField.text.length > 0);
                        btnBrowseEntitlements.enabled = (certificateField.text.length > 0);
                    }
                }
            }

            Row {
                id: installCertificateRow
                width: parent.width
                height: installCertificateField.height

                Label {
                    id: installCertificateLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "Mac Install Certificate "
                }

                TextField {
                    id: installCertificateField
                    enabled: false
                    width: parent.width - installCertificateLabel.width
                    placeholderText: "3rd Party Mac Developer Installer: <your ID>"

                    onTextChanged: {
                        checkAllFields();
                    }
                }
            }

            Row {
                id: entitlementsRow
                width: parent.width
                height: entitlementsField.height

                Label {
                    id: entitlementsLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "Entitlements Path "
                }

                TextField {
                    id: entitlementsField
                    enabled: false
                    width: parent.width - entitlementsLabel.width - btnBrowseEntitlements.width

                    onTextChanged: {
                        checkAllFields();
                    }
                }

                Button {
                    id: btnBrowseEntitlements
                    height: parent.height
                    enabled: false
                    text: "..."

                    onClicked: {
                        openPlist.type = 1;
                        openPlist.nameFilters = ["Entitlements.plist"];
                        openPlist.setSelectFolder(false);
                        openPlist.open();
                    }
                }
            }

            Row {
                id: appPathRow
                width: parent.width
                height: appPathField.height

                Label {
                    id: appPathLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "Application Path "
                }

                TextField {
                    id: appPathField
                    width: parent.width - appPathLabel.width - btnBrowse.width

                    onTextChanged: {
                        checkAllFields();
                    }
                }

                Button {
                    id: btnBrowse
                    height: parent.height
                    text: "..."

                    onClicked: {
                        openDirectory.type = 2;
                        openDirectory.nameFilters = ["*.app"]
                        openDirectory.setSelectFolder(false);
                        openDirectory.open();
                    }
                }
            }

            Row {
                id: qmlFilesPathRow
                width: parent.width
                height: qmlFilesPathField.height

                Label {
                    id: qmlFilesPathLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "QML Files Path (optional) "
                }

                TextField {
                    id: qmlFilesPathField
                    width: parent.width - qmlFilesPathLabel.width - btnBrowseQml.width
                }

                Button {
                    id: btnBrowseQml
                    height: parent.height
                    text: "..."

                    onClicked: {
                        openDirectory.type = 3;
                        openDirectory.nameFilters = ["*"]
                        openDirectory.setSelectFolder(true);
                        openDirectory.open();
                    }
                }
            }

            Row {
                id: qtPathRow
                width: parent.width
                height: qtPathField.height

                Label {
                    id: qtPathLabel
                    width: 200
                    height: parent.height
                    verticalAlignment: Qt.AlignVCenter
                    text: "Qt Install Folder "
                }

                TextField {
                    id: qtPathField
                    width: parent.width - qtPathLabel.width - btnBrowseQt.width

                    onTextChanged: {
                        checkAllFields();
                    }
                }

                Button {
                    id: btnBrowseQt
                    height: parent.height
                    text: "..."

                    onClicked: {
                        openDirectory.type = 4;
                        openDirectory.nameFilters = ["*"]
                        openDirectory.setSelectFolder(true);
                        openDirectory.open();
                    }
                }
            }

            GroupBox {
                id: consoleGroup
                width: parent.width
                height: parent.height - (qtPathRow.height + qtPathRow.y + 10);
                title: "Console "

                TextArea {
                    id: consoleView
                    anchors.fill: parent
                    readOnly: true
                }
            }
        }

        BusyIndicator {
            id: spinnerView
            anchors {left: parent.left; bottom: parent.bottom}
            width: 20
            height: 20
            running: false
        }

        Row {
            id: buttonsRow
            anchors {top: contentColumn.bottom; topMargin: 10; right: parent.right}
            width: btnDeploy.width + 10 + saveDeplotScript.width
            spacing: 10

            CheckBox {
                id: saveDeplotScript
                anchors.verticalCenter: parent.verticalCenter
                checked: false
                text: "Save Deploy Script"
            }

            Button {
                id: btnDeploy
                text: "Deploy"
                enabled: false

                onClicked: {
                    if(appPathField.text.length > 0 && qtPathField.text.length > 0)
                    {
                        spinnerView.running = true;
                        btnDeploy.enabled = false;
                        qmdManager.settings.certificate = certificateField.text;
                        qmdManager.settings.installCertificate = installCertificateField.text;
                        qmdManager.settings.entitlements = entitlementsField.text.replace(" ", "\ ");
                        qmdManager.settings.appPath = appPathField.text.replace(" ", "\ ");
                        qmdManager.settings.qmlFilesPath = qmlFilesPathField.text.replace(" ", "\ ");
                        qmdManager.settings.qtFolder = qtPathField.text.replace(" ", "\ ");
                        qmdManager.startDeploy(saveDeplotScript.checked);
                    }
                }
            }
        }
    }

    QmdManager {
        id: qmdManager
        settings: QmdSettings {}

        onConsoleMessageDidChange: {
            consoleView.text = msg;
        }

        onDeployDidFinish: {
            btnDeploy.enabled = true;
            spinnerView.running = false;
        }
    }
}
