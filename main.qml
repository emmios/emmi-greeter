import QtQuick 2.5
import QtQuick.Window 2.2
import "Components"


App {
    id: main
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Emmi Greeter")
    //flags: Qt.FramelessWindowHint

    property int efeito1: 300

    MainForm {
        id: mainForm
        anchors.fill: parent

        property bool show: true

        Label {
            x: (mainForm.width - width) - 40
            y: (mainForm.height - height) - 130
            text: Context.date()
            color: "#fff"
            size: 18
            opacity: 0.8
        }

        Label {
            x: (mainForm.width - width) - 70
            y: (mainForm.height - height) - 40
            text: Context.time().split("-")[0]
            color: "#fff"
            size: 78
            opacity: 0.7
        }

        Label {
            x: (mainForm.width - width) - 40
            y: (mainForm.height - height) - 55
            text: Context.time().split("-")[1]
            color: "#fff"
            size: 18
            opacity: 0.8
        }

        Rectangle {
            id: menu
            x: parent.width
            y: 0
            width: 200
            height: parent.height
            color: "transparent"

            MouseArea {

                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    sessions.unfocus()
                    users.unfocus()
                }

                onExited: {
                    menu.x = mainForm.width
                    show = true
                    sessions.unfocus()
                    users.unfocus()
                }
            }

            Rectangle {
                anchors.fill: parent
                opacity: 0.5
                color: "#000"
            }

            Label {x: 12; y: 100; text: 'Session:'; size: 14; color: "#fff"}
            SelectList {
                id: sessions
                selected.text: Context.lastSession()
                y: 118
                x: 12
                height: 30
                initial: 30
                max: 30
                width: menu.width - 20
                lista: Context.sessions()

                onChange: {
                    Context.session(value)
                }
            }

            Label {x: 12; y: 130 + sessions.height; text: 'User:'; size: 14; color: "#fff"}
            SelectList {
                id: users
                selected.text: Context.lastUser()
                y: 148 + sessions.height
                x: 12
                height: 30
                initial: 30
                max: 30
                width: menu.width - 20
                lista: Context.users()

                onChange: {
                    mainForm.imgUser.source = "file:///usr/share/emmi-greeter/users/" + value + ".jpg"
                    Context.userChange(value)
                }

                Component.onCompleted: {
                    Context.userChange(Context.lastUser())
                }
            }

            Label {
                x: (parent.width / 2) - (width / 2)
                y: parent.height - (height + 20)
                text: "\uf011"
                font.family: "Font Awesome 5 Free"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Context.power()
                    }
                }
            }
        }

        Rectangle {
            x: parent.width - 36
            y: 10
            width: 24
            height: 26
            color: "transparent"
            z: 9
            Rectangle {x: 0; y: 3; width: parent.width; height: 3}
            Rectangle {x: 0; y: 11; width: parent.width; height: 3}
            Rectangle {x: 0; y: 19; width: parent.width; height: 3}
            MouseArea {

                anchors.fill: parent

                onClicked: {
                    if (show) {
                        menu.x = mainForm.width - 200
                        show = false
                    } else {
                        menu.x = mainForm.width
                        show = true
                    }
                    sessions.unfocus()
                    users.unfocus()
                }   
            }
        }
    }

    function clearPassword() {
        mainForm.textPassword.text = ""
        mainForm.textPassword.setFocus()
    }
}
