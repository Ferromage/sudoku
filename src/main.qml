import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: _root
    width: 640
    height: 480
    visible: true
    title: "Sudoku"

    Board {
        anchors.fill: parent
    }
}
