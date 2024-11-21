import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs


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
            height: 100
            color: index % 2 === 0 ? "#FFFFFF" : "#F3F3F3"
            radius: 5
            border.color: "#3D318E"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 5

                Text {
                    text: "Site: " + model.site
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    text: "Login: " + model.login
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    text: "Password: " + model.password
                    Layout.fillWidth: true
                    color: "#3D318E"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignRight
                    spacing: 10

                    Button {
                        text: "Edit"
                        Layout.preferredWidth: 80
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
                        Layout.preferredWidth: 80
                        background: Rectangle {
                            color: "#3D318E"
                            radius: 5
                            border.color: "#3D318E"
                        }
                        onClicked: {
                            confirmDeleteDialog.index = index
                            confirmDeleteDialog.open()
                        }
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
        onClicked: {
            addDialog.open()
        }
        background: Rectangle {
            color: "#3D318E"
            radius: 5
        }
    }

    Button {
        id: togglePasswordVisibilityButton
        text: "👁️"
        anchors.bottom: parent.bottom
        anchors.right: addButton.left
        anchors.bottomMargin: 20
        anchors.rightMargin: 10
        width: 30
        height: 30

        property bool passwordsVisible: false

        background: Rectangle {
            color: "#3D318E"
            radius: 5
        }

        onClicked: {
            passwordsVisible = !passwordsVisible
            updatePasswordDisplay()
        }

        function updatePasswordDisplay() {
            for (var i = 0; i < passwordsModel.count; i++) {
                var item = passwordsModel.get(i)
                passwordsModel.set(i, {
                                       "site": item.site,
                                       "login": item.login,
                                       "password": passwordsVisible
                                                   ? manager.getPassword(i)
                                                   : "*".repeat(8)
                                   })
            }
        }

        Component.onCompleted: {
            updatePasswordDisplay()
        }
    }

    MessageDialog {
        id: duplicateMessage
        title: "Duplicate Entry"
        text: "This site and login already exist in the system. Look closely!"
        onAccepted: console.log("Duplicate warning acknowledged.")
    }

    MessageDialog {
        id: confirmDeleteDialog
        title: "Confirm Deletion"
        text: "Are you sure you want to delete this entry?"
        property int index: -1


        buttons: MessageDialog.Ok | MessageDialog.Cancel

        onAccepted: {
            manager.deletePassword(index)
        }

        onRejected: {
            console.log("Deletion cancelled")
        }
    }

    Dialog {
        id: addDialog
        title: "Add Password"
        anchors.centerIn: parent
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
                text: "Show Password"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if (newPassword.echoMode === TextInput.Password) {
                        newPassword.echoMode = TextInput.Normal;
                    } else {
                        newPassword.echoMode = TextInput.Password;
                    }
                }
            }

            Button {
                text: "Add"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if(manager.isDuplicate(newSite.text, newLogin.text)){
                        duplicateMessage.open()
                        return;
                    }

                    manager.addPassword(
                                newSite.text,
                                newLogin.text,
                                newPassword.text
                                )
                    newSite.text = "";
                    newLogin.text = "";
                    newPassword.text = "";
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
                text: "Show Password"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if (editPassword.echoMode === TextInput.Password) {
                        editPassword.echoMode = TextInput.Normal;
                    } else {
                        editPassword.echoMode = TextInput.Password;
                    }
                }
            }

            Button {
                text: "Save"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if(manager.isDuplicate(editSite.text, editLogin.text, editDialog.index)){
                        duplicateMessage.open()
                        return;
                    }
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
        var savedPasswords = manager.getPasswords()
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
        function onPasswordAdded(site, login, password) {
            passwordsModel.append({
                                      "site": site,
                                      "login": login,
                                      "password": password
                                  })

            var lastIndex = passwordsModel.count - 1;
            if (lastIndex > 0) {
                var previousItem = passwordsModel.get(lastIndex - 1);

                if (previousItem.password === "*".repeat(8)) {
                    passwordsModel.set(lastIndex, {
                                           "site": site,
                                           "login": login,
                                           "password": "*".repeat(8)
                                       });
                }
            }
        }

        function onPasswordEdited(index, site, login, password) {
            passwordsModel.set(index, {
                                   "site": site,
                                   "login": login,
                                   "password": password
                               })
        }

        function onPasswordDeleted(index) {
            passwordsModel.remove(index)
        }
    }
}
