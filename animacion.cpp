	/*
	Ahuir Domínguez,Victor
	Soriano Pérez,Carles Salvador
	IGU: 3o Facultad de Informática Trabajo Voluntario 1: Animación alámbrica*/
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <windows.h> 

//********************************************************************
/* Global intern variables (better not to touch them) */
int updateTime;				// Animation support
int initTime;				// FPS support calculation
unsigned int nFrames=0;		// Visualized frames counter.
float fps=60;				// Current visualization speed (FPS)


const unsigned int winX = 1440;
const unsigned int winY = 850;


float zoomX=0, zoomY=0, zoomZ=0;

//Takes Variables
int cityTake = 0, roomTake = 1, consoleTake = 2, chipTake = 3;
int phaseNumber=2; //Starting Phase

//City variables
float cloud1_speed=100, cloud1_altitude=50, cloud2_speed=100, cloud2_altitude=30, cloud3_speed=100, cloud3_altitude=10, cloud4_speed=100, cloud4_altitude=50;
float x1=0.98,x2=0.83,x3=0.27,x4=0.08,x5=0.54,x6=1;
float windowHouse=1;
float cloud1=0.6;
float cloud2=0.72;
float cloud3=0.72;
bool windowIsWhite=false;
//Chip variables
int lightPosition=5; //si falla el pos. de la luz poner posluz=5 en el display de consola
int rot_chip, chip_rotado=0;
int el_an1; 
float upX,upY=1.0,upZ;
float eyeX=100,eyeY=-30,eyeZ=0;
float centerX=0,centerY=0,centerZ=0;
//haces de luz
float posBall1Y=50,posBall1Z=22;
float posBall2Y=50,posBall2Z=12;
float posBall3Y=-10,posBall3Z=50;
float posBall4Y=-10,posBall4Z=50;
float pos_elx=0,pos_ely=0,pos_elz=0.0;

//Variables para la consola
int parte_consola = 0;
int iSeg1, iSeg2;
int cSeg1, cSeg2, cSeg3, cSeg4;
int RED, GREEN;
int chat=0,letras=1;

//*****************************************************************************************************

int forceWait(){
     int t;
     t=(int)clock()/CLOCKS_PER_SEC;
	 return t;
}
void drawText(unsigned int x, unsigned int y, char *text, int color, void *font = GLUT_BITMAP_HELVETICA_18) {
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winX, 0, winY);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	if (color==1) {
		GLfloat red[3]={1.0f, 0.0f, 0.0f};
		glColor3fv(red);
	}
	if (color==2) {
		GLfloat green[3]={0.0f, 0.6f, 0.0f};
		glColor3fv(green);
	}
	if (color==3) {
		GLfloat blue[3]={0.0f, 0.0f, 1.0f};
		glColor3fv(blue);
	}
	glRasterPos2f(x, winY-y);
	while (*text) 
	{
		glutBitmapCharacter(font, *text++);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void calculateFps(void)
{
	static char msg[20];

	nFrames++;
	if (nFrames==60) {
		int taux=glutGet(GLUT_ELAPSED_TIME);
		if (taux==initTime) return;
		fps=(float)(nFrames*1000)/(taux-initTime);
		initTime=taux;
		sprintf_s(msg, sizeof(msg), "FPS: %.2f",fps); 
		nFrames=0;
	}
	drawText(50, 50, msg, 3);
}

void forceRestart(void){
		glMatrixMode (GL_MODELVIEW) ;
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear (GL_COLOR_BUFFER_BIT);
}

void screenChats(void){
	//Part 1
	if(chat == 0) drawText(600,300,">> Hello, visitor",2);
	if(chat == 1) drawText(600,300,"- What?, Where am I?",1);
	if(chat == 2) { //U
		drawText(600,300,"- What?, Where am I?",1);
		drawText(600,320,"last thing I remembered I was....",1);
	}
	if(chat == 3) drawText(600,300,">> Don't worry, you're safe now",2);
	if(chat == 4) { //M
		drawText(600,300,">> Don't worry, you're safe now",2);
		drawText(600,320,">> Look...",2);
	}

	//Part 2
	if(chat == 5) { //U
		drawText(600,300,"- Hey wait, you didn't say me",2);
		drawText(600,320,"who you are yet...",2);
	}
	if(chat == 6) drawText(600,300,">> I'm VC2012",1);
	if(chat == 7) drawText(600,300,"- What are you?",2);
	if(chat == 8) drawText(600,300,">> Look",1);
	
	//Part 3
	if(chat == 9) 	drawText(600,300,"- So you are a machine",2);
	if(chat == 10) {
		drawText(600,300,">> Yes, as you last saw, we are",1);
		drawText(600,320,"based in electrical impulses.",1);
	}
	if(chat == 11)	drawText(600,300,"- We are? You know I'm a human.",2);
	if(chat == 12)	drawText(600,300,"- Do you? I can't be a machine.",2);
	if(chat == 13){
		drawText(600,300,"- I don't like this anymore.",2);
		drawText(600,320,"- Let me out.",2);
	}
	if(chat == 14) drawText(600,300,">> Sure",1);
	if(chat == 15) {
		drawText(600,300,">> Subject BD350XY -> Terminate",1);
		drawText(600,320,"> Reason:",1);
	}
	if(chat == 16) {
		drawText(600,300,">> Subject BD350XY -> Terminate",1);
		drawText(600,320,"> Reason: Reasoning.",1);
		  
	}
	//Credits
	if(chat == 17) drawText(600,280,"IGU 2012 - Proyecto 1 (Alambrico)",3);
	if(chat == 18){
		drawText(600,280,"IGU 2012 - Proyecto 1 (Alambrico)",3);
		drawText(600,300,"Victor Ahuir Dominguez", 1);
		drawText(600,320,"Carles S. Soriano Perez", 2);
	}

	cSeg2 = forceWait();
}
void display(void)
{	 
	if(phaseNumber == consoleTake){
		forceRestart();
		screenChats();
	}
	if(phaseNumber == chipTake){
		forceRestart();
		glLoadIdentity();
		gluLookAt (eyeX, eyeY,eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
		glTranslatef(zoomX,zoomY,zoomZ);

		//BASE
		// Chip
		glPushMatrix();
			glRotatef(-(GLfloat)rot_chip,1,0,0);
			glBegin(GL_QUADS);
				glColor3f (0,0.5,0);
				glVertex3f (0,-15,30); glVertex3f (0,-15,-25);
				glVertex3f (0,15,-25); glVertex3f (0,15,30);
			glEnd();
			// Chipe borders
			glBegin(GL_LINE_LOOP);
				glColor3f (0,1,0);
				glVertex3f (0,-15,30); glVertex3f (0,-15,-25); 
				glVertex3f (0,15,-25); glVertex3f (0,15,30);
			glEnd();
			// Processor
			glBegin(GL_QUADS);
				glColor3f (0.2,0.2,0.2);
				glVertex3f (0,8,15); glVertex3f (0,8,-5); 
				glVertex3f (0,-5,-5); glVertex3f (0,-5,15);
			glEnd();
			// Processor border
			glBegin(GL_LINE_LOOP);
				glColor3f (0,0,0);
				glVertex3f (0,8,15); glVertex3f (0,8,-5); 
				glVertex3f (0,-5,-5); glVertex3f (0,-5,15);
			glEnd();
			// Memory
			glBegin(GL_QUADS);
				glColor3f (0.2,0.2,0.2);
				glVertex3f (0,5,-20); glVertex3f (0,5,-12); 
				glVertex3f (0,-5,-12); glVertex3f (0,-5,-20);
			glEnd();
			// Memory border
			glBegin(GL_LINE_LOOP);
				glColor3f (0,0,0);
				glVertex3f (0,5,-20); glVertex3f (0,5,-12); 
				glVertex3f (0,-5,-12); glVertex3f (0,-5,-20);
			glEnd();
			// Wires
			glBegin(GL_LINES);
				glColor3f (1,1,0);
				glVertex3f (1,0,12); glVertex3f (1,50,12);//1
				glVertex3f (1,12,0); glVertex3f (1,12,-50);
				glVertex3f (1,-10,-50); glVertex3f (1,-10,50);//3
				glVertex3f (1,3,0);	glVertex3f (1,12,0);
				glVertex3f (1,50,22); glVertex3f (1,5,22);//5
				glVertex3f (1,5,22); glVertex3f (1,5,12);//6
				glVertex3f (1,0,10); glVertex3f (1,-10,10);
				glVertex3f (1,0,12); glVertex3f (1,0,-15);//8
				glVertex3f (1,3,-15); glVertex3f (1,-10,-15);
				glVertex3f (1,3,-15); glVertex3f (1,3,0); //10
			glEnd();	
			//Electric impuse (ball)
			glPushMatrix(); //Leading / main ball
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, posBall1Y, posBall1Z);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			//Rest of E.I.
			glPushMatrix(); //Ball 2
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, posBall2Y, posBall2Z);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix(); //Ball 3
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, posBall3Y, posBall3Z);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix(); //Ball 4
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, posBall4Y, posBall4Z);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix();
				//Atom core
				glColor3f (0, 0,0.75);
				glTranslatef (1, posBall1Y, posBall1Z);
				glutWireSphere(0.075, 10, 8);
				//Electrons (Regarding Atom core position)
				glPushMatrix();
					glColor3f (0.75, 0,0);
					glRotatef((GLfloat)el_an1,0,1,0);
					glTranslatef (0.15,0,0);
					glutWireSphere(0.015, 10, 8);
				glPopMatrix();
				glPushMatrix();
					glColor3f (0.75, 0,0);
					glRotatef(-(GLfloat)el_an1,0,1,1);
					glTranslatef (0.2,0,0);
					glutWireSphere(0.015, 10, 8);
				glPopMatrix();
				glPushMatrix();
					glColor3f (0.75, 0,0);
					glRotatef((GLfloat)el_an1,0,-1,1);
					glTranslatef (0.3,0,0);
					glutWireSphere(0.015, 10, 8);
				glPopMatrix();
			glPopMatrix();
			//Above
				// Processor Top
				//glTranslatef(zoomx,zoomy,zoomz); Not needed
				glBegin(GL_LINES);
					glColor3f (0,0,0);
					glVertex3f (0,8,15); glVertex3f (2,8,15); 
					glVertex3f (0,8,-5); glVertex3f (2,8,-5);
					glVertex3f (0,-5,-5); glVertex3f (2,-5,-5); 
					glVertex3f (0,-5,15); glVertex3f (2,-5,15);
				glEnd();
				//Top
				glBegin(GL_QUADS);
					glColor3f (0.2,0.2,0.2);
					glVertex3f (2,8,15); glVertex3f (2,8,-5); 
					glVertex3f (2,-5,-5); glVertex3f (2,-5,15);
				glEnd();
				// PROC Top (Border)
				glBegin(GL_LINE_LOOP);
					glColor3f (0,0,0);
					glVertex3f (2,8,15); glVertex3f (2,8,-5); 
					glVertex3f (2,-5,-5); glVertex3f (2,-5,15);
				glEnd();
				// MEM Top
				glBegin(GL_LINES);
					glColor3f (0,0,0);
					glVertex3f (2,5,-20); glVertex3f (0,5,-20); 
					glVertex3f (2,5,-12); glVertex3f (0,5,-12);
					glVertex3f (2,-5,-12); glVertex3f (0,-5,-12); 
					glVertex3f (2,-5,-20); glVertex3f (0,-5,-20);
				glEnd();
				//Top
				glBegin(GL_QUADS);
					glColor3f (0.2,0.2,0.2);
					glVertex3f (2,5,-20); glVertex3f (2,5,-12); 
					glVertex3f (2,-5,-12); glVertex3f (2,-5,-20);
				glEnd();
				// MEM Top (Border)
				glBegin(GL_LINE_LOOP);
					glColor3f (0,0,0);
					glVertex3f (2,5,-20); glVertex3f (2,5,-12); 
					glVertex3f (2,-5,-12); glVertex3f (2,-5,-20);
				glEnd();
		glPopMatrix();
		//cSeg4=forceWait();
	}
	if(phaseNumber == roomTake){
		forceRestart();
		zoomZ=0; zoomY=0;
		glLoadIdentity();
		gluLookAt (100, 30,0, 0, 0, 0, 0.0, 1.0, 0.0);
		glTranslatef(zoomX,zoomY,zoomZ);
		 
		//////////ground////////////
		glBegin(GL_QUADS);
			glColor3f (0.75, 0.75, 0.75);//white
			glVertex3f (-60, 0, -60.0);
			glColor3f (1, 1, 1);//white
			glVertex3f (-60,0, 60.0);
			glColor3f (1, 1, 1);//white
			glVertex3f (60,0,60.0);
			glColor3f (1, 1, 1);//white
			glVertex3f (60, 0,-60.0);
		glEnd();
		//Left wall
		glBegin(GL_QUADS);
			glColor3f (1, 1, 1);//white
			glVertex3f (60, 0,60);
			glColor3f (1, 1, 1);//white
			glVertex3f (-60,0,60 );
			glColor3f (1, 1, 1);//white
			glVertex3f (-60,60,60);
			glColor3f (1, 1, 1);
			glVertex3f (60,60,60);
		glEnd();
		//Right wall
		glBegin(GL_QUADS);
			glColor3f (1, 1, 1);//white
			glVertex3f (-60, 0,-60);//red
			glColor3f (1, 1, 1);//white
			glVertex3f (60,0,-60 );//green
			glColor3f (1, 1, 1);//white
			glVertex3f (60,60,-60);
			glColor3f (1, 1, 1);//white
			glVertex3f (-60,60,-60);
		glEnd();
		//Background wall
		glBegin(GL_QUADS);
			glColor3f (0.85, 0.85,0.85);//white
			glVertex3f (-60, 0,60);//red
			glColor3f (0.85, 0.85, 0.85);//white
			glVertex3f (-60,0,-60 );//green
			glColor3f (1, 1, 1);//whtie
			glVertex3f (-60,60,-60);
			glColor3f (1, 1, 1);
			glVertex3f (-60,60,60);
		glEnd();

		//Screen
		glBegin(GL_QUADS);
			glColor3f (0,0, 0);
			glVertex3f (-45,15 ,15);
			glColor3f (0, 0, 0);
			glVertex3f (-45,15,-15 );
			glColor3f (0, 0, 0);
			glVertex3f (-45,30,-15);
			glColor3f (0, 0, 0);
			glVertex3f (-45,30,15);
		glEnd();
		//Table board
		glBegin(GL_QUADS);
			glColor3f(0.5,0.25, 0);
			glVertex3f (-60, 10, -30.0);
			glColor3f (0.5,0.25, 0);
			glVertex3f (-60,10, 30);
			glColor3f (0.5,0.25, 0);
			glVertex3f (-30,10,30);
			glColor3f (0.5,0.25, 0);
			glVertex3f (-30, 10,-30);
		glEnd();
		
		//keyboard
		glBegin(GL_QUADS);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-40, 12, -11.0);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-40,12, 11);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-30,12,11);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-30, 12,-11);
		glEnd();
		//mouse
		glBegin(GL_QUADS);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-40, 12, -17.0);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-40,12, -14);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-30,12,-14);
			glColor3f(0.75,0.75,0.75);
			glVertex3f (-30, 12,-17);
		glEnd();
	}
	if(phaseNumber== cityTake){
		forceRestart();
		glLoadIdentity();
		gluLookAt (100, 0,0, 0, 0, 0, 0.0, 1.0, 0.0);
		glTranslatef(zoomX,zoomY,zoomZ);
		//Background
		glBegin(GL_QUADS);
		glColor3f (x4,x5, x6);
		glVertex3f (0, -90,110);
		glColor3f (0, 0.54,0.64 );
		glVertex3f (0,-90,-110 );
		glColor3f (x1, x2, x3);
		glVertex3f (0,90,-110);
		glColor3f (x4, x5, x6);
		glVertex3f (0,90,110);
		glEnd();
		//cloud 0
	glPushMatrix();
		glColor3f (cloud1 ,cloud2, cloud2);
		glTranslatef(-50,cloud2_altitude,cloud4_speed);
		glScalef (0.5,1,10);
		glutWireSphere(10, 100, 10);   
	glPopMatrix();

		//cloud 1
	glPushMatrix();
		glColor3f (cloud1 ,cloud2, cloud3);
		glTranslatef(-50,cloud1_altitude,cloud1_speed);
		glScalef (0.5,0.1,2);
		glutWireSphere(10, 100, 10);   
	glPopMatrix();

	//cloud 2
	glPushMatrix();
		glColor3f (0.58 ,0.73, 0.78);
		glTranslatef(-50,cloud2_altitude,cloud2_speed);
		glScalef (0.5,0.05,2);			
		glutWireSphere(10, 100, 10);   
	glPopMatrix();
	
	//cloud 3
		glPushMatrix();
			glColor3f (0.58 ,0.73, 0.78);
			glTranslatef(-10,cloud3_altitude,cloud3_speed);
			glScalef (0.5,0.25,3);
			glutWireSphere(10, 100, 10);   
		glPopMatrix();
	//Cloud 4
		glPushMatrix();
			glColor3f (0.58 ,0.73, 0.78);
			glTranslatef(-9,cloud4_altitude,cloud4_speed);
			glScalef (0.5,0.25,3);
			glutWireSphere(10, 100, 50);   
		glPopMatrix();

	
		//Building 1

		glBegin(GL_QUADS);
			glColor3f (0.65,0.65, 0.65);
			glVertex3f (5, -90,70);
			glColor3f (0.65, 0.65,0.65 );
			glVertex3f (5,-90,30 );
			glColor3f (0.65, 0.65, 0.65);
			glVertex3f (5,0,30);
			glColor3f (0.65, 0.65, 0.65);
			glVertex3f (5,0,70);
		glEnd();

			//Building 2

		glBegin(GL_QUADS);
			glColor3f (0.40,0.40, 0.40);
			glVertex3f (10, 0,50);
			glColor3f (0.40, 0.40,0.40 );
			glVertex3f (10,0,30 );
			glColor3f (0.40, 0.40, 0.40);
			glVertex3f (10,40,30);
			glColor3f (0.40, 0.40, 0.40);
			glVertex3f (10,30,50);
		glEnd();

				//Building 3

		glBegin(GL_QUADS);
			glColor3f (0.55,0.55, 0.55);
			glVertex3f (2, -90,30);
			glColor3f (0.55, 0.55,0.55 );
			glVertex3f (2,-90,10 );
			glColor3f (0.55, 0.55, 0.55);
			glVertex3f (2,15,10);
			glColor3f (0.55, 0.55, 0.55);
			glVertex3f (2,15,30);
		glEnd();
		//Building 4

		glBegin(GL_QUADS);
			glColor3f (0.35,0.35, 0.35);
			glVertex3f (0, -90,10);//iz ab
			glColor3f (0.35, 0.35,0.35 );
			glVertex3f (0,-90,-30 );//der ab
			glColor3f (0.35, 0.35, 0.35);
			glVertex3f (0,-10,-30);//der arri
			glColor3f (0.35, 0.35, 0.35);
			glVertex3f (0,-10,10);//iz arriba
		glEnd();
				//Building 5

		glBegin(GL_QUADS);
			glColor3f (0.55,0.55, 0.55);
			glVertex3f (-6, -90,-10);//iz ab
			glColor3f (0.55, 0.55,0.55 );
			glVertex3f (-6,-90,-40 );//der ab
			glColor3f (0.55, 0.55, 0.55);
			glVertex3f (-6,10,-40);//der arri
			glColor3f (0.55, 0.55, 0.55);
			glVertex3f (-6,10,-10);//iz arriba
		glEnd();

						//edificio 6

		glBegin(GL_QUADS);
			glColor3f (0.6,0.6, 0.6);
			glVertex3f (10, -90,-40);//iz ab
			glColor3f (0.6, 0.6,0.6 );
			glVertex3f (10,-90,-70 );//der ab
			glColor3f (0.6, 0.6, 0.6);
			glVertex3f (10,19,-70);//der arri
			glColor3f (0.6, 0.6, 0.6);
			glVertex3f (10,19,-40);//iz arriba
		glEnd();


		//edificio 7
		glBegin(GL_QUADS);
			glColor3f (0.75,0.75, 0.75);
			glVertex3f (12, -90,-70);//iz ab
			glColor3f (0.75, 0.75,0.75 );
			glVertex3f (12,-90,-110 );//der ab
			glColor3f (0.75, 0.75, 0.75);
			glVertex3f (12,30,-110);//der arri
			glColor3f (0.75, 0.75, 0.75);
			glVertex3f (12,30,-70);//iz arriba
		glEnd();

				//edificio 8 entre el 5 y 6
		glBegin(GL_QUADS);
			glBegin(GL_QUADS);
			glColor3f (0.65,0.65, 0.65);
			glVertex3f (0, -90,-20);//iz ab
			glColor3f (0.65, 0.65,0.65 );
			glVertex3f (0,-90,-50 );//der ab
			glColor3f (0.65, 0.65, 0.65);
			glVertex3f (0,5,-50);//der arri
			glColor3f (0.65, 0.65, 0.65);
			glVertex3f (0,5,-20);//iz arriba
		glEnd();

		//ventana
		glBegin(GL_QUADS);
			glBegin(GL_QUADS);
			glColor3f (windowHouse,windowHouse, windowHouse);
			glVertex3f (0, -10,-22);//iz ab
			glColor3f (windowHouse, windowHouse,windowHouse );
			glVertex3f (0,-10,-30 );//der ab
			glColor3f (windowHouse, windowHouse, windowHouse);
			glVertex3f (0,1,-30);//der arri
			glColor3f (windowHouse, windowHouse, windowHouse);
			glVertex3f (0,1,-22);//iz arriba
		glEnd();
	}
	calculateFps();
	glutSwapBuffers();
}
void moveRemaining(){
	float s=0.1;
	//bola2
	if(posBall2Y > 0) posBall2Y -= s;
	else { 
		posBall2Y = 50;	posBall2Z = 12;
	}
	//bola3
	if(posBall3Z>10){
		posBall3Z -=s;
	}else{
		if(posBall3Y<0)	posBall3Y +=s;
		else{
			posBall3Y = -10;
			posBall3Z = 50;
		}
	}
	//bola4
	if(posBall4Z>-15){
		posBall4Z -=s;
	}else{
		if(posBall4Y<0)	posBall4Y +=s;
		else{
			posBall4Y = -10;
			posBall4Z = 50;
		}
	}	
}
void moveLight(int s){
	float s1;

	if(s==0) s1=1;
	else s1=0.001;
	
	if(lightPosition==5){
		posBall1Y -= s1 ;
		if(posBall1Y <= 5) lightPosition=6;
	}
	if(lightPosition==6){
		posBall1Z -= s1;
		if(posBall1Z <= 12) lightPosition=1;
	}
	if(lightPosition==1){
		posBall1Y -=s1;
		if(posBall1Y <= 0) lightPosition=8;
	}
	if(lightPosition==8){
		posBall1Z -=s1;
		if(posBall1Z <= -15) lightPosition=9;
	}
	if(lightPosition==9){
		posBall1Y +=s1;
		if(posBall1Y >= 3) lightPosition=10;	
	}
	if(lightPosition==10){
		posBall1Z +=s1;
		if(posBall1Z >= 0) lightPosition=4;	
	}
	if(lightPosition==4){
		posBall1Y+=s1;
		if(posBall1Y >= 12) lightPosition=2;	
	}
	if(lightPosition==2){
		posBall1Z-=s1;
		if(posBall1Z <= -50){
			posBall1Y =50;
			posBall1Z =22;
			lightPosition=5;
		}
	}
}

void reShape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (5, 0, 0.0, 0, 2 , 0, 0.0,1.0, 0.0);
}



void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, winX, 0.0, winY, -1.0, 1.0);
	initTime=glutGet(GLUT_ELAPSED_TIME);
	updateTime=initTime;
}
int update(int elapsed){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(phaseNumber == roomTake){
		zoomY=0;zoomX+=0.01;
		if(zoomX >= 100){
			zoomX=0;
			phaseNumber = consoleTake;
			cSeg1 = forceWait();
		}
	}
	if(phaseNumber == consoleTake){
		//PARTE 1
		if(parte_consola == 0){// M.
			if((cSeg2-cSeg1 >=4) && chat == 0){ chat = 1;	cSeg1 = forceWait();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 1){ chat = 2;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=1) && chat == 2){ chat = 3;	cSeg1 = forceWait();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 3){ chat = 4;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 4){ chat = 5;	phaseNumber = cityTake;	parte_consola = 1;} //M.
		}
		//PARTE 2
		if(parte_consola == 1){
			if((cSeg2-cSeg1 >=3) && chat == 5){ chat = 6;	cSeg1 = forceWait();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 6){ chat = 7;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 7){ chat = 8;	cSeg1 = forceWait();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 8){ chat = 9;	phaseNumber = chipTake; parte_consola = 2;} // M.
		}
		//PARTE 3
		if( parte_consola == 2){
			if((cSeg2-cSeg1 >=5) && chat == 9){ chat = 10;	cSeg1 = forceWait();} // Us.
			if((cSeg2-cSeg1 >=3) && chat == 10){ chat = 11;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 11){ chat = 12;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 12){ chat = 13;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 13){ chat = 14;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 14){ chat = 15;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 15){ chat = 16;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 16){ chat = 17;	cSeg1 = forceWait(); parte_consola = 3;} // A los créditos.
		}

		//CREDITOS
		if( parte_consola == 3){
			if((cSeg2-cSeg1 >=2) && chat == 17){ chat = 18;	cSeg1 = forceWait();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 18){ exit(0);} // TERMINAR PROGRAMA
		}
	}
	if(phaseNumber == chipTake){
		el_an1 = (el_an1+10)%360;
		moveRemaining();
		if(eyeX>10){	eyeX-=0.01;moveLight(0);}
		else if(eyeY<0&&eyeX>2){
			eyeY+=0.01;
			eyeX-=0.01;
			moveLight(0);
		}else{
			if(eyeY<-3){moveLight(0);eyeY+=0.01;}
			else{	
				if(rot_chip<89)	rot_chip = (rot_chip+1)%90;
				else {
					if(!chip_rotado)	cSeg3 = forceWait();
					chip_rotado = 1;
				}
			}
			if((posBall1Z>=-4 && posBall1Z<=4)) moveLight(1);
			else moveLight(0);
			
			if(chip_rotado){
				cSeg4 = forceWait();
				if(cSeg4-cSeg3>=10){
					phaseNumber = consoleTake;
					cSeg1 = forceWait();
				}
			}
		}
	}
	if(phaseNumber== cityTake ){
		if(cloud1_speed>-100 && cloud1_altitude<150){cloud1_speed-=0.005;cloud1_altitude+=0.005;}
		else 	
			if(cloud1_speed>-300){cloud1_speed-=0.051;}
		if(cloud2_speed>-100 && cloud2_altitude<150){cloud2_speed-=0.011;cloud2_altitude+=0.005;}
		else 	
			if(cloud2_speed>-80){cloud2_speed-=0.051;}
		if(cloud3_speed>-100 && cloud3_altitude<150){cloud3_speed-=0.071;cloud3_altitude+=0.005;}
		else 	
			if(cloud3_speed>-80){cloud3_speed-=0.051;cloud3_altitude-=0.001;}
		if(cloud4_speed>-100 && cloud4_altitude<150){cloud4_speed-=0.031;cloud4_altitude+=0.005;}
		else 	
			if(cloud4_speed>-150){cloud4_speed-=0.051;}
	
		if(	x1>=0) x1-=0.0002;
		if( x2>=0) x2-=0.0002;
		if( x3>=0) x3-=0.0002;
		if(	x4>=0) x4-=0.0001;
		if( x5>=0) x5-=0.0002;
		if( x6>=0) x6-=0.0001;
		zoomX+=0.01; zoomZ=26; zoomY=5;

		if(windowHouse>0.5 && !windowIsWhite){windowHouse-=0.0001;windowIsWhite=false;}
		else{ windowIsWhite=true;windowHouse+=0.001;}

		if(zoomX >= 100){		
			phaseNumber= roomTake;
			zoomX= 0;}	
		}
 return 1;
 }
void keyboard (unsigned char key, int x, int y)//FUNCION PARA TERMINAR 
{
	switch (key) {
	  case 27://ESCAPE 
		  exit(0);
		  break;
	  default:
		  break;
	}
}
void onIdle(void)
{
	int updateNow = glutGet(GLUT_ELAPSED_TIME);
	int elapsed = updateNow-updateTime;

	if (elapsed > 0)
	{
		updateTime = updateNow;
		if (update(elapsed))
		{
			glutPostRedisplay();
		}
	}
}

void main(int argc, char * argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (winX, winY); 
	glutInitWindowPosition (0, 50);
	glutCreateWindow ("Animacion Victor Ahuir & Carles Soriano");
	//glutFullScreen();
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reShape);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(keyboard);
	glutMainLoop(); 
}