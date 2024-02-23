#include "game_model.h"
#include <algorithm>
#include <random>
#include <QDebug>

GameModel::GameModel(QObject *parent) : QAbstractListModel(parent) {
    m_data.resize(81);
}

int GameModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(m_data.size());
}

QVariant GameModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

//    if (index.row() < 0 || index.row() >= (int)m_data.size()) {
//        return QVariant();
//    }

    return 6;
}

int GameModel::dimension() const {
    return 9;
}

//int GameModel::hiddenElement() const {
//    return static_cast<int>(m_size);
//}

//Q_INVOKABLE void GameModel::move(int clickedPosition) {
//    if (isMovable(clickedPosition)) {
//        std::swap(m_data[m_hiddenElementPos], m_data[clickedPosition]);
//        m_hiddenElementPos = clickedPosition;
//        emit dataChanged(createIndex(0, 0), createIndex(m_data.size() - 1, 0));
//    }
//}

//bool GameModel::isMovable(int pos) const {
//    if (pos < 0 || pos >= (int)m_size || pos == m_hiddenElementPos) {
//        return false;
//    }

//    const bool isLeftPosFree = (pos % m_dimension) != 0 && (pos - 1) == m_hiddenElementPos;
//    const bool isRightPosFree = ((pos + 1) % m_dimension) != 0 && (pos + 1) == m_hiddenElementPos;
//    const bool isUpperPosFree = (pos - m_dimension) >= 0 && (pos - m_dimension) == m_hiddenElementPos;
//    const bool isLowerPosFree = (pos + m_dimension) < m_size && (pos + m_dimension) == m_hiddenElementPos;

//    return isLeftPosFree || isRightPosFree || isUpperPosFree || isLowerPosFree;
//}
