#include "ModLoader/mutils.h"

//QString getLevelName(GLogLevel lv){
//	switch(lv){
//	case GLogLevel::ERR  : return "[E]";
//	case GLogLevel::WARN : return "[W]";
//	case GLogLevel::INFO : return "[I]";
//	case GLogLevel::DEBUG: return "[D]";
//	case GLogLevel::FINE : return "[F]";
//	case GLogLevel::FFINE: return "[F]";
//	case GLogLevel::ALL  : return "[A]";
//	}
//}
//GLogE::GLogE(GLogLevel lvl,QDateTime dt, QString cls, QString mss):lv(lvl), d(dt), cl(cls), ms(mss){
//
//}
//QString GLogE::toString(){
//	QString t = "<div ";
//
//	switch(lv){
//	case GLogLevel::ERR  : t += "style=\"color:red"; break;
//	case GLogLevel::WARN : t += "style=\"color:#ff9c00"; break;
//	case GLogLevel::INFO : t += "style=\"color:blue"; break;
//	case GLogLevel::DEBUG: t += "style=\"color:black"; break;
//	case GLogLevel::FINE : t += "style=\"color:gray"; break;
//	case GLogLevel::FFINE: t += "style=\"color:gray"; break;
//	case GLogLevel::ALL  : t += "style=\"color:gray"; break;
//	}
//
//	//t += "\">[" + d.toString("HH:mm:ss dd.MM.yyyy") + "]";
//	t += "\">[" + d.toString("HH:mm:ss") + "]";
//	t.append(getLevelName(lv));
//	t.append("["+cl+"]");
//	t.append(": "+ms);
//
//	t.append("</div>");
//	return t;
//}
QJsonObject loadJson(QString file){
	QFile loadFile(file);
	qDebug() << "loading " << file;
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.object();
}