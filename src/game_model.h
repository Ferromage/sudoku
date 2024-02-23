#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <vector>

class GameModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    //Q_PROPERTY(int hiddenElement READ hiddenElement CONSTANT)

public:
    explicit GameModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int dimension() const;
    //int hiddenElement() const;
    //Q_INVOKABLE void move(int clickedPosition);

private:
    //bool isMovable(int currentPosition) const;

    std::vector<int> m_data;
};
