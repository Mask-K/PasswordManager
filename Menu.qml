import QtQuick
import QtQuick.Controls

Rectangle {
    signal loginSuccessful

    width: 400
    height: 300
    color: "#FFFFFF"
    anchors.centerIn: parent
    radius: 10

    Text {
        id: titleText
        text: toggle.checked ? "Register" : "Login"
        font.pixelSize: 24
        color: "#3D318E"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    TextField {
        id: loginField
        placeholderText: "Enter your login"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 80
        width: parent.width * 0.8
        font.pixelSize: 18
        color: "#000000"
        background: Rectangle {
            color: "white"
            radius: 5
            border.color: "#3D318E"
        }
    }

    TextField {
        id: passwordField
        placeholderText: "Enter your password"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: loginField.bottom
        anchors.topMargin: 20
        width: parent.width * 0.8
        font.pixelSize: 18
        echoMode: TextInput.Password
        color: "#000000"

        background: Rectangle {
            color: "white"
            radius: 5
            border.color: "#3D318E"
        }
    }

    CheckBox {
        id: showPasswordCheckBox
        text: "Show password"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: passwordField.bottom
        anchors.topMargin: 10
        onCheckedChanged: {
            passwordField.echoMode = checked ? TextInput.Normal : TextInput.Password
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: showPasswordCheckBox.bottom
        anchors.topMargin: 20

        Text {
            text: "Login"
            font.pixelSize: 16
            color: toggle.checked ? "#AAAAAA" : "#3D318E"
            anchors.verticalCenter: toggle.verticalCenter
        }

        Switch {
            id: toggle
            checked: false
            onCheckedChanged: {
                titleText.text = toggle.checked ? "Register" : "Login"
            }
        }

        Text {
            text: "Register"
            font.pixelSize: 16
            color: toggle.checked ? "#3D318E" : "#AAAAAA"
            anchors.verticalCenter: toggle.verticalCenter
        }
    }

    Button {
        id: confirm
        text: toggle.checked ? "Register" : "Login"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: parent.width * 0.5

        enabled: loginField.text.length > 0 && passwordField.text.length > 0

        background: Rectangle {
            color: confirm.enabled ? "#3D318E" : "#818181"
            radius: 5
        }

        onClicked: {
            if (toggle.checked) {
                if (authenticator.regist(loginField.text, passwordField.text)) {
                    console.log("Registration successful")
                    manager.addKey(passwordField.text)
                    loginSuccessful()
                } else {
                    console.log("Registration failed")
                }
            } else {
                if (authenticator.login(loginField.text, passwordField.text)) {
                    console.log("Login successful")
                    manager.addKey(passwordField.text)
                    loginSuccessful()
                } else {
                    console.log("Login failed")
                }
            }
        }
    }
}

