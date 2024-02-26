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
    if (!index.isValid() || index.row() >= static_cast<int>(m_data.size())) {
        return {};
    }

    const auto& cell = m_data.at(index.row());
    switch (role) {
        case Roles::ValueRole :
            return cell.m_value;
        break;
        case Roles::AttributeRole :
            return cell.m_attr;
        break;
    }

    return {};
}

QHash<int,QByteArray> GameModel::roleNames() const {
    QHash<int, QByteArray> table;
    table[Roles::ValueRole] = "value";
    table[Roles::AttributeRole] = "attribute";
    return table;
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
