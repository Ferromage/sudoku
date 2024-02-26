import QtQuick 2.15

Rectangle {
    id: _tile

    property alias text: _text.text

    readonly property color borderColor: "grey"
    readonly property color borderBoldColor: "green"
    readonly property color backColor: "white"
    readonly property color backSelectedColor: "#52a459"

    color: backColor

    border {
        width: 1
        color: borderColor
    }

    Text {
        id: _text
        anchors.centerIn: parent
        text: "1"
        font {
            pointSize: Math.min(parent.width, parent.height) / 2
        }
    }
}
