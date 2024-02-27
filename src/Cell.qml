import QtQuick 2.15

Rectangle {
    id: _tile

    property alias text: _text.text
    property alias textColor: _text.color

    readonly property color borderColor: "grey"
    readonly property color borderBoldColor: "green"
    readonly property color backColor: "white"
    readonly property color backSelectedColor: "#b373bf78"
    readonly property color defaultTextColor: "grey"
    readonly property color userTextColor: "blue"

    color: backColor

    border {
        width: 1
        color: borderColor
    }

    Text {
        id: _text
        anchors.centerIn: parent
        text: ""
        color: defaultTextColor
        font {
            pointSize: Math.min(parent.width, parent.height) / 2
        }
    }
}
