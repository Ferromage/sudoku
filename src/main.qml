import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Window {
    id: _root
    width: 600
    height: 600
    minimumWidth: 600
    minimumHeight: 600

    visible: true
    title: "Sudoku"    

    function secondsToString(seconds) {
        var ss = Math.floor(seconds % 60)
        var mm = Math.floor((seconds / 60) % 60)
        var hh = Math.floor(seconds / 3600)
        if (ss < 10) {
            ss = "0" + ss.toLocaleString()
        }
        if (mm < 10) {
            mm = "0" + mm.toLocaleString()
        }
        if (hh < 10) {
            hh = "0" + hh.toLocaleString()
        }
        return hh + ":" + mm + ":" + ss
    }

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

            onGameOver: {
                if (status) {
                    _dialogInfo.text = "Вы выиграли! Ваш результат: " + _root.secondsToString(seconds)
                } else {
                    _dialogInfo.text = "Вы проиграли"
                }
                _dialogInfo.title = "Игра окончена"
                _dialogInfo.visible = true
                _control.saveEnabled = false
            }

            onCurrentTime: {
                _control.time = _root.secondsToString(seconds)
            }

            onGameWasSaved: {
                _dialogInfo.text = status ? "Игра сохранена" : "Не удалось сохранить игру"
                _dialogInfo.title = "Сохранение"
                _dialogInfo.visible = true
            }

            onGameLoadError: {
                _dialogInfo.text = "Не удалось загрузить игру"
                _dialogInfo.title = "Загрузка"
                _dialogInfo.visible = true
            }
        }

        ControlPanel {
            id: _control

            onNewGame: {
                if (_board.isGameInProgress) {
                    _dialogNewGame.text = "Вы действительно хотите закончить<br>текущую игру и начать новую?"
                } else {
                    _dialogNewGame.text = "Начать новую игру?"
                }
                _dialogNewGame.visible = true
            }

            onSaveGame: {
                _board.saveGame()
            }

            onLoadGame: {
                if (_board.isGameInProgress) {
                    _dialogLoadGame.text = "Вы действительно хотите закончить<br>текущую игру и загрузить предыдущую?"
                } else {
                    _dialogLoadGame.text = "Загрузить предыдущую игру?"
                }
                _dialogLoadGame.visible = true
            }
        }
    }

    MessageDialog {
        id: _dialogNewGame
        visible: false
        modality: Qt.WindowModal
        title: "Начать новую игру"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            _board.startNewGame(_control.level)
            _board.focus = true
            _control.saveEnabled = true
        }
    }

    MessageDialog {
        id: _dialogLoadGame
        visible: false
        modality: Qt.WindowModal
        title: "Загрузить предыдущую игру"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            _board.loadGame()
            _board.focus = true
            _control.saveEnabled = true
        }
        onNo: {
            _board.focus = true
        }
    }

    MessageDialog {
        id: _dialogInfo
        visible: false
        modality: Qt.WindowModal        
        standardButtons: StandardButton.Ok
        onAccepted: {
            _board.focus = true
        }
    }
}
