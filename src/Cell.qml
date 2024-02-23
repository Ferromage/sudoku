import QtQuick 2.15

Rectangle {
    id: _tile
    color: "white"
    property alias text: _text.text

    border {
        width: 1
        color: "grey"
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
