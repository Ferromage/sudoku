#include "game_model.h"
#include <algorithm>
#include <random>
#include <cassert>
#include <QDebug>

GameModel::GameModel(QObject *parent) : QAbstractListModel(parent) {
    m_state = State::Idle;
    m_elapsedSeconds = 0;
    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::PreciseTimer);

    QObject::connect(m_timer, &QTimer::timeout, [this] {
        if (m_state == State::GameInProgress) {
            emit currentTime(++m_elapsedSeconds);
        }
    });
}

int GameModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(m_data.size());
}

QVariant GameModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= rowCount()) {
        return {};
    }
    if (m_state == State::Idle) {
        return "";
    }

    const auto [row, col] = convertPositionToMatrixCoordinates(index.row());
    const auto& item = m_data.getItem(row, col);
    switch (role) {
        case Roles::ValueRole :
            if (item.state() == MatrixItem::State::Hidden) {
                return "";
            }
            return item.value();
        break;
        case Roles::AttributeRole :
            if (item.state() == MatrixItem::State::Hidden) {
                return "hidden";
            } else if (item.state() == MatrixItem::State::Generated) {
                return "generated";
            } else if (m_state == State::GameOver) {
                if (item.isGuessed()) {
                    return "user_setted";
                } else {
                    return "user_wrong";
                }
            }
            return "user_setted";
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
    assert(m_data.columns() == m_data.rows());
    return static_cast<int>(m_data.columns());
}

int GameModel::position() const {
    return m_currentPosition ? m_currentPosition.value() : -1;
}

bool GameModel::isGameInProgress() const {
    return m_state == State::GameInProgress;
}

Q_INVOKABLE void GameModel::setPosition(int position) {
    if (m_state == State::Idle) {
        return;
    }

    if (0 <= position && position < (int)m_data.size()) {
        if ((m_currentPosition && m_currentPosition.value() != position) || !m_currentPosition) {
            m_currentPosition = position;
            emit positionChanged();
        }
    }
}

Q_INVOKABLE void GameModel::handleKey(Qt::Key key) {
    if (m_state == State::Idle) {
        return;
    }

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
    } else if (Qt::Key::Key_1 <= key && key <= Qt::Key::Key_9 && m_state != State::GameOver) {
        const auto [row, col] = convertPositionToMatrixCoordinates(m_currentPosition.value());
        auto& item = m_data.getItem(row, col);
        if (item.state() != MatrixItem::State::Generated) {
            item.setUserValue(key - Qt::Key::Key_0);
            if (m_data.isFilledByUser()) {
                m_state = State::GameOver;
            }

            if (m_state == State::GameOver) {
                emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0));
                emit gameOver(m_data.isValid(), m_elapsedSeconds);
            } else {
                emit dataChanged(createIndex(m_currentPosition.value(), 0), createIndex(m_currentPosition.value(), 0));
            }
        }
    }
}

Q_INVOKABLE void GameModel::startNewGame(int level) {
    beginResetModel();
    m_currentPosition.reset();
    m_state = State::GameInProgress;
    m_data.reset();
    m_data.shuffle(static_cast<DifficultLevel>(level % 3));
    endResetModel();

    m_elapsedSeconds = 0;
    emit currentTime(m_elapsedSeconds);
    m_timer->start(1000);
}

Q_INVOKABLE void GameModel::saveGame() {
    if (m_state == State::GameInProgress) {
        const auto status = MatrixStorage::saveMatrix(m_data, m_elapsedSeconds);
        emit gameWasSaved(status);
    }
}

Q_INVOKABLE void GameModel::loadGame() {
    Matrix matrix;
    int seconds;
    if (MatrixStorage::loadMatrix(matrix, seconds)) {
        beginResetModel();
        m_currentPosition.reset();
        m_state = State::GameInProgress;
        std::swap(matrix, m_data);
        m_elapsedSeconds = seconds;
        emit currentTime(m_elapsedSeconds);
        m_timer->start(1000);
        endResetModel();
    } else {
        emit gameLoadError();
    }
}

std::pair<size_t, size_t> GameModel::convertPositionToMatrixCoordinates(int position) const {
    std::pair<size_t, size_t> result;
    result.first = position / m_data.columns(); //row
    result.second = position % m_data.rows(); //column
    return result;
}

