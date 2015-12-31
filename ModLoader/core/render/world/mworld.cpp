#include "ModLoader/core/render/world/mworld.h"

MWorldRender::MWorldRender(MCoreMods *m): loader(m) {

}

void MWorldRender::init() {
	getVertexArray();
	getColorArray();
	getIndexArray();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

void MWorldRender::render() {
	drawAxis();

//	glVertexPointer(3, GL_FLOAT, 0, VertexArray);
//	glColorPointer(3, GL_FLOAT, 0, ColorArray);
//
//	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, IndexArray);

	renderCube(0, 0, 0);

}

void MWorldRender::renderPolygon(float x1, float y1, float z1, float x2, float y2, float z3){

}

void MWorldRender::renderCube(float x, float y, float z){
	float r = 0.5f;
	glBegin(GL_QUADS);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(x +  r, y +  r, z -  r);
	glVertex3f(x -  r, y +  r, z -  r);
	glVertex3f(x -  r, y +  r, z +  r);
	glVertex3f(x +  r, y +  r, z +  r);
	glColor3f(1.0f,0.5f,0.0f);
	glVertex3f(x +  r, y -  r, z +  r);
	glVertex3f(x -  r, y -  r, z +  r);
	glVertex3f(x -  r, y -  r, z -  r);
	glVertex3f(x +  r, y -  r, z -  r);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(x +  r, y +  r, z +  r);
	glVertex3f(x -  r, y +  r, z +  r);
	glVertex3f(x -  r, y -  r, z +  r);
	glVertex3f(x +  r, y -  r, z +  r);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(x +  r, y -  r, z -  r);
	glVertex3f(x -  r, y -  r, z -  r);
	glVertex3f(x -  r, y +  r, z -  r);
	glVertex3f(x +  r, y +  r, z -  r);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(x -  r, y +  r, z +  r);
	glVertex3f(x -  r, y +  r, z -  r);
	glVertex3f(x -  r, y -  r, z -  r);
	glVertex3f(x -  r, y -  r, z +  r);
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(x +  r, y +  r, z -  r);
	glVertex3f(x +  r, y +  r, z +  r);
	glVertex3f(x +  r, y -  r, z +  r);
	glVertex3f(x +  r, y -  r, z -  r);
	glEnd(); // ��������� ��������
}

void MWorldRender::drawAxis(){
	glLineWidth(3.0f); // ������������ ������ ����� ���������� � ��������
	// �� ������ ������� ������ ����� 1 ������� �� ���������

	glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // ��������������� ���� ����������� ����������
	// ��� x �������� �����
	glBegin(GL_LINES); // ���������� �����
	glVertex3f( 1.0f,  0.0f,  0.0f); // ������ �����
	glVertex3f(-1.0f,  0.0f,  0.0f); // ������ �����
	glEnd();

	glColor4i(0, 128, 0, 255);
	glBegin(GL_LINES);
	// ��� y �������� �����
	glVertex3f( 0.0f,  1.0f,  0.0f);
	glVertex3f( 0.0f, -1.0f,  0.0f);

	glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
	// ��� z ������ �����
	glVertex3f( 0.0f,  0.0f,  1.0f);
	glVertex3f( 0.0f,  0.0f, -1.0f);
	glEnd();
}

void MWorldRender::getVertexArray(){
	GLfloat R=0.75; // ������ �����

	// ��������� �������� ��� ���������
	GLfloat a=4*R/sqrt(10+2*sqrt(5)); // ������� ���������
	GLfloat alpha=acos((1-a*a/2/R/R)); // ������ ���� �������� �� ���� // cos(alpha)=(1-a*a/2/R/R)

	// ��������� ����� ���������
	//0 �����
	VertexArray[0][0]=0;   // x
	VertexArray[0][1]=0;   // y
	VertexArray[0][2]=R;   // z

	//1 �����
	VertexArray[1][0]=R*sin(alpha)*sin(0);
	VertexArray[1][1]=R*sin(alpha)*cos(0);
	VertexArray[1][2]=R*cos(alpha);

	//2 �����
	VertexArray[2][0]=R*sin(alpha)*sin(72*k);
	VertexArray[2][1]=R*sin(alpha)*cos(72*k);
	VertexArray[2][2]=R*cos(alpha);

	//3 �����
	VertexArray[3][0]=R*sin(alpha)*sin(2*72*k);
	VertexArray[3][1]=R*sin(alpha)*cos(2*72*k);
	VertexArray[3][2]=R*cos(alpha);

	//4 �����
	VertexArray[4][0]=R*sin(alpha)*sin(3*72*k);
	VertexArray[4][1]=R*sin(alpha)*cos(3*72*k);
	VertexArray[4][2]=R*cos(alpha);

	//5 �����
	VertexArray[5][0]=R*sin(alpha)*sin(4*72*k);
	VertexArray[5][1]=R*sin(alpha)*cos(4*72*k);
	VertexArray[5][2]=R*cos(alpha);

	//6 �����
	VertexArray[6][0]=R*sin(pi-alpha)*sin(-36*k);
	VertexArray[6][1]=R*sin(pi-alpha)*cos(-36*k);
	VertexArray[6][2]=R*cos(pi-alpha);

	//7 �����
	VertexArray[7][0]=R*sin(pi-alpha)*sin(36*k);
	VertexArray[7][1]=R*sin(pi-alpha)*cos(36*k);
	VertexArray[7][2]=R*cos(pi-alpha);

	//8 �����
	VertexArray[8][0]=R*sin(pi-alpha)*sin((36+72)*k);
	VertexArray[8][1]=R*sin(pi-alpha)*cos((36+72)*k);
	VertexArray[8][2]=R*cos(pi-alpha);

	//9 �����
	VertexArray[9][0]=R*sin(pi-alpha)*sin((36+2*72)*k);
	VertexArray[9][1]=R*sin(pi-alpha)*cos((36+2*72)*k);
	VertexArray[9][2]=R*cos(pi-alpha);

	//10 �����
	VertexArray[10][0]=R*sin(pi-alpha)*sin((36+3*72)*k);
	VertexArray[10][1]=R*sin(pi-alpha)*cos((36+3*72)*k);
	VertexArray[10][2]=R*cos(pi-alpha);

	//11 �����
	VertexArray[11][0]=0;
	VertexArray[11][1]=0;
	VertexArray[11][2]=-R;
}

void MWorldRender::getColorArray(){
	for (int i=0; i<12; i++){
		ColorArray[i][0]=0.1f*(qrand()%11); // R - ������� ������������
		ColorArray[i][1]=0.1f*(qrand()%11); // G - ������ ������������
		ColorArray[i][2]=0.1f*(qrand()%11); // B - ����� ������������
		// qrand()%11 - ��������������� ����� �� 0 �� 10
	}
}

void MWorldRender::getIndexArray(){
	// 0 �����������
	IndexArray[0][0]=0; // ������ (�����) 1-�� �������
	IndexArray[0][1]=2; // ������ (�����) 2-�� �������
	IndexArray[0][2]=1; // ������ (�����) 3-�� �������

	// 1 �����������
	IndexArray[1][0]=0;
	IndexArray[1][1]=3;
	IndexArray[1][2]=2;

	// 2 �����������
	IndexArray[2][0]=0;
	IndexArray[2][1]=4;
	IndexArray[2][2]=3;

	// 3 �����������
	IndexArray[3][0]=0;
	IndexArray[3][1]=5;
	IndexArray[3][2]=4;

	// 4 �����������
	IndexArray[4][0]=0;
	IndexArray[4][1]=1;
	IndexArray[4][2]=5;

	// 5 �����������
	IndexArray[5][0]=6;
	IndexArray[5][1]=1;
	IndexArray[5][2]=7;

	// 6 �����������
	IndexArray[6][0]=7;
	IndexArray[6][1]=1;
	IndexArray[6][2]=2;

	// 7 �����������
	IndexArray[7][0]=7;
	IndexArray[7][1]=2;
	IndexArray[7][2]=8;

	// 8 �����������
	IndexArray[8][0]=8;
	IndexArray[8][1]=2;
	IndexArray[8][2]=3;

	// 9 �����������
	IndexArray[9][0]=8;
	IndexArray[9][1]=3;
	IndexArray[9][2]=9;

	// 10 �����������
	IndexArray[10][0]=9;
	IndexArray[10][1]=3;
	IndexArray[10][2]=4;

	// 11 �����������
	IndexArray[11][0]=9;
	IndexArray[11][1]=4;
	IndexArray[11][2]=10;

	// 12 �����������
	IndexArray[12][0]=10;
	IndexArray[12][1]=4;
	IndexArray[12][2]=5;

	// 13 �����������
	IndexArray[13][0]=10;
	IndexArray[13][1]=5;
	IndexArray[13][2]=6;

	// 14 �����������
	IndexArray[14][0]=6;
	IndexArray[14][1]=5;
	IndexArray[14][2]=1;

	// 15 �����������
	IndexArray[15][0]=7;
	IndexArray[15][1]=11;
	IndexArray[15][2]=6;

	// 16 �����������
	IndexArray[16][0]=8;
	IndexArray[16][1]=11;
	IndexArray[16][2]=7;

	// 17 �����������
	IndexArray[17][0]=9;
	IndexArray[17][1]=11;
	IndexArray[17][2]=8;

	// 18 �����������
	IndexArray[18][0]=10;
	IndexArray[18][1]=11;
	IndexArray[18][2]=9;

	// 19 �����������
	IndexArray[19][0]=6;
	IndexArray[19][1]=11;
	IndexArray[19][2]=10;
}
