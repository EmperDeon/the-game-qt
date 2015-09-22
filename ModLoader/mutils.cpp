#include "ModLoader/mutils.h"

void LLogWidget::addL(GLogLevel lv, QString cl, QString m){
	GLogE e = GLogE(lv, QDateTime::currentDateTime(), "BML-"+cl, m );
	if(lv <= curr){
		last += e.toString();
		w_edit->setHtml(last);
	}
	list->append(e);
	qDebug() << e.toString();
}
QString getLevelName(GLogLevel lv){
	switch(lv){
	case GLogLevel::ERR  : return "[E]";
	case GLogLevel::WARN : return "[W]";
	case GLogLevel::INFO : return "[I]";
	case GLogLevel::DEBUG: return "[D]";
	case GLogLevel::FINE : return "[F]";
	case GLogLevel::FFINE: return "[F]";
	case GLogLevel::ALL  : return "[A]";
		default:
			return "";
		//	case GLogLevel::ERR  : return "[ERROR]";
		//	case GLogLevel::WARN : return "[WARNING]";
		//	case GLogLevel::INFO : return "[INFO]";
		//	case GLogLevel::DEBUG: return "[DEBUG]";
		//	case GLogLevel::FINE : return "[FINE]";
	}
}
GLogE::GLogE(GLogLevel lvl,QDateTime dt, QString cls, QString mss):lv(lvl), d(dt), cl(cls), ms(mss){

}
QString GLogE::toString(){
	QString t = "<div ";

	switch(lv){
	case GLogLevel::ERR  : t += "style=\"color:red"; break;
	case GLogLevel::WARN : t += "style=\"color:#ff9c00"; break;
	case GLogLevel::INFO : t += "style=\"color:blue"; break;
	case GLogLevel::DEBUG: t += "style=\"color:black"; break;
	case GLogLevel::FINE : t += "style=\"color:gray"; break;
	case GLogLevel::FFINE: t += "style=\"color:gray"; break;
	case GLogLevel::ALL  : t += "style=\"color:gray"; break;
	}

	//t += "\">[" + d.toString("HH:mm:ss dd.MM.yyyy") + "]";
	t += "\">[" + d.toString("HH:mm:ss") + "]";
	t.append(getLevelName(lv));
	t.append("["+cl+"]");
	t.append(": "+ms);

	t.append("</div>");
	return t;
}
void GLogger:: log(GLogLevel lv, QString cl, QString ms){
	//QString s = QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy") + "^";
	QString s = QDateTime::currentDateTime().toString("HH:mm:ss") + "^";
	s += getLevelName(lv) + "^M-";
	s += cl + "^";
	s += ms;

	sendM(s);
}
void GLogger::sendM(QString s){
	if(!conn){
		socket->connectToServer("GameLogServer");
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_4);

	out << (quint16)0;
	out << s;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	socket->write(block);
	socket->flush();
}
QObject *GVars::get(QString name){
	return (*map)[name];
}
