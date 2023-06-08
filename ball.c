/*  c6-3.c   Copyright (c) 2003 by T. HAYASHI and K. KATO  */
/*                                    All rights reserved  */
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "myShape.h"
#define KEY_ESC 27

void polarview( void );
float distance=7.0, twist=0.0, elevation=-45.0, azimuth=30.0;

float diffuse[] = { 0.7, 0.6, 0.2, 1.0 };
float specular[] = { 0.8, 0.8, 0.8, 1.0 };
float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
float shininess = 128.0;
float ball[60][3][3];//ボール
float x_basket=0.0;
float x_cood=0.0;
float y_basket=0.0;
int i;
int k;
int j=0;
float ballX;
float ballTX;
int time_limit=60;
int score=0;
float speball[2][2];
void limit(int value)
{
	
	time_limit-=1;//このように1sごとにlimit()を呼び出し、time_limitを一つずつ減らすことで、タイマーの役割を果たしています。
	glutTimerFunc(1000,limit,0);//1000ms(1s)ごとに呼び出します。
	if(time_limit<0)
	{
		printf("あなたは%d点ゲットできました。",score);
		exit(0);
	}
}

void ball_judge()
{
	//printf("ball_judge check");
	for(i=0;i<j;i++)
	{
		for(k=0;k<3;k++)
		{
			//ここで当たり判定を行っています。
			if((ball[i][k][0]+0.2>x_basket)&&
				(ball[i][k][0]-0.2<x_basket+0.4)&&
				(ball[i][k][1]<y_basket+0.5)&&
				(ball[i][k][1]>y_basket-0.5)&&
				(ball[i][k][2]==1)
				)
				{
					printf("10点ゲット\n");
					score+=10;
					ball[i][k][2]=0;

				}	
		}
	}
	
}
void update(int value)
{
	srand((unsigned)time(NULL));
	for(i=0;i<j;i++)
	{
		for(k=0;k<3;k++)
		{
			ballTX=((rand()%5)-2)/10;
			ball[i][k][0]+=ballTX;
			ball[i][k][1]-=0.1;//ここでボールの座標を更新しています。
			//printf("%f",ball[i][k][1]);
		}
	}
	
	glutPostRedisplay();
	ball_judge();//ボールの座標を更新した後でボールが籠に当たった場合に得点が入るように当たり判定を行っています。
	glutTimerFunc(100,update,0);//100秒ごとにupdate()文を呼び出します。
	
}
DrawString(char *str,float x0,float y0,double w,double h)
{
	int i,len;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.,w,0.,h);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		glRasterPos2f(x0+2*i,y0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*str);
		str++;
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}
void ball_g(int value)
{
	srand((unsigned)time(NULL));
	//このfor文でボールを生成しています。
	for(k=0;k<3;k++)
	{
		ballX=((double)((rand()%41)-20/10));
		ball[j][k][0]=ballX;
		ball[j][k][1]=5.0;
		ball[j][k][2]=1;//ボールの当たり判定
	}
	j++;
	glutTimerFunc(1000,ball_g,0);//1000ms(1s)ごとにball_g()を呼び出します。
}
void display(void)
{
	char mojit[20];
	char mojis[20];
	int m,n;

	
	sprintf_s(mojit,20,"%d",time_limit);
	sprintf_s(mojis,20,"%d",score);
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DrawString("time",42,95,100,100);
	DrawString("score",52,95,100,100);
	if(time_limit<=20)
	{
		glColor3f(1.0,0.0,0.0);
	}
	DrawString(mojit,44,92,100,100);
	if(score>50)
	{
		glColor3f(1.,1.,1.);
	}
	DrawString(mojis,54,92,100,100);
	glLoadIdentity();
	glPushMatrix();
	//polarview();
		glTranslatef(0.0,0.0,-distance);
		glPushMatrix();
			
		glPopMatrix();
    	glEnable( GL_DEPTH_TEST );
		
		glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse);
		
		glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
		glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
		glMaterialf( GL_FRONT, GL_SHININESS, shininess );
		glShadeModel(GL_FLAT);
		glTranslatef(0.0,-2.5,0.0);
	glPushMatrix();
	glTranslatef(x_basket,y_basket,0);
	x_cood+=x_basket;
	glColor3f(1.,1.,1.);
	myWireCylinder(0.4,1.0,24);
	glPopMatrix();
	glEnable( GL_LIGHTING );
	for(i=0;i<j;i++)
	{
		for(k=0;k<3;k++)
		{
			glPushMatrix();
			glTranslatef(ball[i][k][0],ball[i][k][1],0.0);
			glutSolidSphere( 0.2, 100, 100 );
			glPopMatrix();
		}
	}
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glPopMatrix();
	glFlush();
}


void myKbd(unsigned char key, int x, int y)
{
	switch( key ) {
		case KEY_ESC:
        exit( 0 );
	}
}
void basket_trans(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			x_basket-=0.2;//←を押したときに籠が左に動きます。
			break;
		case GLUT_KEY_RIGHT:
			x_basket+=0.2;//→を押したときに籠が右に動きます。
			break;

	}
}

void myInit (char *progname)
{
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( 800, 800);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
	glutSpecialFunc(basket_trans);
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, aspect, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	int start;
	srand((unsigned)time(NULL));

	printf("ピンボールランナーへようこそ\n");
	printf("ボールが落ちてくるので、制限時間内にかごを操作してください\n");
	printf("ボールが入ると、得点が入ります。\n");
	printf("矢印キー(←、→)を押すことで籠を操作することができます。\n");
	printf("開始（1~9）");
	scanf("%d",&start);
	if((start>=0)&&(start<=9))
	{
		glutInit(&argc, argv);
		myInit(argv[0]);
		ball_g(0);
		glutReshapeFunc (myReshape);
		glutDisplayFunc(display);
		glutTimerFunc(100,update,0);
		glutTimerFunc(1000,limit,0);
		glutMainLoop();
	}
	 
	
	return(0);
}