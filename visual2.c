/*C3-2*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "myShape.h"
#define KEY_ESC 27
double dist=-0.1;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0,dist,-20.0);

	glPushMatrix();/*���W�n�̕ۑ�*/	
	glTranslatef(0.0,1.0,0.0);
	myWireCylinder(1.0,2.0,12); /*2�i�ڂ̕`��*/
	glTranslatef(0.0,1.0,0.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	glutWireCone(1.0,2.0,12,3);/*3�i�ڂ̕`��*/
	glTranslatef(0.0,2.0,0.0);
	glPopMatrix();
	glTranslatef(0.0,-1.0,0.0);
	myWireCylinder(1.0,2.0,12);/*1�i�ڂ̕`��*/
	glTranslatef(1.5,-0.2,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.5,1.0,0.0);
		glVertex3f(-0.5,1.2,0.0);
		glVertex3f(-0.5,-0.8,0.0);
		glVertex3f(0.5,-1.0,0.0);
	glEnd();
	glTranslatef(-3.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.5,1.2,0.0);
		glVertex3f(-0.5,1.0,0.0);
		glVertex3f(-0.5,-1.0,0.0);
		glVertex3f(0.5,-0.8,0.0);
	glEnd();
	glTranslatef(1.5,0.6,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.5,1.2,0.0);
		glVertex3f(-0.5,1.0,0.0);
		glVertex3f(-0.5,-1.0,0.0);
		glVertex3f(0.5,-0.8,0.0);
	glEnd();
	glTranslatef(0.0,-dist-1.8,0.0);
	glScalef(0.9,0.6,0.4);
	glRotatef(-90.0,1.0,0.0,0.0);
	glutWireCone(1.0,2.0,9,3);
	glPopMatrix();/*���W�n�̕����@15�s�ɖ߂�*/
	glFlush();
}
void idle(void)
{
	dist=dist+0.0001;
	glutPostRedisplay();
}
void myKbd(unsigned char key, int x, int y)
{
	if(key==KEY_ESC) exit(0);
}
void myInit(char *progname)
{
	int width=500,height=500;
	float aspect=(float)width/(float)height;
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(progname);
	glClearColor(0.0,0.0,0.0,1.0);	
	glutKeyboardFunc(myKbd);
	
	glMatrixMode(GL_PROJECTION);
	/*���e�ϊ��s��X�^�b�N�𑀍�ΏۂƂ���*/
	glLoadIdentity();/*�s��X�^�b�N���N���A*/
	gluPerspective(30.0,aspect,1.0,50.0);
	glMatrixMode(GL_MODELVIEW);/*�􉽕ϊ��s��X�^�b�N�𑀍�Ώۂ���*/
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	myInit(argv[0]);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}