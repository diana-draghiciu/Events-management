#include "TableModel.h"

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->user_serv->getElems().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	// get the events
	std::vector<Event> events = this->user_serv->getElems();

	// Allow adding in the table
	// this is to show an empty row at the end of the table - to allow adding new events
	if (row == events.size())
	{
		return QVariant();
	}

	// get the event from the current row
	Event e = events[row];
	std::string aux;
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(e.getTitle());
		case 1:
			return QString::fromStdString(e.getDescription());
		case 2:
			return QString::fromStdString(e.getLink());
		case 3:
			return QString::fromStdString(std::to_string(e.getNr()));
		case 4:
			aux = std::to_string(e.getDate().day) + "/" + std::to_string(e.getDate().month) + "/" + std::to_string(e.getDate().year);
			return QString::fromStdString(aux);
		case 5:
			if(e.getDate().minutes<10)
				aux= std::to_string(e.getDate().hours) + ":0" + std::to_string(e.getDate().minutes);
			else
				aux = std::to_string(e.getDate().hours) + ":" + std::to_string(e.getDate().minutes);
			return QString::fromStdString(aux);
		default:
			break;
		}
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Description" };
			case 2:
				return QString{ "Link" };
			case 3:
				return QString{ "Nr participants" };
			case 4:
				return QString{ "Date" };
			case 5:
				return QString{ "Time" };
			default:
				break;
			}
		}
	}

	return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

