#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>
#include <gl/glut.h>
#include <gl/glext.h>
#include <gl/glm.h>
#include <mmsystem.h>
#include <ctime> 
using namespace std;

void grab();

PFNGLMULTITEXCOORD1FARBPROC        glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC        glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC        glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC    glClientActiveTextureARB = NULL;

float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f
float fRotate1 = 0.0f;
float zhuanx = 0.0, zhuanz = 0.0, ztx = 0.0f, zty = 0.0f, ztz = 0.0f, tpx = 0.0f, tpz = 0.0f, sa = 0.0, sx = 0.0, sz = 0.0;
float lx = 100.0, ly = 100.0, lz = 100.0;
int i, i1, i2, j, k, time1, timebase[] = { 0, 0, 0, 0, 0, 0, 0 }, score = 0, level = 1, killnum = 0, max = 0, stay[10];
GLuint texture[20], list_id, list_id2;
bool bco[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false };

float spe1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float spe0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float amb0[] = { 0.2f, 0.2f, 0.2f, 1.0f }, flyhead[] = { 0, 0, 0, 0, 0, 0, 0 };
float mat_diffuse00[] = { 0.8f, 0.8f, 0.8f, 1.0f }, t[] = { 0, -12, 12, -12, 12, -12, 12 }, tk = 0.1, tlast = 3600;
float be[] = { 0, -12, 12, -12, 12, -12, 12 }, en[] = { 0, -6.5, 5.0, -2.5, 6.5, -5.0, 2.5 };  //各个物体的起始和终点位置
GLUnurbsObj *theNurb1;
GLUnurbsObj *theNurb2;
GLfloat ctrlpoints[5][5][3] =
{
	{ { -3, 0.5, 0 }, { -1, 1.5, 0 }, { -2, 2, 0 }, { 1, -1, 0 }, { -5, 0, 0 } },
	{ { -3, 0.5, -1 }, { -1, 1.5, -1 }, { -2, 2, -1 }, { 1, -1, -1 }, { -5, 0, -1 } },
	{ { -3, 0.5, -2 }, { -1, 1.5, -2 }, { -2, 2, -2 }, { 1, -1, -2 }, { -5, 0, -2 } },
	{ { -3, 0.5, -3 }, { -1, 1.5, -3 }, { -2, 2, -3 }, { 1, -1, -3 }, { -5, 0, -3 } },
	{ { -3, 0.5, -4 }, { -1, 1.5, -4 }, { -2, 2, -4 }, { 1, -1, -4 }, { -5, 0, -4 } }
};

bool bPersp = true;
bool bAnim = false, dt = false;
bool bWire = false, start = false, capture = false, kaishi[] = { false, false, false, false, false, false, false };
bool rotea = false, changelight = false, tospot = false, changetex = true, kita[] = { false, false, false, false, false, false, false };
bool fcc[] = { true, true, true, true, true, true, true }, home[] = { true, true, true, true, true, true, true }, tf[] = { true, true, true, true, true, true, true };

int wHeight = 0;
int wWidth = 0;

#define BITMAP_ID 0x4D42
#define TEXW 128
#define TEXH 128
#define BMP_Header_Length 54
#define WINDOWWIDTH 720
#define WINDOWHEIGHT 720
GLubyte tex[TEXW][TEXH][3];

const GLfloat pi = 3.14;

/// record the state of mouse
GLboolean mouserdown = GL_FALSE;
GLboolean mouseldown = GL_FALSE;
GLboolean mousemdown = GL_FALSE;

/// when a mouse-key is pressed, record current mouse position 
static GLint mousex = 0, mousey = 0;
static GLfloat yrotate = pi/2.3; /// angle between y-axis and look direction
static GLfloat xrotate = pi/2; /// angle between x-axis and look direction
static GLfloat celength = 60;/// lenght between center and eye

//手动读obj文件，放弃此方法
//class obj3dmodel
//{
//public:
//	struct vertex{
//		double x;
//		double y;
//		double z;
//	};
//	struct face{
//		unsigned int v1, v2, v3;
//	};
//	vector<vertex> vetexes;
//	vector<face> faces;
//
//	void parse(const char* filename);
//	void draw();
//};
//
//void obj3dmodel::parse(const char *filename)
//{
//	string s;
//	ifstream fin(filename);
//	if (!fin)
//		return;
//	while (fin >> s)
//	{
//		cout << s << endl;
//		if (!strcmp(s.c_str(), "v"))
//		{
//			vertex v;
//			fin >> v.x >> v.y >> v.z;
//			cout << v.x << v.y << v.z << endl;
//			vetexes.push_back(v);
//		}
//		else if (!strcmp(s.c_str(), "f"))
//		{
//			face f;
//			fin >> s;
//			f.v1= *s.c_str()-'0';
//			fin >> s;
//			f.v2 = *s.c_str() - '0';
//			fin >> s;
//			f.v3 = *s.c_str() - '0';
//			faces.push_back(f);
//		}
//	}
//}
//
//void obj3dmodel::draw()
//{
//	glBegin(GL_TRIANGLES);
//	for (int i = 0; i<faces.size(); i++)
//	{
//		//索引要减去1
//		vertex v1 = vetexes[faces[i].v1 - 1];
//		vertex v2 = vetexes[faces[i].v2 - 1];
//		vertex v3 = vetexes[faces[i].v3 - 1];
//		glVertex3f(v1.x, v1.y, v1.z);
//		glVertex3f(v2.x, v2.y, v2.z);
//		glVertex3f(v3.x, v3.y, v3.z);
//	}
//	glEnd();
//}
//
//obj3dmodel orz;
//orz.parse("dounazi.obj");
//orz.draw();

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char	*bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量

	// 以“二进制+读”模式打开文件filename 
	fopen_s(&filePtr,filename, "rb");
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0;imageIdx<(bitmapInfoHeader->biSizeImage); imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}

//加载纹理的函数：
void texload(int i, char *filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
	unsigned char*   bitmapData;                                       // 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 	    //mipmap层次(通常为，表示最上层) 
		GL_RGB,	//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,	//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的f类型
		bitmapData);	//bitmap数据指针  
}

//定制自定义纹理
void makeTexture(void)
{
	int i2, j2, i, j;
	for (i = 0; i<TEXW; i += 2)
	{
		for (j = 0; j<TEXH; j += 2)
		{/*
		 r = (i*j) % 255;
		 g = (4 * i) % 255;
		 b = (4 * j) % 255;*/
			if ((i + j) % 4 == 0)
			for (i2 = i; i2 < i + 2; i2++)
			for (j2 = j; j2 < j + 2; j2++)
			{
				tex[i2][j2][0] = (GLubyte)0;
				tex[i2][j2][1] = (GLubyte)125;
				tex[i2][j2][2] = (GLubyte)255;
			}
			else
			for (i2 = i; i2 < i + 2; i2++)
			for (j2 = j; j2 < j + 2; j2++)
			{
				tex[i2][j2][0] = (GLubyte)255;
				tex[i2][j2][1] = (GLubyte)255;
				tex[i2][j2][2] = (GLubyte)255;
			}
		}
	}
}

//定义纹理的函数：
void init()
{
	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");

	//下面生成自定义纹理
	makeTexture(); //参考opengl red book，理解后请解释函数的步骤。
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXW, TEXH, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

//绘制桌腿
void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

//用glm库读取obj
void readobj()
{
	glPushMatrix();
	GLMmodel *glm_model;
	glm_model = glmReadOBJ("body.obj");

	glmUnitize(glm_model);
	glmScale(glm_model, 4.0);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);
	list_id = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
	glmDelete(glm_model);

	GLMmodel *glm_model2;
	glm_model2 = glmReadOBJ("head.obj");

	glmUnitize(glm_model2);
	glmScale(glm_model2, 8.0);
	glmFacetNormals(glm_model2);
	glmVertexNormals(glm_model2, 90);
	list_id2 = glmList(glm_model2, GLM_MATERIAL | GLM_SMOOTH);
	glmDelete(glm_model2);

	glPopMatrix();
}

//各个显示列表
void lists()
{
	GLint lid = glGenLists(10);

	glNewList(7, GL_COMPILE);  //茶壶
	glutSolidTeapot(1);
	glEndList();

	glNewList(3, GL_COMPILE);  //桌子
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);
	////多重纹理
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_BLEND);

	//glActiveTextureARB(GL_TEXTURE1_ARB);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_BLEND);

	//glRotatef(-90, 1, 0, 0);
	//glBegin(GL_QUADS);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
	//glVertex3f(-2.51, 2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
	//glVertex3f(-2.51, -2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
	//glVertex3f(2.51, -2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
	//glVertex3f(2.51, 2.01, 4.001);
	//glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glDisable(GL_TEXTURE_2D);

	glPushMatrix();  //桌面
	float mat_diffuse1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();  //桌腿
	float mat_diffuse2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	float mat_diffuse3[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	float mat_diffuse4[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();  //桌腿
	float mat_diffuse5[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	glEndList();

	glNewList(4, GL_COMPILE);    //六面墙壁
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  //地板
	float amb1[] = { 0.8, 0.8, 0.8 ,1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb1);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 0.0, -150.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 0.0, -150.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  //天花板
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	float mat_diffuse11[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse11);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 0);   glVertex3f(-100.0, 35.0, -150.0);
	glTexCoord2f(0, 0);   glVertex3f(100.0, 35.0, -150.0);
	glTexCoord2f(0, 1);   glVertex3f(100.0, 35.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);  //前方墙壁
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, -150.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, -150.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, -150.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, -150.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //左方墙壁
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(-100.0, 35.0, -150.0);
	glTexCoord2f(1, 0);   glVertex3f(-100.0, 0.0, -150.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //右方墙壁
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, -150.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, -150.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //后方墙壁
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, 100.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(5, GL_COMPILE);  //两排物体
	GLUquadricObj *objCylinder = gluNewQuadric();
	gluQuadricNormals(objCylinder, GL_SMOOTH);
	gluQuadricTexture(objCylinder, TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	//float mat_diffuse21[] = { 0.5f, 0.3f, 0.6f, 1.0f };  //圆锥
	float mat_diffuse21[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆台
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //球体
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //另一排球体
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //另一排球体
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //立方体
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-88.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();


	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //长方体
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();


	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-11.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-12.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);
	
	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(11.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(12.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -95.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //圆柱
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -115.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(6, GL_COMPILE);    
	//Nurbs曲面
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	theNurb1 = gluNewNurbsRenderer();//创建NURBS对象theNurb1
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_FILL);

	GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(30.0, 4.0, -155.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0, 4.0, -155.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -60.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -40.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -20.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 0.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 20.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 40.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glEndList();
}

//绘制各个物体，设置游戏逻辑
void Draw_Scene()
{
	//int id = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);
	init();
	glEnable(GL_TEXTURE_2D);
	if (!changetex) glBindTexture(GL_TEXTURE_2D, texture[3]); else  glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glPushMatrix();
	glTranslatef(tpx, 5.0f, tpz + 30);
	glRotatef(fRotate1, 0, 1, 0);
	if (rotea) fRotate1 += 2.0f;
	if (dt) glCallList(7);  //茶壶
	glPopMatrix();
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0.0, 0.0f, 30.0);
	glRotatef(-90, 1, 0, 0);
	if (dt) glCallList(3);  //桌子
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);

	//float mat_diffuse11[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse11);
	//glBegin(GL_QUADS);
	////glColor3f(0.0, 1.0, 0.0);
	//glVertex3f(100.0, 0.0, 100.0);
	//glVertex3f(-100.0, 0.0, 100.0);
	//glVertex3f(-100.0, 0.0, -100.0);
	//glVertex3f(100.0, 0.0, -100.0);
	//glEnd();

	glCallList(4);  //四面墙壁

	glMaterialfv(GL_FRONT, GL_AMBIENT, amb0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe0);

	glCallList(5);  //两排物体
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe0);
	srand((int)time(0));
	for (i = 1; i <= 6; i++)
	if (home[i]&&start)  //每次从原点出现的时间不同，用随机数生成，这样出现的先后有层次感
	{
		time1 = glutGet(GLUT_ELAPSED_TIME);
		if (tf[i]) {
			stay[i] = rand() % 3 + 1;
			stay[i] *= 1000;
			timebase[i] = time1;
			tf[i] = false;
		}
		if (time1 - timebase[i] > stay[i])
		{
			home[i] = false;
			tf[i] = true;
		}
	}
	else
	{
		glLoadName(2*i-1);  //六个靶子移动
		float mat_diffuse32[] = { 1.0, 0.0, 0.0, 1.0 }, mat_diffuse31[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		if (!start) glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse31);
		else if (!bco[2 * i - 1] && !bco[2 * i]) glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse31); else
		{
			if (fcc[i]) { timebase[i] = glutGet(GLUT_ELAPSED_TIME); fcc[i] = false; kita[i] = true; }
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse32);
		}
		glPushMatrix();
		if (!start)
		{
			t[i] = en[i];
			score = 0;
			level = 1;
			if (!kaishi[i]) kaishi[i] = !kaishi[i];
		}
		else if (kaishi[i])
		{
			t[i] = be[i];
			kaishi[i] = !kaishi[i];
		}
		if ((t[i] < en[i]) && (en[i]<0)) t[i] += tk;
		else if ((t[i]> en[i]) && (en[i]>0)) t[i] -= tk;
		else
		if (start)
		{
			time1 = glutGet(GLUT_ELAPSED_TIME);
			if (!kita[i]) {
				timebase[i] = time1;
				kita[i] = true;
			}
			if (bco[2 * i - 1] || bco[2 * i])
			{
				if (time1 - timebase[i] > 500)
				{
					kita[i] = false;
					home[i] = true;
					t[i] = be[i];
					bco[2*i-1] = false;
					bco[2 * i] = false;
					fcc[i] = true;
					flyhead[i] = 0.0;
				}
				if (bco[2 * i]) flyhead[i] += 3.0;
			}
			else if (time1 - timebase[i] > tlast) 
			{
				kita[i] = false;
				home[i] = true;
				bco[2 * i] = false;
				bco[2 * i-1] = false;
				fcc[i] = true;
				flyhead[i] = 0.0;
				t[i] = be[i];
				killnum = 0;
				PlaySound("Knifekill_GR.wav", NULL, SND_ASYNC | SND_FILENAME);
				score -= 200;
				if (score / 1000 < (level - 1))
				{
					if (tk > 0.1) tk -= 0.05;
					if (tlast < 3600) tlast += 400;
					//if (tlast <= 1000 && tlast>500) tlast += 200;
					if (level>1) level -= 1;
				}
			}
		}
		if (i > 3) j = i - 3; else j = i;
		glTranslatef(t[i], 3.0, 38.0 - j * 20);
		glCallList(1);
		glLoadName(2 * i);
		glTranslatef(0, 5.0+flyhead[i],0.0 );  //爆头效果，头部向上飞去
		glCallList(2);
		glPopMatrix();
	
	}

	glLoadName(13);
	//glPopName();
	float mat_diffuse41[] = { 1.0, 0.0, 0.0, 1.0 }, mat_diffuse42[] = { 0.3, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse41);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse42);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, spe1);
	glCallList(6);  //Nurbs曲面
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);

	glPushMatrix();
	glTranslatef(0.0,0.0,20.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse41);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse42);
	//glCallList(6);
	glTranslatef(0.0, 0.0, 20.0);
	//glCallList(6);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);
	glPopMatrix();
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		gluPerspective(45.0, 1.0, 1.0, 1000.0);
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 0 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	//case 'e': {zhuanx += 5.0f; break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }
	case 'r':{changetex = !changetex; break; }
	case 'x':{start = !start; break; }
	case 'e': {dt = !dt; break; }

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
				  ztx -= 1.5*sin(xrotate);
				  ztz -= - 1.5*cos(xrotate);
				  break;
	}
	case 'd': {//todo
				  ztx += 1.5*sin(xrotate);
				  ztz += - 1.5*cos(xrotate);
				  break;
	}
	case 'w': {//todo
				  ztx -= 1.5*cos(xrotate);
				  ztz -= 1.5*sin(xrotate);
				  break;
	}
	case 's': {//todo
				  ztx += 1.5*cos(xrotate);
				  ztz += 1.5*sin(xrotate);
				  break;
	}
	case 'z': {//todo
				  if (zty >= -1000) zty -= 1.0f;
				  break;
	}
	case 'c': {//todo
				  if (zty <= 1000) zty += 1.0f;
				  break;
	}

	case 'y': {//todo
				  changelight = !changelight;
				  break;
	}

		// the position of light source
	case 't': {//todo
				  if (ly <= 100.0) ly += 1.0f;
				  break;
	}
	case 'g': {//todo
				  if (ly >= -100.0) ly -= 1.0f;
				  break;
	}
	case 'f': {//todo
				  if (lx >= -100.0) lx -= 1.0f;
				  break;
	}
	case 'h': {//todo
				  if (lx <= 100.0) lx += 1.0f;
				  break;
	}
	case 'n': {//todo
				  if (lz <= 80.0) lz += 1.0f;
				  break;
	}
	case 'v': {//todo
				  if (lz >= -80.0) lz -= 1.0f;
				  break;
	}
	case 'm': {//todo
				  tospot = !tospot;
				  break;
	}
		//the spotlight
	case '[': {//todo
				  if (sa>-40) sa -= 0.2;
				  break;
	}
	case ']': {//todo
				  sa += 0.2;
				  break;
	}
	case ';': {//todo
				  sz -= 0.1;
				  break;
	}
	case '.': {//todo
				  sz += 0.1;
				  break;
	}
	case ',': {//todo
				  sx -= 0.1;
				  break;
	}
	case '/': {//todo
				  sx += 0.1;
				  break;
	}

	case 'l': {//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
				  if (tpx <= 2.0) tpx += 0.1f;
				  break;
	}
	case 'j': {//todo
				  if (tpx >= -2.0) tpx -= 0.1f;
				  break;
	}
	case 'i': {//todo
				  if (tpz >= -1.5) tpz -= 0.1f;
				  break;
	}
	case 'k': {//todo
				  if (tpz <= 1.5) tpz += 0.1f;
				  break;
	}
	case '3': {//todo
				  rotea = !rotea;
				  break;
	}
	case '0': {//todo
				  capture = !capture;
				  break;
	}
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256], buffertitle[256];

	char mode[64];
	//if (bDrawList)
	//	strcpy(mode, "display list");
	//else
	//	strcpy(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		if (start)
		{
			sprintf_s(buffertitle, "  Game Mode   max:%d  score:%d  level:%d  combo:%d  FPS:%4.2f", max, score, level, killnum, frame*1000.0 / (time - timebase));
			sprintf_s(buffer, "Game Mode    max:%d  score:%d  level:%d  combo:%d   FPS:%4.2f", max, score, level, killnum, frame*1000.0 / (time - timebase));
		}
		else
		{
			sprintf_s(buffertitle, "  Free Mode   max:%d  score:%d  level:%d  combo:%d  FPS:%4.2f", max, score, level, killnum, frame*1000.0 / (time - timebase));
			sprintf_s(buffer, "Press X start game    max:%d  score:%d  level:%d  combo:%d   FPS:%4.2f", max, score, level, killnum, frame*1000.0 / (time - timebase));
		}
		timebase = time;
		frame = 0;
	}

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  
	glPushMatrix();               
	glLoadIdentity();         
	glOrtho(0, 480, 0, 480, -1, 1); 
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix();       
	glLoadIdentity();     
	glRasterPos2f(10, 10);

	char *c;
	glLineWidth(2.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		//glutStrokeCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	}

	glMatrixMode(GL_PROJECTION); 
	glPopMatrix();           
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix();      
	glEnable(GL_DEPTH_TEST);

	glutSetWindowTitle(buffertitle);
}

//场景绘制函数，漫游实现
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();		// Reset The Current Modelview Matrix
	
	if (bAnim)
	{
		xrotate += 0.01;
	}
	if (start)
	{
		ztx = 0;
		zty = 5;
		ztz = 0;
		yrotate = pi / 2;
		xrotate = pi / 2;
		celength = 60;
	}
	center[0] = ztx;
	center[1] = zty;
	center[2] = ztz;

	//center[0] = ztx;
	//center[1] = zty;
	//center[2] = ztz;

	eye[0] = center[0] + celength * sin(yrotate) * cos(xrotate);
	eye[1] = center[1] + celength * cos(yrotate);
	eye[2] = center[2] + celength * sin(yrotate) * sin(xrotate);

	gluLookAt(eye[0], eye[1] , eye[2] ,
		center[0], center[1] , center[2],
		0, 1, 0);		

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	if (changelight) {
		white[0] = 1.0;
		white[1] = 0.0;
		white[2] = 0.0;
	}

	if (capture){
		grab();
		capture = !capture;
	}

	GLfloat light_pos[] = { lx, ly, lz, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	GLfloat spotcolor[] = { 1.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotcolor);  
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotcolor); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotcolor);  
	GLfloat position[] = { 0, 6, 0, 1 }, spotangle = 5.0 + sa, lightDir[] = { 0.0 + sx, -5.0, 0.0 + sz };
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotangle); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0); 
	if (tospot)
		glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);

	//if (ztz > -20) ztz -= 0.5;
	//else if (zhuanx < 90) zhuanx += 1;
	//else if (ztx>-20) ztx -= 0.5;

	//if (ztz > -4) ztz -= 0.1;
	//else if (zhuanx < 90) zhuanx += 1;
	//else if (ztz>-10) ztz -= 0.1;
	//glRotatef(fRotate + zhuanx, 0, 1.0f, 0);
	//glTranslatef(-ztx, -zty, -ztz);
	//glRotatef(-90, 1, 0, 0);
	Draw_Scene();// Draw Scene

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	getFPS();
	glutSwapBuffers();
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr, minZ, *ptrNames, numberOfNames;
	//printf("zmin = %d\n", buffer[3]);
	//printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	ptrNames = ptr+3;
	//minZ = 0;
	minZ = 0xffffffff;
	for (i = 0; i < hits; i++) {
		names = *ptr;
		ptr++;
		if (*ptr<minZ) {
			//printf("haha\n");
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr + 2;
		}
		printf("The names are %d,distance:%d\n", *(ptr + 2), *ptr);
		//bco[*(ptr + 2)] = !bco[*(ptr + 2)];
		ptr += (names + 2);
	}
	printf("The closest hit names are %d\n\n", *ptrNames);
	if (!bco[*ptrNames])
	{
		killnum++;
		score += 100;
		if (*ptrNames % 2 == 0){ bco[*ptrNames - 1] = !bco[*ptrNames - 1]; score += 100; PlaySound("Headshot_BL.wav", NULL, SND_ASYNC | SND_FILENAME); }
		else
		{
			//bco[*ptrNames + 1] = !bco[*ptrNames + 1];
			switch (killnum)
			{
			case 1:PlaySound("Grenadekill_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 2:PlaySound("MultiKill_2_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 3:PlaySound("MultiKill_3_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 4:PlaySound("MultiKill_4_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 5:PlaySound("MultiKill_5_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 6:PlaySound("MultiKill_7_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			case 7:PlaySound("MultiKill_8_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			default:PlaySound("MultiKill_6_BL.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP); break;
			}
		}
		if (score > max) max = score;
		if (score > 0 && (score / 1000 >= level))
		{
			if (tk < 1.0) tk += 0.05;
			if (tlast > 400) tlast -= 400;
			//if (tlast <= 1000&&tlast>500) tlast -= 200;
			level += 1;
		}
		bco[*ptrNames] = !bco[*ptrNames];
	}
}

//鼠标操作1，识别左右键单击
#define SIZE 500
#define N 50
void mouse1(int button, int state, int x, int y)
{
	GLuint selectBuffer[SIZE];//存放物体名称的栈
	GLint hits;//存放被选中对象个数
	GLint viewport[4];//存放可视区参数
	/*mousex1 = x, mousey1 = y;*/
	//if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		//if ((x == mousex1) && (y == mousey1))
		glGetIntegerv(GL_VIEWPORT, viewport);//获取当前视口坐标参数
		glSelectBuffer(SIZE, selectBuffer);//选择名称栈存放被选中的名称
		glRenderMode(GL_SELECT);//设置当前为 选择模式

		glInitNames();
		glPushName(0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(x, viewport[3] - y, 1, 1, viewport);//创建用于选择的投影矩阵栈
		gluPerspective(45.0, 1.0, 1.0, 1000.0);
		//glTranslatef(0.0f, 0.0f, -500.0f);
		//glOrtho(-10, 10, -10, 10, -100, 100);
		glRotatef(fRotate + zhuanx, 0, 1.0f, 0);
		Draw_Scene();
		//glRotatef(fRotate, 0, 1.0f, 0);
		//glRotatef(-90, 1, 0, 0);
		//glScalef(0.2, 0.2, 0.2);
		//Draw_Triangle();
		//glFrustum(-3, 3, -3, 3, 3, 100);
		//draw(GL_SELECT);//绘制场景
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glFlush();

		hits = glRenderMode(GL_RENDER);
		printf("outhit=%d X:%d Y:%d\n", hits, x, y);
		if (hits > 1 && start)
		{
			processHits(hits, selectBuffer);
		}
		glutPostRedisplay();
	}
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_TRUE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_TRUE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_TRUE;
	}
	else
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_FALSE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_FALSE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_FALSE;
	}
	mousex = x, mousey = y;
}

//鼠标操作2，识别鼠标按下后拖动
void mouse2(int x, int y)
{
	if (mouseldown == GL_TRUE)
	{
		float aa = yrotate - (y - mousey) / 120.0f;
		xrotate += (x - mousex) / 80.0f;
		//yrotate -= (y - mousey) / 120.0f;
		if (aa<1.56 && aa>1.05) yrotate -= (y - mousey) / 120.0f;  //设置视角上下角的限度
		//cout << yrotate<<endl;
	}

	if (mouserdown == GL_TRUE)
	{
		celength += (y - mousey) / 25.0f;
	}
	mousex = x, mousey = y;
	glutPostRedisplay();
}

//截图功能
void grab()   //函数grab抓取窗口中的像素
{
	//交换缓冲区以便像素读取
	glutSwapBuffers();
	FILE* pReadFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	// 计算像素数据的实际长度
	i = WINDOWWIDTH * 3; // 得到每一行的像素数据长度
	while (i % 4 != 0) // 补充数据，直到i是的倍数
		++i; // 本来还有更快的算法，
	// 但这里仅追求直观，对速度没有太高要求
	PixelDataLength = i * WINDOWHEIGHT;

	// 分配内存和打开文件
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);

	fopen_s(&pReadFile, "Monet.bmp", "rb");
	if (pReadFile == 0)
		exit(0);

	fopen_s(&pWritingFile, "grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	// 读取像素
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WINDOWWIDTH, WINDOWHEIGHT,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把spot.bmp的文件头复制为新文件的文件头
	fread(BMP_Header, sizeof(BMP_Header), 1, pReadFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WINDOWWIDTH;
	j = WINDOWHEIGHT;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件
	fclose(pReadFile);
	fclose(pWritingFile);
	free(pPixelData);

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOWWIDTH,WINDOWHEIGHT);
	int windowHandle = glutCreateWindow("The Final");

	glGenTextures(19, texture);
	texload(1, "tree1.bmp");
	texload(2, "Monet.bmp");
	texload(4, "qiang1.bmp");
	texload(5, "sora1.bmp");
	texload(6,"diban.bmp");
	texload(7, "qiang2.bmp");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(mouse1);
	glutMotionFunc(mouse2);
	readobj();
	lists();

	glutMainLoop();
	return 0;
}

