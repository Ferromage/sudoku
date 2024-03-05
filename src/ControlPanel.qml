import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: _root

    signal newGame(int level)
    signal saveGame()
    signal loadGame()

    property alias level: _cmbbox.currentIndex
    property alias time: _label.text
    property alias saveEnabled: _buttonSaveGame.enabled

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
        id: _buttonNewGame
        text: "New game"
        font.pointSize: 13
        onClicked: _root.newGame(_cmbbox.currentIndex)
        KeyNavigation.tab: _cmbbox
        Layout.preferredWidth: 110        
    }

    ComboBox {
        id: _cmbbox
        font.pointSize: 13
        model: ["Easy", "Normal", "Hard"]
        KeyNavigation.tab: _buttonSaveGame
        Layout.preferredWidth: 110
    }

    Button {
        id: _buttonSaveGame
        text: "Save"
        font.pointSize: 13
        onClicked: _root.saveGame()
        KeyNavigation.tab: _buttonLoadGame
        Layout.preferredWidth: 110
        enabled: false
    }

    Button {
        id: _buttonLoadGame
        text: "Load"
        font.pointSize: 13
        onClicked: _root.loadGame()
        KeyNavigation.tab: _board
        Layout.preferredWidth: 110
    }
}
