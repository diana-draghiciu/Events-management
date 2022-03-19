#pragma once
#include <QAbstractTableModel>
#include "UserController.h"

class TableModel: public QAbstractTableModel
{
private:
	UserController* user_serv;

public:
	TableModel(UserController* r, QObject* parent = NULL) : QAbstractTableModel{ parent },user_serv{ r } {};

	// number of rows
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	// number of columns
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	// Value at a given position
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	// add header data
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void update() { beginResetModel(); endResetModel(); }

	// used to set certain properties of a cell
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};


