import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Password Manager"

    // Основний колір
    color: "#3D318E"

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#FFFFFF"
        anchors.centerIn: parent
        radius: 10

        // Заголовок форми з динамічним текстом
        Text {
            id: titleText
            text: toggle.checked ? "Register" : "Login"
            font.pixelSize: 24
            color: "#3D318E"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }

        // Поле вводу для логіна
        TextField {
            id: loginField
            placeholderText: "Enter your login"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 80
            width: parent.width * 0.8
            font.pixelSize: 18

            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "#3D318E"
            }
        }

        // Поле вводу для пароля
        TextField {
            id: passwordField
            placeholderText: "Enter your password"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: loginField.bottom
            anchors.topMargin: 20
            width: parent.width * 0.8
            font.pixelSize: 18
            echoMode: TextInput.Password

            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "#3D318E"
            }
        }

        // Toggle Switch для перемикання між режимами
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: passwordField.bottom
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

            // Кнопка активна лише коли обидва поля не порожні
            enabled: loginField.text.length > 0 && passwordField.text.length > 0

            background: Rectangle {
                color: confirm.enabled ? "#3D318E" : "#818181"
                radius: 5
            }

            onClicked: {
                if (toggle.checked) {
                    if (authenticator.regist(loginField.text, passwordField.text)) {
                        console.log("Registration successful")
                    } else {
                        console.log("Registration failed")
                    }
                } else {
                    if (authenticator.login(loginField.text, passwordField.text)) {
                        console.log("Login successful")
                    } else {
                        console.log("Login failed")
                    }
                }
            }
        }
    }
}

