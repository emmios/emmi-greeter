import QtQuick 2.5
import QtGraphicalEffects 1.0
import "Components"

Rectangle {
    id: mainForm
    anchors.fill: parent

    property alias textPassword: textField
    property alias imgUser: user

    Image {
        id: image
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
        antialiasing: true
        source: "file://" + Context.background()
    }

    FastBlur {
        id: fastBlur
        anchors.fill: image
        source: image
        radius: 50
    }

    Image {
        id: user
        y: parent.height / 4
        x: (parent.width / 2) - (width / 2)
        width: 100
        height: 100
        fillMode: Image.PreserveAspectCrop
        antialiasing: true
        visible: false
        source: "file:///usr/share/emmi-greeter/users/" + Context.lastUser() + ".jpg"
    }

    Rectangle {
        x: user.x - 2
        y: user.y - 2
        width: user.width + 4
        height: user.height + 4
        radius: user.width + 4
        color: "transparent"
        border {width: 4; color: "#007fff"}
    }

    OpacityMask {
        anchors.fill: user
        source: user
        maskSource: Rectangle {
            width: user.width
            height: user.height
            radius: user.width
            visible: false // this also needs to be invisible or it will cover up the image
        }
    }

    TextField {
        id: textField
        y: (user.y + user.height) + 30
        x: (parent.width / 2) - (width / 2)
        width: 250
        height: 35
        bg.opacity: 1
        textColor: "#333"
        maxLength: 20
        size: 12
        effectColor: "#007fff"
        text: ""
        password: true

        Keys.onReturnPressed: {
            Context.passwordRespond(text)
        }
    }

    Component.onCompleted: {
        textField.setFocus()
    }
}
