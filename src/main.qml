import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Window {
    id: _root
    width: 600
    height: 600
    visible: true
    title: "Sudoku"    

    ColumnLayout {
        spacing: 20
        anchors.fill: parent
        anchors.margins: 10

        Board {
            id: _board

            Layout.preferredWidth: 480
            Layout.preferredHeight: 480
            Layout.minimumWidth: Math.min(Layout.preferredWidth, _root.width)
            Layout.minimumHeight: Math.min(Layout.preferredHeight, _root.height)
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ControlPanel {
            id: _control
            onNewGame: {
                if (_board.isGameInProgress) {
                    _dialog.text = "Вы действительно хотите закончить<br>текущую игру и начать новую?"
                } else {
                    _dialog.text = "Начать новую игру?"
                }
                _dialog.visible = true
            }
        }
    }

    MessageDialog {
        id: _dialog
        visible: false
        modality: Qt.WindowModal
        title: "Start new game"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: _board.startNewGame(_control.level)
    }
}
