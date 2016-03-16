#include <widgets/lmods.h>

LModsWidget::LModsWidget(LMainWindow *l){
	loader = l;

	QVBoxLayout* layout = new QVBoxLayout;
	QHBoxLayout* l_model = new QHBoxLayout;
	QHBoxLayout* l_wgt = new QHBoxLayout;

	QPushButton* b_rl = new QPushButton(tr("Reload mods list"));
	QPushButton* b_add = new QPushButton(tr("Add .zip"));
	QPushButton* b_del = new QPushButton(tr("Disable mod"));

	list = new QListView;

	connect(b_rl, SIGNAL(clicked()), this, SLOT(reload()));
	connect(b_add, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked(bool)), this, SLOT(del()));

	l_model->addWidget(b_add);
	l_model->addWidget(b_del);
	l_wgt->addWidget(b_rl);
	layout->addLayout(l_model);
	layout->addWidget(list);
	layout->addLayout(l_wgt);

	loader->modsMap->load();
	model = new LListModel(loader->modsMap->lst);
	list->setModel(model);
	this->setLayout(layout);
	lLogD("Constructed");
}

void LModsWidget::reload(){	loader->modsMap->reload();	}

void LModsWidget::add(){	loader->modsMap->addNew();	}

void LModsWidget::del(){	model->del(list);	}

void LModsWidget::closeEvent(QCloseEvent *event){
	loader->modsMap->save();
	event->accept();
}
