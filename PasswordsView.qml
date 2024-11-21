import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    color: "#FFFFFF"
    radius: 10

    ListView {
        id: passwordsList
        width: parent.width - 20
        height: parent.height
        anchors.fill: parent
        anchors.margins: 20
        model: passwordsModel
        delegate: Rectangle {
            id: passwordEntry
            width: parent.width
            height: 50
            color: index % 2 === 0 ? "#FFFFFF" : "#F3F3F3"
            radius: 5
            border.color: "#3D318E"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: model.site
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                }

                Text {
                    text: model.login
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                }

                Text {
                    text: model.password
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                }

                Button {
                    text: "Edit"

                    background: Rectangle {
                        color: "#3D318E"
                        radius: 5
                        border.color: "#3D318E"
                    }
                    onClicked: {
                        editDialog.site = model.site
                        editDialog.login = model.login
                        editDialog.password = model.password
                        editDialog.index = index
                        editDialog.open()
                    }
                }

                Button {
                    text: "Delete"

                    background: Rectangle {
                        color: "#3D318E"
                        radius: 5
                        border.color: "#3D318E"
                    }
                    onClicked: {
                        manager.deletePassword(index)
                    }
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            id: verticalScrollBar
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 12
            policy: ScrollBar.AlwaysOn
            orientation: Qt.Vertical
        }
    }

    Button {
        id: addButton
        text: "Add Password"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        onClicked: addDialog.open()
    }

    Dialog {
        id: addDialog
        title: "Add Password"

        ColumnLayout {
            spacing: 10
            anchors.margins: 20

            TextField {
                id: newSite
                placeholderText: "Site"
                Layout.fillWidth: true
            }

            TextField {
                id: newLogin
                placeholderText: "Login"
                Layout.fillWidth: true
            }

            TextField {
                id: newPassword
                placeholderText: "Password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
            }

            Button {
                text: "Add"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    manager.addPassword(
                        newSite.text,
                        newLogin.text,
                        newPassword.text
                    )
                    addDialog.close()
                }
            }
        }
    }

    Dialog {
        id: editDialog
        title: "Edit Password"
        anchors.centerIn: parent
        property string site
        property string login
        property string password
        property int index

        ColumnLayout {
            spacing: 10
            anchors.margins: 20

            TextField {
                id: editSite
                placeholderText: "Site"
                text: editDialog.site
                Layout.fillWidth: true
            }

            TextField {
                id: editLogin
                placeholderText: "Login"
                text: editDialog.login
                Layout.fillWidth: true
            }

            TextField {
                id: editPassword
                placeholderText: "Password"
                echoMode: TextInput.Password
                text: editDialog.password
                Layout.fillWidth: true
            }

            Button {
                text: "Save"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    manager.editPassword(
                        editSite.text,
                        editLogin.text,
                        editPassword.text,
                        editDialog.index
                    )
                    editDialog.close()
                }
            }
        }
    }

    ListModel {
        id: passwordsModel
    }

    Component.onCompleted: {

        var savedPasswords = manager.getPasswords2()
        for (var i = 0; i < savedPasswords.length; i++) {
            passwordsModel.append({
                "site": savedPasswords[i].site,
                "login": savedPasswords[i].login,
                "password": savedPasswords[i].password
            })
        }
    }

    Connections {
        target: manager
        function onPasswordsUpdated() {

            passwordsModel.clear()
            var passwords = manager.getPasswords2()
            for (var i = 0; i < passwords.length; i++) {
                passwordsModel.append({
                    "site": passwords[i].site,
                    "login": passwords[i].login,
                    "password": passwords[i].password
                })
            }
        }
    }
}
