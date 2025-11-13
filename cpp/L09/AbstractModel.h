#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class CarteTableModel : public QAbstractTableModel {
private:
    std::vector<Carte> carti;
public:
    CarteTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setCarti(const std::vector<Carte>& cartiNou) {
        beginResetModel();
        carti = cartiNou;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return static_cast<int>(carti.size());
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 5;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const Carte& c = carti[index.row()];
            switch (index.column()) {
            case 0: return c.get_id();
            case 1: return QString::fromStdString(c.get_title());
            case 2: return QString::fromStdString(c.get_author());
            case 3: return QString::fromStdString(c.get_genre());
            case 4: return c.get_year();
            }
        }
        return {};
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "ID";
            case 1: return "Title";
            case 2: return "Author";
            case 3: return "Genre";
            case 4: return "Year";
            }
        }
        return {};
    }
};