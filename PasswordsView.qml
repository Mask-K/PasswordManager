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
                        passwordsModel.remove(index)
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
                    passwordsModel.append({
                                              "site": newSite.text,
                                              "login": newLogin.text,
                                              "password": newPassword.text
                                          })
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
                    passwordsModel.set(editDialog.index, {
                                           "site": editSite.text,
                                           "login": editLogin.text,
                                           "password": editPassword.text
                                       })
                    editDialog.close()
                }
            }
        }
    }

    ListModel {
        id: passwordsModel
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
        ListElement { site: "example.com"; login: "user1"; password: "pass1" }
        ListElement { site: "example.org"; login: "user2"; password: "pass2" }
    }
}
