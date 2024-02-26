#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include <optional>

class GameModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int position READ position
                            NOTIFY positionChanged)

public:
    explicit GameModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int dimension() const;

    int position() const;
    Q_INVOKABLE void setPosition(int position);
    Q_INVOKABLE void handleKey(Qt::Key key);

signals:
    void positionChanged();

private:
    std::optional<int> m_currentPosition;
    std::vector<int> m_data;
};
