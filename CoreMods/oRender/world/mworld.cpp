#include <world/mworld.h>

MWorldRender::MWorldRender(){
	this->manager = varG(ILevelManager*, "mLevel");
 this->queue = varG(QThreadPool*, "eThreadQueue");
	this->listMutex = new QMutex;
	this->chunks = new QMap<IAChunkPos, GLuint>;
	this->renderLists = new QList<GLuint>;
	this->randomColors = new QList<IVec3>;
}

void MWorldRender::init() {
	this->widget = varG(MGlWidget*, "mRender");
	renderDistance = 6;

	for(int i=0;i<255;i++) randomColors->append(IVec3((qrand() % 31)*0.01f+0.7f,(qrand() % 31)*0.01f+0.7f,(qrand() % 31)*0.01f+0.7f));

	this->manager->loadLevel("TestLevel1");
	this->level = manager->getCurrentLevel();
	queue->waitForDone();
}

void MWorldRender::render() {
	drawAxis();
	checkPos();

	listMutex->lock();

	for ( GLuint i : *renderLists) {
		glCallList(i);
	}

//		for(int i = 0; i < currentActive ; i++)
//		 glCallList(currentIndex + i);
	listMutex->unlock();

	// Box of Epileptic
//	this->drawRCube(IVec3(0, 0, 0), 0.15f);
//	this->drawRCube(IVec3(0, 0, 0), 1.0f);
	selectBlock();
}

void MWorldRender::selectBlock() {
	IVec3i enPos, t1;
	IVec3 t;
	float pt, yw;

	if(lock){
		enPos = ep;
		yw = py;
		pt = pp;
	}else{
		enPos = en->pos();
		yw = en->yaw();
		pt = en->pitch();
	}

	//IVec3i c(10,5,11);
	float sc = 0.5f;
	float x = 0.0f;
 int ic = 0;
 //c.x += 1;
//	c.z += 1;

	IVec3 i(
		cosf(pt) * cosf(yw),
		sinf(yw),
		sinf(pt) * cosf(yw)
	);

	while(x < 20.0f){
		x += sc;
		t.x = enPos.x + i.x * x;
		t.y = enPos.y + i.y * x;
		t.z = enPos.z + i.z * x;

		if(t1 != IVec3i(t)){
			t1 = IVec3i(t);
			t = randomColors->value(ic++);
			glColor3f(t.x, t.y, t.z);
			drawBorder(t1);
			if(level->isBlock(t1)) break;
		}
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	if(t1 != IVec3i(en->pos())) drawBorder(t1);


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
//	if(currentGened){
//		glDeleteLists(currentIndex, currentGenCount);
//	}
//	this->currentIndex = glGenLists(i + 5);
//	this->currentGenCount = i + 5;
//	this->currentActive = 0;

	this->level->reAllocate(this);
}

GLuint MWorldRender::getFreeList() {
//	if(currentActive >= currentGenCount){
//		QMutexLocker l(this->listMutex);
//		reAllocate(currentGenCount);
//	}
	return glGenLists(1);
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

void MWorldRender::lockPos() {
	ep = en->pos();
	py = en->yaw();
	pp = en->pitch();
 lock = !lock;
}
