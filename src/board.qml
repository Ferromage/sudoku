import QtQuick 2.15
import game_cxx_model 1.0

GridView {
    id: _view

    model: GameCxxModel {
        id: _model
    }

    cellWidth: width / _model.dimension
    cellHeight: height / _model.dimension

    delegate: Item {
        width: cellWidth
        height: cellHeight
        visible: true

        Cell {
            id: _cell
            anchors.fill: parent
            text: display

            MouseArea {
                anchors.fill: parent
                //onClicked: _model.move(index);
                onClicked: {
                    console.log(index)
                }
            }
        }

        Rectangle {
            id: _border

            visible: {index % 3 == 0}
            color: "green" //_cell.border.color
            width: _cell.border.width * 4
            height: _cell.height
            x: -width / 2
        }

        Rectangle {
            visible: {
                index === 8 || index === 17 || index === 26 ||
                index === 35 || index === 44 || index === 53 ||
                index === 62 || index === 71 || index === 80
            }
            color: _border.color
            width: _border.width
            height: _cell.height
            x: _cell.width - width / 2
        }

        Rectangle {
            visible: {
                (index >= 0 && index <= 8) ||
                (index >= 27 && index <= 35) ||
                (index >= 54 && index <= 62)
            }

            color: _border.color
            width: _cell.width
            height: _border.width
            y: -height / 2
        }

        Rectangle {
            visible: {index >= 72 && index <= 80}
            color: _border.color
            width: _cell.width
            height: _border.width
            y: _cell.height - height / 2
        }
    }
}

