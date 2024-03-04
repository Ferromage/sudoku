import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: _root

    signal newGame(int level)

    property alias level: _cmbbox.currentIndex
    property alias time: _label.text

    spacing: 10

    Label {
        id: _label
        text: "00:00:00"
        font.pointSize: 13
        Layout.alignment: Qt.AlignLeft
    }

    Rectangle {
        color: "transparent"
        height: 1
        Layout.fillWidth: true
        Layout.minimumWidth: 5
    }

    Button {
        id: _button
        text: "New game"
        font.pointSize: 13
        onClicked: _root.newGame(_cmbbox.currentIndex)
        KeyNavigation.tab: _cmbbox
    }

    ComboBox {
        id: _cmbbox
        font.pointSize: 13
        model: ["Easy", "Normal", "Hard"]
        KeyNavigation.tab: _board
    }
}
