#ifndef GLOBALQT_LWMODELS_H
#define GLOBALQT_LWMODELS_H
#include <Launcher/ldefines.h>
#include <Launcher/widgets/lmodeditor.h>

class LTextModWidgetEditor;


class LModLoaderSelect : public QAbstractTableModel{
private:
	QMap<QString, QString>& mp;
public:
	LModLoaderSelect(QMap<QString, QString>& m , QObject *pobj = 0);

	QVariant data(const QModelIndex& index, int nRole) const;
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
};

class LSettingsModel :public QAbstractTableModel{
private:
	QString cat;
	QMap<QString, QJsonObject>* mp;
	QStringList ind;
public:
	LSettingsModel(QString c, QMap<QString, QJsonObject>* m , QObject *pobj = 0);

	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
};

class LListModel : public QAbstractListModel{
private:
	QJsonArray obj;
public:
	LListModel(const QJsonArray &o, QObject* pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	int rowCount(const QModelIndex& = QModelIndex()) const;
	QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void add(QString k);
	void del(QListView *i);
};

class LTableModel :public QAbstractTableModel{
private:
	QJsonObject& obj;
public:
	LTableModel(QJsonObject& o, QObject *pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
	void add(QString k, QString v);
	void del(QString k);
};

class LTextModWidgetModel : public QAbstractTableModel{
	LTextModWidgetEditor* wgt;
public:
	LTextModWidgetModel(LTextModWidgetEditor* e, QObject *pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	
	Qt::ItemFlags flags(const QModelIndex& index)const;
	void add();
	void del();
};

#endif //GLOBALQT_LWMODELS_H
