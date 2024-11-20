import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    visibility: ApplicationWindow.Maximized
    title: "Password Manager"

    color: "#3D318E"

    Loader {
        id: viewLoader
        anchors.fill: parent
        source: "Menu.qml"

        Connections {
            target: viewLoader.item
            function onLoginSuccessful() {
                switchToPasswordsView();
            }
        }
    }

    function switchToPasswordsView() {
        viewLoader.source = "PasswordsView.qml";
    }
}
