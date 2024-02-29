import QtQuick 2.15
import game_cxx_model 1.0

Rectangle {
    id: _root

    function startNewGame(level) {
        _model.startNewGame(level)
    }

    GridView {
        id: _view
        focus: true
        anchors.fill: parent

        model: GameCxxModel {
            id: _model
        }

        cellWidth: width / _model.dimension
        cellHeight: height / _model.dimension

        Keys.onPressed: _model.handleKey(event.key)

        delegate: Item {
            width: _view.cellWidth
            height: _view.cellHeight
            visible: true

            Cell {
                id: _cell
                anchors.fill: parent
                text: value
                textColor: {
                    if (attribute === "user_setted") {
                        return _cell.userTextColor
                    } else if (attribute === "user_wrong") {
                        return _cell.userTextColorWrong
                    }
                    return _cell.defaultTextColor
                }
                color: _model.position === index ? backSelectedColor : backColor

                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        _model.setPosition(index);
                    }
                }
            }

            Rectangle {
                id: _border

                visible: {index % 3 == 0}
                color: _cell.borderBoldColor
                width: _cell.border.width * 4
                height: _cell.height + 4
                x: -width / 2
                y: -2
            }

            Rectangle {
                visible: {
                    index === 8 || index === 17 || index === 26 ||
                    index === 35 || index === 44 || index === 53 ||
                    index === 62 || index === 71 || index === 80
                }
                color: _border.color
                width: _border.width
                height: _cell.height + 4
                x: _cell.width - width / 2
                y: -2
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
}
