#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;
struct ball
{
	float ballx,bally,ballwh,velx,vely;
	float red;
	float green;
	float blue;
	bool left,right,up,down;
} ball;

struct block
{
	float myx;
	float myy;
	float width;
	float height;
	bool lft;
	bool rgt;
	float red;
	float green;
	float blue;
}block,block1;

float red=0.0;
float green=0.0;
float blue=0.0;

int player1=0, player2=0;
int size1=0,size2=0;

void specialUp(int,int,int);	//To check for key press
void specialDown(int,int,int);  //To check for key release
void reshape(void);		//To Modify the co-ordinates of the game objects according to the events
void draw(void);		//To Render the Game objects on the screen
void revert(void);

void initialize()	//To set the initial co-ordinates of the objects on the screen
{
	
	block.myx=300;
	block.myy=0;
	block.width=150-15*size1;
	block.height=20;
	block.lft=false;
	block.rgt=false;
	
	block1.myx=300;
	block1.myy=380;
	block1.width=150-15*size2;
	block1.height=20;
	block1.lft=false;
	block1.rgt=false;

	ball.ballx=300;
	ball.bally=200;
	ball.ballwh=30;
	ball.velx=1.1;
	ball.vely=1.1;
	
	
	ball.red=0.65;
	ball.green=0.49;
	ball.blue=0.24;
	if(player1==0 && player2==0) {
	block.red=1;
	block.green=1;
	block.blue=1; 

	block1.red=0;
	block1.green=0;
	block1.blue=0;
	}
	else {
	block.red=rand()%2;
	block.green=rand()%2;
	block.blue=rand()%2; 

	block1.red=rand()%2;
	block1.green=rand()%2;
	block1.blue=rand()%2;
	}

}

bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{
  if ( Ay+Ah < By ) return false; //if A is more to the lft than B
  else if ( Ay > By+Bh ) return false; //if A is more to rgt than B
  else if ( Ax+Aw < Bx ) return false; //if A is higher than B
  else if ( Ax > Bx+Bw ) return false; //if A is lower than B

  return true; //There is a collision because none of above returned false
}

void reshape()		//Modify the co-ordinates according to the key-presses and collisions etc...
{
	if(block.myx<0)
	  block.myx=0;
	if(block.myx+block.width>600)
	  block.myx=block.myx-(block.myx+block.width-600);
	if(block.lft==true)
	  block.myx=block.myx-0.05;
	if(block.rgt==true)
	  block.myx=block.myx+0.05;


	if(block1.myx<0)
	  block1.myx=0;
	if(block1.myx+block1.width>600)
	  block1.myx=block1.myx-(block1.myx+block1.width-600);
	if(block1.lft==true)
	  block1.myx=block1.myx-0.05;
	if(block1.rgt==true)
	  block1.myx=block1.myx+0.05;
	  
	
	  
	ball.ballx+=0.04*ball.velx;
	ball.bally+=0.04*ball.vely;

	if(ball.ballx<0)
	{
		ball.velx=-ball.velx;
		ball.right=true;
		ball.left=false;
	}
	if(ball.ballx+ball.ballwh>600)
	{
		ball.right=false;
		ball.left=true;
		ball.velx=-ball.velx;
	}
	//if(ball.bally+ball.ballwh>400)
		//ball.vely=-ball.vely;
	if(ball.bally>400)
		{
			player1++;
			size1++;
			if(player1>=5)
			{
				cout<<"Finally Player 1 wins"<<endl;
				_sleep(5000);
				exit(0);
			}
			initialize();
			cout<<"Player 1 wins\nScore="<<player1<<":"<<player2<<endl;
			
		}
	else if(ball.bally<0)
		{
			player2++;
			size2++;
			if(player2>=5)
			{
				cout<<"Finally Player 2 wins"<<endl;
				_sleep(5000);
				exit(0);
			}
			initialize();
			cout<<"Finally Player 2 wins\nScore="<<player1<<":"<<player2<<endl;
			//_sleep(5000);
			//exit(0);
		}
	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,block.myx,block.myy,block.width,block.height)==true)
	{
			ball.vely=-ball.vely;
			ball.up=true;
			ball.down=false;
	}
	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,block1.myx,block1.myy,block1.width,block1.height)==true)
	{
			ball.vely=-ball.vely;
			ball.up=false;
			ball.down=true;
	}

	draw();
}
void specialUp(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=false;break;
		case (GLUT_KEY_RIGHT): block.rgt=false;break;
		case (GLUT_KEY_UP): block1.lft=false;break;
		case (GLUT_KEY_DOWN): block1.rgt=false;break;
		//case 65: block1.lft=false;break;
		//case 68: block1.rgt=false;break;
	}
}
void specialDown(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=true;break;
		case (GLUT_KEY_RIGHT): block.rgt=true;break;
		case (GLUT_KEY_UP): block1.lft=true;break;
		case (GLUT_KEY_DOWN): block1.rgt=true;break;
		
			//case 65: block1.lft=true;break;
		//case 68: block1.rgt=true;break;	
	}
}


void keyboard(unsigned char key,int x,int y)
{
	if(key==27) exit(0);
	if(key=='a'){specialUp(1,0,0);specialDown(1,0,0);}

	if(key=='d'){specialUp(2,0,0);specialDown(2,0,0);}
}
void myinit()
{
	glViewport(0,0,600,400);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,600,0,400);
}
void draw()		//Render the objects on the screen using the latest updated co-ordinates 
{
	glColor3f(block.red,block.green,block.blue);
	glBegin(GL_POLYGON);
		glVertex2f(block.myx,block.myy);
		glVertex2f(block.myx+block.width,block.myy);
		glVertex2f(block.myx+block.width,block.myy+block.height);
		glVertex2f(block.myx,block.myy+block.height);
	glEnd();
	

	glColor3f(block1.red,block1.green,block1.blue);
	glBegin(GL_POLYGON);
		glVertex2f(block1.myx,block1.myy);
		glVertex2f(block1.myx+block1.width,block1.myy);
		glVertex2f(block1.myx+block1.width,block1.myy+block1.height);
		glVertex2f(block1.myx,block1.myy+block1.height);
	glEnd();
	

	glColor3f(ball.red,ball.green,ball.blue);
	glBegin(GL_POLYGON);
		glVertex2f(ball.ballx,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally+ball.ballwh);
		glVertex2f(ball.ballx,ball.bally+ball.ballwh);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
	
}
void revert()
{
	ball.velx=0.0;
	ball.vely=0.0;
	if(ball.up==true)
	{
		if(ball.right==true)
		{
			ball.velx=ball.velx;
			ball.vely=ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=ball.vely;
		}
	}
	else if(ball.down=true)
	{
		if(ball.right=true)
		{
			ball.velx=ball.velx;
			ball.vely=-ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=-ball.vely;
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(red,green,blue,1);
	glClearColor(0.7,1,0.8,1);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	reshape();
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("2D AIR HOCKEY");
	initialize();
	myinit();
	draw();
	glutDisplayFunc(display);
        glutSpecialFunc(specialDown);
    	glutSpecialUpFunc(specialUp);
    	glutKeyboardFunc(keyboard);
	glutIdleFunc(reshape);
	glutMainLoop();
	return 0;
}
