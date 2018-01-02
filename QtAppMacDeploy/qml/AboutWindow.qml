import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

Window {
    id:aboutWindow
    width: 500
    height: 200
    minimumWidth: 500
    minimumHeight: 200
    maximumWidth: 500
    maximumHeight: 200
    color: "#e8e8e8"
    flags: (Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.WindowCloseButtonHint)
    title: "About Qt App Mac Deploy"

    Rectangle {
        id: contentView
        anchors {fill: parent; margins: 10}
        color: "transparent"
        clip: true

        Row {
            id: infoRow
            width: parent.width
            height: parent.height
            spacing: 10

            Image {
                id: icon
                width: 150
                fillMode: Image.PreserveAspectFit
                source: "images/icon_256x256.png"
            }

            Column {
                id: infoContentColumn
                width: parent.width - icon.width - 10
                height: licenseLabel.height + licenseLabel.y
                spacing: 10

                Label {
                    id: appTitleLable
                    width: parent.width
                    height: appTitleLable.contentHeight
                    font {family: "Helvetica Neue"; bold: true; pointSize: 18}
                    text: "Qt App Mac Deploy"
                }

                Label {
                    id: appVersionLable
                    width: parent.width
                    height: appVersionLable.contentHeight
                    font {family: "Helvetica Neue"; pointSize: 14}
                    text: "Version: 1.1.0"
                }

                Label {
                    id: copyrightLabel
                    width: parent.width
                    height: copyrightLabel.contentHeight
                    text: "Copyright 2014 - 2017 Andrew Shapovalov. All rights reserved."
                    verticalAlignment: Qt.AlignVCenter
                    wrapMode: Text.WordWrap
                    font {family: "Helvetica Neue"; pointSize: 14}
                    textFormat: Text.RichText
                }

                Label {
                    id: licenseLabel
                    width: parent.width
                    height: licenseLabel.contentHeight
                    text: "The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."
                    wrapMode: Text.WordWrap
                    verticalAlignment: Qt.AlignVCenter
                    font {family: "Helvetica Neue"; pointSize: 14}
                    textFormat: Text.RichText
                }
            }
        }
    }
}
