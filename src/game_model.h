#pragma once

#include "matrix.h"
#include "matrix_storage.h"
#include <QObject>
#include <QAbstractListModel>
#include <QTimer>
#include <vector>
#include <optional>

class GameModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int position READ position NOTIFY positionChanged)
    Q_PROPERTY(bool isGameInProgress READ isGameInProgress)

public:
    explicit GameModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

    int dimension() const;
    int position() const;
    bool isGameInProgress() const;

    Q_INVOKABLE void setPosition(int position);
    Q_INVOKABLE void handleKey(Qt::Key key);
    Q_INVOKABLE void startNewGame(int level); //level: 0..2
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE void loadGame();

signals:
    void positionChanged();
    void gameOver(bool isSuccess, int totalSeconds);
    void currentTime(int elapsedSeconds);
    void gameWasSaved(bool isSuccess);
    void gameLoadError();

private:
    enum class State {Idle, GameInProgress, GameOver};

    std::pair<size_t, size_t> convertPositionToMatrixCoordinates(int position) const;

    enum Roles {
        ValueRole = Qt::UserRole + 1,
        AttributeRole
    };

    std::optional<int> m_currentPosition;
    Matrix m_data;
    State m_state;
    QTimer *m_timer;
    int m_elapsedSeconds;
};
