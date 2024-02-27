import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: _root
    width: 600
    height: 600
    visible: true
    title: "Sudoku"    

    Board {
        id: _board
        anchors.fill: parent
        anchors.margins: 10
    }
}
