import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: _root

    signal newGame(int level)
    property alias level: _cmbbox.currentIndex

    spacing: 10
    Layout.alignment: Qt.AlignRight

    Button {
        id: _button
        text: "New game"
        font.pointSize: 13
        onClicked: _root.newGame(_cmbbox.currentIndex)
        focusPolicy: Qt.NoFocus
    }

    ComboBox {
        id: _cmbbox
        font.pointSize: 13
        model: ["Easy", "Normal", "Hard"]
        focusPolicy: Qt.NoFocus
    }
}
