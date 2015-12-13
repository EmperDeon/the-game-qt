#include <ModLoader/core/render/mrender.h>

MGlWidget::MGlWidget(MCoreMods* m) : loader(m){
	cam = new MCamera(IBlockPos(0, 0, 0));
	world = new MWorldRender(m);
	gui = new MGuiRender(m);
}

void MGlWidget::initializeGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // цвет для очистки буфера изображения - здесь просто фон окна
	glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
	glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов
	glEnable(GL_CULL_FACE);   // устанавливается режим, когда строятся только внешние поверхности

	world->init();
//	gui->init();

}

void MGlWidget::resizeGL(int nWidth, int nHeight){
	glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
	glLoadIdentity();            // присваивает проекционной матрице единичную матрицу

	GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth; // отношение высоты окна виджета к его ширине

	// мировое окно
	if (nWidth>=nHeight)
		glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
	else
		glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

	// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

	glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MGlWidget::paintGL(){
	// glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

 cam->apply();
	world->render();
	//gui->render();
}

void MGlWidget::mousePressEvent(QMouseEvent* pe) { mPos = pe->pos();}
void MGlWidget::mouseReleaseEvent(QMouseEvent* pe){}
void MGlWidget::mouseMoveEvent(QMouseEvent* pe){
	Vector3 scl = cam->getScl();
 cam->rotate(
 	180/scl.x*(GLfloat)(pe->y() - mPos.y())/height(),
 	180/scl.z*(GLfloat)(pe->x() - mPos.x())/width()
	);
	mPos = pe->pos();

	updateGL();
}

void MGlWidget::wheelEvent(QWheelEvent* pe){
	if ((pe->delta())>0)
		cam->scale(0.1f, 0.1f, 0.1f);
	else if ((pe->delta())<0)
		cam->scale(-0.1f, -0.1f, -0.1f);

	updateGL(); // обновление изображения
}

void MGlWidget::keyPressEvent(QKeyEvent* pe) {
	switch (pe->key())	{
		case Qt::Key_Up:	   cam->rotate( 0.3f,  0.0f);	break;
		case Qt::Key_Down:	 cam->rotate(-0.3f,  0.0f);	break;
		case Qt::Key_Left:	 cam->rotate( 0.0f,  0.3f); break;
		case Qt::Key_Right: cam->rotate( 0.0f, -0.3f); break;

		case Qt::Key_W: cam->move( 0.5f,  0.0f,  0.0f); break;
		case Qt::Key_S: cam->move(-0.5f,  0.0f,  0.0f); break;

		case Qt::Key_A: cam->move( 0.0f,  0.5f,  0.0f); break;
		case Qt::Key_D: cam->move( 0.0f, -0.5f,  0.0f); break;

		case Qt::Key_Q: cam->move( 0.0f,  0.0f,  0.5f); break;
		case Qt::Key_E: cam->move( 0.0f,  0.0f, -0.5f); break;


		case Qt::Key_Escape:
			this->close();
			break;

		default:;
	}

	updateGL(); // обновление изображения
}

//QSize EMWidget::minimumSizeHint() const
//{
//				return QSize(50, 50);
//}

//QSize EMWidget::sizeHint() const
//{
//				return QSize(200, 200);
//}

//void EMWidget::rotateBy(int xAngle, int yAngle, int zAngle)
//{
//				xRot += xAngle;
//				yRot += yAngle;
//				zRot += zAngle;
//				update();
//}

//void EMWidget::setClearColor(const QColor &color)
//{
//				clearColor = color;
//				update();
//}

//void EMWidget::initializeGL()
//{
//				initializeOpenGLFunctions();

//				makeObject();

//				glEnable(GL_DEPTH_TEST);
//				glEnable(GL_CULL_FACE);

//#define PROGRAM_VERTEX_ATTRIBUTE 0
//#define PROGRAM_TEXCOORD_ATTRIBUTE 1

//				QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
//				const char *vsrc =
//								"attribute highp vec4 vertex;\n"
//								"attribute mediump vec4 texCoord;\n"
//								"varying mediump vec4 texc;\n"
//								"uniform mediump mat4 matrix;\n"
//								"void main(void)\n"
//								"{\n"
//								"    gl_Position = matrix * vertex;\n"
//								"    texc = texCoord;\n"
//								"}\n";
//				vshader->compileSourceCode(vsrc);

//				QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
//				const char *fsrc =
//								"uniform sampler2D texture;\n"
//								"varying mediump vec4 texc;\n"
//								"void main(void)\n"
//								"{\n"
//								"    gl_FragColor = texture2D(texture, texc.st);\n"
//								"}\n";
//				fshader->compileSourceCode(fsrc);

//				program = new QOpenGLShaderProgram;
//				program->addShader(vshader);
//				program->addShader(fshader);
//				program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
//				program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
//				program->link();

//				program->bind();
//				program->setUniformValue("texture", 0);
//}

//void EMWidget::paintGL()
//{
//				glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
//				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//				QMatrix4x4 m;
//				m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
//				m.translate(0.0f, 0.0f, -10.0f);
//				m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
//				m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
//				m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

//				program->setUniformValue("matrix", m);
//				program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
//				program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
//				program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
//				program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

//				for (int i = 0; i < 6; ++i) {
//								textures[i]->bind();
//								glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
//				}
//}
//void EMWidget::resizeGL(int width, int height)
//{
//				int side = qMin(width, height);
//				glViewport((width - side) / 2, (height - side) / 2, side, side);
//}

//void EMWidget::mousePressEvent(QMouseEvent *event)
//{
//				lastPos = event->pos();
//}

//void EMWidget::mouseMoveEvent(QMouseEvent *event)
//{
//				int dx = event->x() - lastPos.x();
//				int dy = event->y() - lastPos.y();

//				if (event->buttons() & Qt::LeftButton) {
//								rotateBy(8 * dy, 8 * dx, 0);
//				} else if (event->buttons() & Qt::RightButton) {
//								rotateBy(8 * dy, 0, 8 * dx);
//				}
//				lastPos = event->pos();
//}

//void EMWidget::mouseReleaseEvent(QMouseEvent * /* event */)
//{
//				emit clicked();
//}

//void EMWidget::makeObject()
//{
//				static const int coords[6][4][3] = {
//								{ { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
//								{ { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
//								{ { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
//								{ { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
//								{ { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
//								{ { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
//				};

//				for (int j = 0; j < 6; ++j)
//								textures[j] = new QOpenGLTexture(QImage(QString(":/images/side%1.png").arg(j + 1)).mirrored());

//				QVector<GLfloat> vertData;
//				for (int i = 0; i < 6; ++i) {
//								for (int j = 0; j < 4; ++j) {
//												// vertex position
//												vertData.append(0.2 * coords[i][j][0]);
//												vertData.append(0.2 * coords[i][j][1]);
//												vertData.append(0.2 * coords[i][j][2]);
//												// texture coordinate
//												vertData.append(j == 0 || j == 3);
//												vertData.append(j == 0 || j == 1);
//								}
//				}

//				vbo.create();
//				vbo.bind();
//				vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
//}

