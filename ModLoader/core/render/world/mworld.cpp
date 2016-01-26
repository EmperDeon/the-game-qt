#include <ModLoader/core/render/world/mworld.h>

MWorldRender::MWorldRender(){
	this->manager = mVarG(ILevelManager*, "mLevel");

	this->listMutex = new QMutex;
	this->chunks = new QMap<IAChunkPos, int>;
	this->renderLists = new QList<int>;
}

void MWorldRender::init() {
	this->widget = mVarG(MGlWidget*, "mRender");
	renderDistance = 12;

	MLevelInfo* i= new MLevelInfo;
	i->setName("TestLevel1");

	this->manager->createLevel(i);
	this->level = manager->getCurrentLevel();
	MV_CORE_MODS->queue->waitForDone();

	qCritical() << QThread::currentThread();
}

void MWorldRender::render() {
//	drawAxis();
	checkPos();

	listMutex->lock();
	for ( int i : *renderLists) {
		glCallList(i);
	}
//		for(int i = 0; i < currentActive ; i++)
//		 glCallList(currentIndex + i);
	listMutex->unlock();

	selectBlock();
	// Box of Epileptic
//	this->drawRCube(IVec3(0, 0, 0), 0.15f);
//	this->drawRCube(IVec3(0, 0, 0), 1.0f);
}

void MWorldRender::selectBlock() {
	IVec3i c(en->pos()),t;
	float sc = 1.0f;
	float x = 0.0f;
	float pt=en->pitch(), yw=en->yaw();

	IVec3 i(
		c.x + c.x * cosf(pt) * cosf(yw),
		c.y + c.x * sinf(yw),
		c.z + c.x * sinf(pt) * cosf(yw)
	);

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 1.0f);

	while(x < 50.0f){
		x += sc;
		t.x = c.x - int(i.x * x);
		t.y = c.y - int(i.y * x);
		t.z = c.z - int(i.z * x);
		glVertex3f(t.x, t.y, t.z);
		if(c != t){
			c = t;
			if(level->isBlock(c)) break;
		}
	}
	glEnd();
	if(c != IVec3i(en->pos())) drawBorder(c);
}


void MWorldRender::drawAxis(){
	glLineWidth(3.0f);

	glBegin(GL_LINES);
	glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
	glVertex3f( 1.0f,  0.0f,  0.0f);
	glVertex3f(-1.0f,  0.0f,  0.0f);

	glColor4i(0, 128, 0, 255);
	glVertex3f( 0.0f,  1.0f,  0.0f);
	glVertex3f( 0.0f, -1.0f,  0.0f);

	glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
	glVertex3f( 0.0f,  0.0f,  1.0f);
	glVertex3f( 0.0f,  0.0f, -1.0f);
	glEnd();
}

void MWorldRender::close() {
	//this->level->save();
}

void MWorldRender::reAllocate(int i) {
	if(currentGened){
		glDeleteLists(currentIndex, currentGenCount);
	}
	this->currentIndex = glGenLists(i + 5);
	this->currentGenCount = i + 5;
	this->currentActive = 0;

	this->level->reAllocate(this);
}

GLuint MWorldRender::getFreeList() {
	if(currentActive >= currentGenCount){
		QMutexLocker l(this->listMutex);
		reAllocate(currentGenCount);
	}
	return currentIndex + currentActive++;
}

void MWorldRender::setChunks(QMap<IAChunkPos, IChunk *> *ch) {
	this->chunks->clear();
	for(IChunk* p : ch->values())
		this->chunks->insert(p->getId(), p->getGlList());
}



void MWorldRender::checkPos() {
	if (this->eCX != en->getCX() || this->eCZ != en->getCZ()) {
		this->eCX = en->getCX();
		this->eCZ = en->getCZ();

		qint32 tx, tz;
		renderLists->clear();
		for ( IAChunkPos p : chunks->keys()){
			tx = eCX - p.x();
			tz = eCZ - p.z();
			if (isInRange(tx, tz)){
				this->renderLists->append(chunks->value(p));
			}
		}
	}
}

