#include <Launcher/lwmodels.h>

// LModModel
LModLoaderSelect::LModLoaderSelect(QMap<QString, QString> &m, QObject *pobj): QAbstractTableModel(pobj), mp(m){
	this->setHeaderData(0, Qt::Horizontal, "Name");
	this->setHeaderData(1, Qt::Horizontal, "File");
}

QVariant LModLoaderSelect::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant(); }
	QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
	       (index.column()==1 ?  mp[mp.keys()[index.row()]] : mp.keys()[index.row()] )
	                                                            : QVariant();
}

Qt::ItemFlags LModLoaderSelect::flags(const QModelIndex &index) const{
	return QAbstractTableModel::flags(index);
}

int LModLoaderSelect::rowCount(const QModelIndex&) const     {
	return mp.keys().size();
}

int LModLoaderSelect::columnCount(const QModelIndex&) const     {
	return 2;
}
// LModModel


// LSettingsModel
LSettingsModel::LSettingsModel(QString c, QMap<QString, QJsonObject> *m, QObject *pobj):QAbstractTableModel(pobj){
	this->cat = c;
	this->mp = m;

	for(QString s : mp->value(cat).keys()){if(s != "name") ind << s;}
	this->setHeaderData(0, Qt::Horizontal, "Key");
	this->setHeaderData(1, Qt::Horizontal, "Value");
}

QVariant LSettingsModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant(); }
	QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
	       (index.column()==1 ?  mp->value(cat) [ind[index.row()]].toString() : ind[index.row()] )
	                                                            : QVariant();
}

bool LSettingsModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		//	if(index.column() == 0){
		//	QString old = ind[index.row()];
		//	mp[cat][value.toString()] = mp[cat][old];
		//	mp[cat].remove(old);
		//}else{
		mp->value(cat)[ind[index.row()]] = value.toString();
		//}
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

Qt::ItemFlags LSettingsModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid() && index.column() == 1) ? (flags | Qt::ItemIsEditable) : flags;
}

int LSettingsModel::rowCount(const QModelIndex&) const     {
	return ind.size();
}

int LSettingsModel::columnCount(const QModelIndex&) const     {
	return 2;
}
// LSettingsModel


// LListModel
LListModel::LListModel(const QJsonArray &o, QObject *pobj):QAbstractListModel(pobj),obj(o){}

QVariant LListModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()){return QVariant();}
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
	       ? obj.at(index.row()).toString()
	       : QVariant();
}

bool LListModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		obj.replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

int LListModel::rowCount(const QModelIndex&) const{
	return obj.size();
}

QVariant LListModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const{
	if (nRole != Qt::DisplayRole) {return QVariant();}
	return (orientation == Qt::Horizontal) ? QString("Wrong_Model")
	                                       : QString::number(nSection);
}

Qt::ItemFlags LListModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractListModel::flags(index);
	return index.isValid() ? (flags | Qt::ItemIsEditable): flags;
}

void LListModel::add(QString k){
	obj << k;
}

void LListModel::del(QListView* i){
	QModelIndexList l = i->selectionModel()->selectedRows();

		foreach(const QModelIndex &index, l){
			QString s = index.data(Qt::DisplayRole ).toString();
			int j = 0;
				foreach(QJsonValue v, obj){
					if(s == v.toString()){
						obj.removeAt(j);
					}
					j++;
				}
		}
}
// LListModel


// LTableModel
LTableModel::LTableModel(QJsonObject& o, QObject *pobj):QAbstractTableModel(pobj), obj(o){
	this->setHeaderData(0, Qt::Horizontal, "Name");
	this->setHeaderData(1, Qt::Horizontal, "Path");
}

QVariant LTableModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {return QVariant(); }
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
	       (index.column()==1 ?  obj[obj.keys()[index.row()]].toString() : obj.keys()[index.row()] )
	                                                            : QVariant();
}

bool LTableModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		if(index.column() == 0){
			QString old = obj.keys()[index.row()];
			obj[value.toString()] = obj[old];
			obj.remove(old);
		}else{
			obj[obj.keys()[index.row()]] = value.toString();
		}
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

Qt::ItemFlags LTableModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid()) ? (flags | Qt::ItemIsEditable) : flags;
}

void LTableModel::add(QString k, QString v){
	obj[k] = v;
}

void LTableModel::del(QString k){
	obj.remove(k);
}

int LTableModel::rowCount(const QModelIndex&) const{
	return obj.size();
}

int LTableModel::columnCount(const QModelIndex&) const{
	return 2;
}
// LTableModel


// LModEditorModel
LTextModWidgetModel::LTextModWidgetModel(LTextModWidgetEditor* e, QObject *pobj):QAbstractTableModel(pobj),wgt(e){}

QVariant LTextModWidgetModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant();
	}else if (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
		return ((*wgt->ob)[index.row()].toObject())[wgt->nameVals.value(index.column())].toString();

	else return QVariant();
}

bool LTextModWidgetModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		QJsonObject o((*wgt->ob)[index.row()].toObject());
		o[wgt->nameVals.value(index.column())] = value.toString();
		wgt->ob->removeAt(index.row());
		wgt->ob->insert(index.row(), o);
		emit dataChanged(index, index);
	}
	return false;
}

Qt::ItemFlags LTextModWidgetModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid()) ? (flags | Qt::ItemIsEditable) : flags;
}

int LTextModWidgetModel::rowCount(const QModelIndex&) const{	return wgt->ob->size();}

int LTextModWidgetModel::columnCount(const QModelIndex&) const{	return 5;}

void LTextModWidgetModel::add(){
	QJsonObject o;
	for(int i = 0 ; i < wgt->list->size() ; i++)
		o.insert(wgt->nameVals.value(i), wgt->list->value(i)->text());
	(*wgt->ob) << o;
}

void LTextModWidgetModel::del(){
		for(QModelIndex i : wgt->table->selectionModel()->selectedIndexes()){
			lLogI("deleting " + QString::number(i.row()) + " " + QString::number(i.column()));
		}
}

QVariant LTextModWidgetModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(orientation == Qt::Horizontal && role == 0){
		return wgt->nameKeys.value(section);
	}else {
		return QAbstractTableModel::headerData(section, orientation, role);
	}
}
// LModEditorModel
