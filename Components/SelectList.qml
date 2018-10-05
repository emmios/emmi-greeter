import QtQuick 2.0


Rectangle {
    id: selectList
    y: 100
    x: 0
    width: parent.width - 8
    height: 24
    clip: true

    signal change

    property string value: ""
    property alias selected: textSelected
    property int max: 24
    property int initial: 24
    property var lista: []
    property bool show: true

    Rectangle {
        y: 0
        x: 0
        width: parent.width
        height: initial
        Label {
            id: textSelected
            text: "session"
            color: "#333"
            size: 14
            anchors.centerIn: parent
        }
        Label {
            id: seta
            y: (initial / 2) - (seta.size / 3)
            x: (parent.width - width) - 10
            text: "\uf0de"
            color: "#333"
            font.family: "Font Awesome 5 Free"
            size: 16
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (show) {
                    animation.stop()
                    animation.to = max
                    animation.start()
                    seta.text = "\uf0dd"
                    seta.y = (initial / 2) - (seta.size / 2)
                    show = false
                } else {
                    animation.stop()
                    animation.to = initial
                    animation.start()
                    seta.text = "\uf0de"
                    seta.y = (initial / 2) - (seta.size / 3)
                    show = true
                }
            }
        }
    }
    Repeater {
        model: lista

        Rectangle {
            id: item
            y: initial * (index + 1)
            x: 0
            width: parent.width
            height: initial

            Rectangle {
                id: bg
                x: parent.width / 2
                width: 0
                height: initial
                opacity: 1
                color: "#007fff"
            }

            Label {
                text: modelData
                color: "#333"
                size: 14
                anchors.centerIn: parent
            }

            Component.onCompleted: {
                max += initial
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ani.to = 0
                    ani.stop()
                    ani.start()
                    ani2.to = parent.width
                    ani2.stop()
                    ani2.start()
                    ani3.to = 0
                    ani3.stop()
                    ani3.start()

                    time.stop()
                    time.start()

                    textSelected.text = modelData
                    value = modelData
                    change.call()
                }
            }

            Timer {
                id: time
                running: false
                interval: 300
                onTriggered: {
                    bg.x = item.width / 2
                    bg.width = 0
                    bg.opacity = 1

                    animation.stop()
                    animation.to = initial
                    animation.start()
                    seta.y = (initial / 2) - (seta.size / 3)
                    seta.text = "\uf0de"
                    show = true
                }
            }

            PropertyAnimation {id: ani; target: bg; to: 0; properties: 'x'; duration: 300}
            PropertyAnimation {id: ani2; target: bg; to: parent.width; properties: 'width'; duration: 300}
            PropertyAnimation {id: ani3; target: bg; to: 0; properties: 'opacity'; duration: 300}
        }
    }

    function unfocus() {
        animation.stop()
        animation.to = initial
        animation.start()
        seta.y = 5
        seta.text = "\uf0de"
        show = true
    }

    PropertyAnimation {id: animation; target: selectList; to: max; properties: 'height'; duration: 300}
}
