	/*
	Ahuir Domínguez,Victor
	Soriano Pérez,Carles Salvador
	IGU: 3o Facultad de Informática Trabajo Voluntario 1: Animación alámbrica*/
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <windows.h> 

//********************************************************************
/* Variables globales internas (mejor no las toques) */
int updateTime;				// Soporte de animación
int initTime;				// Soporte del cálculo de fps
unsigned int nFrames=0;		// Contador del número de frames visualizados
float fps=60;				// Velocidad actual de visualización (frames por segundo)


const unsigned int winX = 1440;
const unsigned int winY = 850;


float zoomx=0, zoomy=0, zoomz=0;

//Variables Escenas
int CIUDAD = 0, HABITACION = 1, CONSOLA = 2, CHIP = 3;
int fase=2; //Fase de inicio

//Variables para la ciudad
float vel_nube1=100, alt_nube1=50, vel_nube2=100, alt_nube2=30, vel_nube3=100, alt_nube3=10, vel_nube4=100, alt_nube4=50;
float x1=0.98,x2=0.83,x3=0.27,x4=0.08,x5=0.54,x6=1;
float ventana=1;
float nube1=0.6;
float nube2=0.72;
float nube3=0.72;
bool ventana_blanco=false;
//Variables para el Chip
int posluz=5; //si falla el pos. de la luz poner posluz=5 en el display de consola
int rot_chip, chip_rotado=0;
int el_an1; 
float ax,ay=1.0,az;
float ojox=100,ojoy=-30,ojoz=0;
float ApuntaX=0,ApuntaY=0,ApuntaZ=0;
//haces de luz
float pos_boly=50,pos_bolz=22;
float pos_boly2=50,pos_bolz2=12;
float pos_boly3=-10,pos_bolz3=50;
float pos_boly4=-10,pos_bolz4=50;
float pos_elx=0,pos_ely=0,pos_elz=0.0;

//Variables para la consola
int parte_consola = 0;
int iSeg1, iSeg2;
int cSeg1, cSeg2, cSeg3, cSeg4;
int RED, GREEN;
int chat=0,letras=1;

//*****************************************************************************************************

int espera(){
     int t;
     t=(int)clock()/CLOCKS_PER_SEC;
	 return t;
}
void draw_text(unsigned int x, unsigned int y, char *text, int color, void *font = GLUT_BITMAP_HELVETICA_18) {
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

void calcula_fps(void)
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
	draw_text(50, 50, msg, 3);
}

void reinicia(void){
		glMatrixMode (GL_MODELVIEW) ;
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear (GL_COLOR_BUFFER_BIT);
}

void dialogos(void){
	//PARTE 1
	if(chat == 0) draw_text(600,300,">> Hello, visitor",2);
	if(chat == 1) draw_text(600,300,"- What?, Where am I?",1);
	if(chat == 2) { //U
		draw_text(600,300,"- What?, Where am I?",1);
		draw_text(600,320,"last thing I remembered I was....",1);
	}
	if(chat == 3) draw_text(600,300,">> Don't worry, you're safe now",2);
	if(chat == 4) { //M
		draw_text(600,300,">> Don't worry, you're safe now",2);
		draw_text(600,320,">> Look...",2);
	}

	//PARTE 2
	if(chat == 5) { //U
		draw_text(600,300,"- Hey wait, you didn't say me",2);
		draw_text(600,320,"who you are yet...",2);
	}
	if(chat == 6) draw_text(600,300,">> I'm VC2012",1);
	if(chat == 7) draw_text(600,300,"- What are you?",2);
	if(chat == 8) draw_text(600,300,">> Look",1);
	
	//PARTE 3
	if(chat == 9) 	draw_text(600,300,"- So you are a machine",2);
	if(chat == 10) {
		draw_text(600,300,">> Yes, as you last saw, we are",1);
		draw_text(600,320,"based in electrical impulses.",1);
	}
	if(chat == 11)	draw_text(600,300,"- We are? You know I'm a human.",2);
	if(chat == 12)	draw_text(600,300,"- Do you? I can't be a machine.",2);
	if(chat == 13){
		draw_text(600,300,"- I don't like this anymore.",2);
		draw_text(600,320,"- Let me out.",2);
	}
	if(chat == 14) draw_text(600,300,">> Sure",1);
	if(chat == 15) {
		draw_text(600,300,">> Subject BD350XY -> Terminate",1);
		draw_text(600,320,"> Reason:",1);
	}
	if(chat == 16) {
		draw_text(600,300,">> Subject BD350XY -> Terminate",1);
		draw_text(600,320,"> Reason: Reasoning.",1);
		  
	}
	//CREDITOS
	if(chat == 17) draw_text(600,280,"IGU 2012 - Proyecto 1 (Alambrico)",3);
	if(chat == 18){
		draw_text(600,280,"IGU 2012 - Proyecto 1 (Alambrico)",3);
		draw_text(600,300,"Victor Ahuir Dominguez", 1);
		draw_text(600,320,"Carles S. Soriano Perez", 2);
	}

	cSeg2 = espera();
}
void display(void)
{	 
	if(fase == CONSOLA){
		reinicia();
		dialogos();
	}
	if(fase == CHIP){
		reinicia();
		glLoadIdentity();
		gluLookAt (ojox, ojoy,ojoz, ApuntaX, ApuntaY, ApuntaZ, ax, ay, az);
		glTranslatef(zoomx,zoomy,zoomz);

		//BASE
		// Xip
		glPushMatrix();
			glRotatef(-(GLfloat)rot_chip,1,0,0);
			glBegin(GL_QUADS);
				glColor3f (0,0.5,0);
				glVertex3f (0,-15,30); glVertex3f (0,-15,-25);
				glVertex3f (0,15,-25); glVertex3f (0,15,30);
			glEnd();
			// XIP (borera)
			glBegin(GL_LINE_LOOP);
				glColor3f (0,1,0);
				glVertex3f (0,-15,30); glVertex3f (0,-15,-25); 
				glVertex3f (0,15,-25); glVertex3f (0,15,30);
			glEnd();
			// PROC
			glBegin(GL_QUADS);
				glColor3f (0.2,0.2,0.2);
				glVertex3f (0,8,15); glVertex3f (0,8,-5); 
				glVertex3f (0,-5,-5); glVertex3f (0,-5,15);
			glEnd();
			// PROC (borera)
			glBegin(GL_LINE_LOOP);
				glColor3f (0,0,0);
				glVertex3f (0,8,15); glVertex3f (0,8,-5); 
				glVertex3f (0,-5,-5); glVertex3f (0,-5,15);
			glEnd();
			// MEM
			glBegin(GL_QUADS);
				glColor3f (0.2,0.2,0.2);
				glVertex3f (0,5,-20); glVertex3f (0,5,-12); 
				glVertex3f (0,-5,-12); glVertex3f (0,-5,-20);
			glEnd();
			// MEM (borera)
			glBegin(GL_LINE_LOOP);
				glColor3f (0,0,0);
				glVertex3f (0,5,-20); glVertex3f (0,5,-12); 
				glVertex3f (0,-5,-12); glVertex3f (0,-5,-20);
			glEnd();
			// Cables
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
			//Bola (impulso electrico)
			glPushMatrix(); //prota
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, pos_boly, pos_bolz);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			//decorativas
			glPushMatrix(); //BOLA2
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, pos_boly2, pos_bolz2);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix(); //BOLA3
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, pos_boly3, pos_bolz3);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix(); //BOLA4
				glColor3f (1.0, 1.0, 1.0);
				glTranslatef (1, pos_boly4, pos_bolz4);
				glutWireSphere(0.5, 10, 8);
			glPopMatrix();
			glPushMatrix();
				//NucleoAtomo	
				glColor3f (0, 0,0.75);
				glTranslatef (1, pos_boly, pos_bolz);
				glutWireSphere(0.075, 10, 8);
				//Electrones (Respecto posición Nucleo Atomo
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
			//Superior
				// PROC Top
				//glTranslatef(zoomx,zoomy,zoomz); CREC QUE SOBRA
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
				// PROC Top (Borera)
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
				// MEM Top (Borera)
				glBegin(GL_LINE_LOOP);
					glColor3f (0,0,0);
					glVertex3f (2,5,-20); glVertex3f (2,5,-12); 
					glVertex3f (2,-5,-12); glVertex3f (2,-5,-20);
				glEnd();
		glPopMatrix();
		//cSeg4=espera();
	}
	if(fase == HABITACION){
		reinicia();
		zoomz=0; zoomy=0;
		glLoadIdentity();
		gluLookAt (100, 30,0, 0, 0, 0, 0.0, 1.0, 0.0);
		glTranslatef(zoomx,zoomy,zoomz);
		 
		//////////suelo////////////
		glBegin(GL_QUADS);
			glColor3f (0.75, 0.75, 0.75);//blanco
			glVertex3f (-60, 0, -60.0);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60,0, 60.0);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (60,0,60.0);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (60, 0,-60.0);
		glEnd();
		//PARED IZQUIERDA
		glBegin(GL_QUADS);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (60, 0,60);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60,0,60 );
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60,60,60);
			glColor3f (1, 1, 1);
			glVertex3f (60,60,60);
		glEnd();
		//pared derecha
		glBegin(GL_QUADS);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60, 0,-60);//rojo
			glColor3f (1, 1, 1);//blanco
			glVertex3f (60,0,-60 );//verde
			glColor3f (1, 1, 1);//blanco
			glVertex3f (60,60,-60);
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60,60,-60);
		glEnd();
		//pared fondo
		glBegin(GL_QUADS);
			glColor3f (0.85, 0.85,0.85);//blanco
			glVertex3f (-60, 0,60);//rojo
			glColor3f (0.85, 0.85, 0.85);//blanco
			glVertex3f (-60,0,-60 );//verde
			glColor3f (1, 1, 1);//blanco
			glVertex3f (-60,60,-60);
			glColor3f (1, 1, 1);
			glVertex3f (-60,60,60);
		glEnd();

		//monitor
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
		//tablero mesa
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
		
		//teclado
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
		//raton
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
	if(fase== CIUDAD){
		reinicia();
		glLoadIdentity();
		gluLookAt (100, 0,0, 0, 0, 0, 0.0, 1.0, 0.0);
		glTranslatef(zoomx,zoomy,zoomz);
		//Fondo
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
		//nube 0
	glPushMatrix();
		glColor3f (nube1 ,nube2, nube2);
		glTranslatef(-50,alt_nube2,vel_nube4);
		glScalef (0.5,1,10);
		glutWireSphere(10, 100, 10);   
	glPopMatrix();

		//nube 1
	glPushMatrix();
		glColor3f (nube1 ,nube2, nube3);
		glTranslatef(-50,alt_nube1,vel_nube1);
		glScalef (0.5,0.1,2);
		glutWireSphere(10, 100, 10);   
	glPopMatrix();

//nube 2
	glPushMatrix();
		glColor3f (0.58 ,0.73, 0.78);
		glTranslatef(-50,alt_nube2,vel_nube2);
		glScalef (0.5,0.05,2);			
		glutWireSphere(10, 100, 10);   
	glPopMatrix();
	
//nube 3
		glPushMatrix();
			glColor3f (0.58 ,0.73, 0.78);
			glTranslatef(-10,alt_nube3,vel_nube3);
			glScalef (0.5,0.25,3);
			glutWireSphere(10, 100, 10);   
		glPopMatrix();
//nube 4
		glPushMatrix();
			glColor3f (0.58 ,0.73, 0.78);
			glTranslatef(-9,alt_nube4,vel_nube4);
			glScalef (0.5,0.25,3);
			glutWireSphere(10, 100, 50);   
		glPopMatrix();

	
		//edificio 1

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

			//edificio 2

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

				//edificio 3

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
		//edificio 4

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
				//edificio 5

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
			glColor3f (ventana,ventana, ventana);
			glVertex3f (0, -10,-22);//iz ab
			glColor3f (ventana, ventana,ventana );
			glVertex3f (0,-10,-30 );//der ab
			glColor3f (ventana, ventana, ventana);
			glVertex3f (0,1,-30);//der arri
			glColor3f (ventana, ventana, ventana);
			glVertex3f (0,1,-22);//iz arriba
		glEnd();
	}
	calcula_fps();
	glutSwapBuffers();
}
void mueve_resto(){
	float s=0.1;
	//bola2
	if(pos_boly2 > 0) pos_boly2 -= s;
	else { 
		pos_boly2 = 50;	pos_bolz2 = 12;
	}
	//bola3
	if(pos_bolz3>10){
		pos_bolz3 -=s;
	}else{
		if(pos_boly3<0)	pos_boly3 +=s;
		else{
			pos_boly3 = -10;
			pos_bolz3 = 50;
		}
	}
	//bola4
	if(pos_bolz4>-15){
		pos_bolz4 -=s;
	}else{
		if(pos_boly4<0)	pos_boly4 +=s;
		else{
			pos_boly4 = -10;
			pos_bolz4 = 50;
		}
	}	
}
void mueve_luz(int s){
	float s1;

	if(s==0) s1=1;
	else s1=0.001;
	
	if(posluz==5){
		pos_boly -= s1 ;
		if(pos_boly <= 5) posluz=6;
	}
	if(posluz==6){
		pos_bolz -= s1;
		if(pos_bolz <= 12) posluz=1;
	}
	if(posluz==1){
		pos_boly -=s1;
		if(pos_boly <= 0) posluz=8;
	}
	if(posluz==8){
		pos_bolz -=s1;
		if(pos_bolz <= -15) posluz=9;
	}
	if(posluz==9){
		pos_boly +=s1;
		if(pos_boly >= 3) posluz=10;	
	}
	if(posluz==10){
		pos_bolz +=s1;
		if(pos_bolz >= 0) posluz=4;	
	}
	if(posluz==4){
		pos_boly+=s1;
		if(pos_boly >= 12) posluz=2;	
	}
	if(posluz==2){
		pos_bolz-=s1;
		if(pos_bolz <= -50){
			pos_boly =50;
			pos_bolz =22;
			posluz=5;
		}
	}
}

void reshape (int w, int h)
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

	if(fase == HABITACION){
		zoomy=0;zoomx+=0.01;
		if(zoomx >= 100){
			zoomx=0;
			fase = CONSOLA;
			cSeg1 = espera();
		}
	}
	if(fase == CONSOLA){
		//PARTE 1
		if(parte_consola == 0){// M.
			if((cSeg2-cSeg1 >=4) && chat == 0){ chat = 1;	cSeg1 = espera();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 1){ chat = 2;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=1) && chat == 2){ chat = 3;	cSeg1 = espera();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 3){ chat = 4;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 4){ chat = 5;	fase = CIUDAD;	parte_consola = 1;} //M.
		}
		//PARTE 2
		if(parte_consola == 1){
			if((cSeg2-cSeg1 >=3) && chat == 5){ chat = 6;	cSeg1 = espera();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 6){ chat = 7;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 7){ chat = 8;	cSeg1 = espera();} // Us.
			if((cSeg2-cSeg1 >=2) && chat == 8){ chat = 9;	fase = CHIP; parte_consola = 2;} // M.
		}
		//PARTE 3
		if( parte_consola == 2){
			if((cSeg2-cSeg1 >=5) && chat == 9){ chat = 10;	cSeg1 = espera();} // Us.
			if((cSeg2-cSeg1 >=3) && chat == 10){ chat = 11;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 11){ chat = 12;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 12){ chat = 13;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 13){ chat = 14;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 14){ chat = 15;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 15){ chat = 16;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=2) && chat == 16){ chat = 17;	cSeg1 = espera(); parte_consola = 3;} // A los créditos.
		}

		//CREDITOS
		if( parte_consola == 3){
			if((cSeg2-cSeg1 >=2) && chat == 17){ chat = 18;	cSeg1 = espera();} // M.
			if((cSeg2-cSeg1 >=3) && chat == 18){ exit(0);} // TERMINAR PROGRAMA
		}
	}
	if(fase == CHIP){
		el_an1 = (el_an1+10)%360;
		mueve_resto();
		if(ojox>10){	ojox-=0.01;mueve_luz(0);}
		else if(ojoy<0&&ojox>2){
			ojoy+=0.01;
			ojox-=0.01;
			mueve_luz(0);
		}else{
			if(ojoy<-3){mueve_luz(0);ojoy+=0.01;}
			else{	
				if(rot_chip<89)	rot_chip = (rot_chip+1)%90;
				else {
					if(!chip_rotado)	cSeg3 = espera();
					chip_rotado = 1;
				}
			}
			if((pos_bolz>=-4 && pos_bolz<=4)) mueve_luz(1);
			else mueve_luz(0);
			
			if(chip_rotado){
				cSeg4 = espera();
				if(cSeg4-cSeg3>=10){
					fase = CONSOLA;
					cSeg1 = espera();
				}
			}
		}
	}
	if(fase== CIUDAD ){
		if(vel_nube1>-100 && alt_nube1<150){vel_nube1-=0.005;alt_nube1+=0.005;}
		else 	
			if(vel_nube1>-300){vel_nube1-=0.051;}
		if(vel_nube2>-100 && alt_nube2<150){vel_nube2-=0.011;alt_nube2+=0.005;}
		else 	
			if(vel_nube2>-80){vel_nube2-=0.051;}
		if(vel_nube3>-100 && alt_nube3<150){vel_nube3-=0.071;alt_nube3+=0.005;}
		else 	
			if(vel_nube3>-80){vel_nube3-=0.051;alt_nube3-=0.001;}
		if(vel_nube4>-100 && alt_nube4<150){vel_nube4-=0.031;alt_nube4+=0.005;}
		else 	
			if(vel_nube4>-150){vel_nube4-=0.051;}
	
		if(	x1>=0) x1-=0.0002;
		if( x2>=0) x2-=0.0002;
		if( x3>=0) x3-=0.0002;
		if(	x4>=0) x4-=0.0001;
		if( x5>=0) x5-=0.0002;
		if( x6>=0) x6-=0.0001;
		zoomx+=0.01; zoomz=26; zoomy=5;

		if(ventana>0.5 && !ventana_blanco){ventana-=0.0001;ventana_blanco=false;}
		else{ ventana_blanco=true;ventana+=0.001;}

		if(zoomx >= 100){		
			fase= HABITACION;
			zoomx= 0;}	
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
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(keyboard);
	glutMainLoop(); 
}