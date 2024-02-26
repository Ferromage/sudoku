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

int GameModel::position() const {
    return m_currentPosition ? m_currentPosition.value() : -1;
}

Q_INVOKABLE void GameModel::setPosition(int position) {
    if (0 <= position && position < (int)m_data.size()) {
        if ((m_currentPosition && m_currentPosition.value() != position) || !m_currentPosition) {
            m_currentPosition = position;
            emit positionChanged();
        }
    }
}

Q_INVOKABLE void GameModel::handleKey(Qt::Key key) {
    if (!m_currentPosition) {
        m_currentPosition = 0;
        emit positionChanged();
        return;
    }

    if (key == Qt::Key::Key_Up) {
        if (m_currentPosition.value() - dimension() >= 0) {
            m_currentPosition.value() -= dimension();
            emit positionChanged();
        }
    } else if (key == Qt::Key::Key_Down) {
        if (m_currentPosition.value() + dimension() < 81) {
            m_currentPosition.value() += dimension();
            emit positionChanged();
        }
    } else if (key == Qt::Key::Key_Left) {
        if (m_currentPosition.value() % dimension() != 0) {
            m_currentPosition.value() -= 1;
            emit positionChanged();
        }
    } else if (key == Qt::Key::Key_Right) {
        if ((m_currentPosition.value() + 1) % dimension() != 0) {
            m_currentPosition.value() += 1;
            emit positionChanged();
        }
    }
}
