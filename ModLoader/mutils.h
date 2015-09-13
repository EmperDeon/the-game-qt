#ifndef MUTILS_H
#define MUTILS_H

#include <QtCore>
#include <QtWidgets>
#include <mmodloader.h>

class ModLoader;

class MListModel : public QAbstractListModel{
private:
	QJsonArray obj;
public:
	MListModel(const QJsonArray &o, QObject* pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	int rowCount(const QModelIndex& = QModelIndex()) const;
	QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void add(QString k);
	void del(QListView *i);
};
class MTableModel :public QAbstractTableModel{
private:
	QJsonObject& obj;
public:
	MTableModel(QJsonObject& o, QObject *pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
	void add(QString k, QString v);
	void del(QString k);
};
class MListManager : public QWidget{
	Q_OBJECT

	MListModel* model;
	QListView* list;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QLineEdit* e_k;
	QPushButton* b_add;
	QPushButton* b_del;
	QPushButton* b_ok;

public slots:
	void add();
	void del();
public:
	MListManager(QJsonArray& o, QString t);

};
class MTableManager : public QWidget{
	Q_OBJECT

	MTableModel* model;
	QTableView* table;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QLineEdit* e_k;
	QLineEdit* e_v;
	QPushButton* b_add;

	QPushButton* b_del;
	QPushButton* b_ok;

public slots:
	void add();
	void del();
public:
	MTableManager(QJsonObject& o, QString t);

};

class MModsList : public QObject{
	Q_OBJECT

	ModLoader* loader;
	QJsonArray* list;

	void update();
	void fillList();
	void addToList(QJsonObject);
	bool contains(QString);
	void disable(QString n);
public:
	QJsonArray lst;

	MModsList(ModLoader*);
	void addNew();
	void load();
	void save();
	void reload();

};
#endif // MUTILS_H
