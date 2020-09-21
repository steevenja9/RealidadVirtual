
#include <glew.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include <FreeImage.h>
#include <GL/freeglut.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

//------------------Declaracion de Variables--------------------------//
int menu();
int ventana = 0;
int color; 


char c[1];
const float PI = 3.1416;
float DEPTH = 6.0; //Con 8 ya empieza a dar problema
// Start and end of camera movement
const int ENDX = 10, STARTX = -500;		//Cuando pulsamos A--> El movimiento que produce
// Angle of branches, and depth of tree
float ANGLE = 10.0, depth = 0;
vector<string> *trees = new vector<string>();


GLuint textureId1;
GLuint textureId2;
GLuint textureId3;


double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;
bool cam = false;
float eyeX, eyeY, eyeZ, lookX, lookY, lookZ,
upX, upY, upZ, fieldOfView, length = 0.001, num = 0,
incr = 0.1;

float lineWidth = 5.7;
GLfloat text = -1.0f; // L-System
string str = "X";
COORD coord = { 0, 0 }; // this is global variable 
int colorT = 0; // Tronco
int colorH = 0; //Hoja
bool quitarhojas = false;



/*center of axis is set to the top left cornor of the screen*/
void gotoxy(int x, int y){
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void push(){
	glPushMatrix();
	if (lineWidth > 0)
		lineWidth += 1;
}

void pop(){
	glPopMatrix();
	lineWidth -= 1;
}

void rotL(){
	glRotatef(ANGLE, 1, 0, 0);
	glRotatef(ANGLE * 4, 0, 1, 0);
	glRotatef(ANGLE, 0, 0, 1);
}

void rotR(){
	glRotatef(-ANGLE, 1, 0, 0);
	glRotatef(ANGLE * 4, 0, 1, 0);
	glRotatef(-ANGLE, 0, 0, 1);
}


GLuint Texturas(char* filename, GLuint textura){
	
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	FreeImage_Unload(pImage);

	return textura;
}

void leaf(){
	glPushAttrib(GL_LIGHTING_BIT); //saves current lighting stuff
	//glColor3f(0.50, 1.0, 0.0);

	//Verde Marroncito
	GLfloat ambient[4] = { 0.55, 0.27, 0.07 };    // ambient reflection
	GLfloat specular[4] = { 0.0, 0.27, 0.07 };   // specular reflection
	GLfloat diffuse[4] = { 0.0, 0.27, 0.07 };   // diffuse reflection

	if (colorH == 2){//Rojo oscuro
		GLfloat aux1[4] = { 1.0, 0.0, 0.2 };    // ambient reflection
		GLfloat aux2[4] = { 0.0, 0.0, 0.0 };    // specular reflection
		GLfloat aux3[4] = { 0.0, 0.0, 0.0 };    // diffuse reflection

		for (int i = 0; i < 4; i++){
			ambient[i] = aux1[i];
			specular[i] = aux2[i];
			diffuse[i] = aux3[i];
		}
	}
	else if (colorH == 3){ //BLANCO Verde fosforito
		GLfloat aux1[4] = { 1.0, 1.0, 1.0 };    // ambient reflection
		GLfloat aux2[4] = { 1.0, 1.0, 1.0 };    // specular reflection
		GLfloat aux3[4] = { 1.0, 1.0, 1.0 };    // diffuse reflection

		for (int i = 0; i < 4; i++){
			ambient[i] = aux1[i];
			specular[i] = aux2[i];
			diffuse[i] = aux3[i];
		}
	}



	// set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	// set the specular reflection for the object      
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);


	// set the size of the specular highlights
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glBindTexture(GL_TEXTURE_2D, textureId1);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //En vez de combinar reemplaza la textura

	//glutSolidCube(depth+1);
	//Forma de las hojas
	glBegin(GL_TRIANGLES);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.6, 0, 1.6);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 2, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);

	glTexCoord2f(-1.0f, 0.0f);
	glVertex3f(-1.2, 0, -2.0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1.0, 0);
	
	glEnd();
	glPopAttrib();
}

void drawLine(){
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff

	//MARRON
	GLfloat ambient[4] = { 0.55, 0.24, 0.07 };    // ambient reflection
	GLfloat specular[4] = { 0.5, 0.08, 0.015 };    // specular reflection
	GLfloat diffuse[4] = { 0.25, 0.08, 0.015 };    // diffuse reflection

	if (colorT == 2){//NEGRO
		GLfloat aux1[4] = { 0.0, 0.0, 0.0 };    // ambient reflection
		GLfloat aux2[4] = { 0.0, 0.0, 0.0 };    // specular reflection
		GLfloat aux3[4] = { 0.0, 0.0, 0.0 };    // diffuse reflection

		for (int i = 0; i < 4; i++){
			ambient[i] = aux1[i];
			specular[i] = aux2[i];
			diffuse[i] = aux3[i];
		}
	}
	else if (colorT == 3){ //BLANCO
		GLfloat aux1[4] = { 1.0, 1.0, 1.0 };    // ambient reflection
		GLfloat aux2[4] = { 1.0, 1.0, 1.0 };    // specular reflection
		GLfloat aux3[4] = { 1.0, 1.0, 1.0 };    // diffuse reflection

		for (int i = 0; i < 4; i++){
			ambient[i] = aux1[i];
			specular[i] = aux2[i];
			diffuse[i] = aux3[i];
		}
	}



	// set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	// set the specular reflection for the object      
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	glLineWidth(lineWidth);
	glBindTexture(GL_TEXTURE_2D, textureId2);

	if (length > 1){
		text += 0.1;
	}

	glBegin(GL_LINES);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(lineWidth, text);
	glVertex3f(0, length, 0);
	glEnd();

	glTranslatef(0, length, 0);
	glPopAttrib();
}

void draw(){

	string ch = "";
	string LSystem = trees->at(depth);
	for (int i = 0; i < LSystem.length(); i++){
		ch = LSystem.at(i);

		if (ch.compare("D") == 0){
			drawLine();
		}else if(ch.compare("X") == 0){ //La inicial crezca mas
			drawLine();
			drawLine();
		}
		else if (ch.compare("[") == 0){
			push();
		}
		else if (ch.compare("]") == 0){
			pop();
		}
		else if (ch.compare("V") == 0){
			leaf();
		}
		else if (ch.compare("R") == 0){
			rotR();
		}
		else if (ch.compare("L") == 0){
			rotL();
		}
	}
}

void expand(float num){
	string ch = "";

	for (int i = 0; i < str.length(); i++){
		ch = str.at(i);

		if (ch.compare("D") == 0 && i<3){ //La segunda comparacion es para controlar su crecimiento
			
			float x = rand();
			if (x > 0.8){
				str.replace(i, 1, "DDD");
			}
			else{
				str.replace(i, 1, "DD");
			}
		}
		else if (ch.compare("X") == 0){
			if (quitarhojas){

				if (num < 0.4){
					float x = rand();
					if (x > 0.5){
						str.replace(i, 1, "DD[RXR]DD[RXL]LX");
					}
					else{
						str.replace(i, 1, "DD[LXD]DD[RXD]LX");
					}

				}
				else {
					float x = rand();
					if (x > 0.5){
						str.replace(i, 1, "DD[RXL]DD[LXR]RX");
					}
					else{
						str.replace(i, 1, "DD[RXD]DD[LXD]RX");
					}
				}
				i = i + 16;	//11
			}
			else{

				if (num < 0.4){
					float x = rand();
					if (x > 0.5){
						str.replace(i, 1, "DD[RVXVRV]DD[RVXVLV]LVX");
					}
					else{
						str.replace(i, 1, "DD[LVXVDV]DD[RVXVDV]LVX");
					}

				}
				else {
					float x = rand();
					if (x > 0.5){
						str.replace(i, 1, "DD[RVXVLV]DD[LVXVRV]RVX");
					}
					else{
						str.replace(i, 1, "DD[RVXVDV]DD[LVXVDV]RVX");
					}
				}
				i = i + 22;	//11
			}

		}

	}
	trees->push_back(str);
}

void display(void){
	// start by clearing the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, 1.0, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);

	glPushMatrix();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Color del suelo
	glPushAttrib(GL_LIGHTING_BIT); //saves current lighting stuff

	GLfloat ambient[4] = { 0.8, 0.4, 0.2 };    // ambient reflection
	GLfloat diffuse[4] = { 0.8, 0.4, 0.2 };   // diffuse reflection  

	// set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	glBindTexture(GL_TEXTURE_2D, textureId3);
	
	//Dibujo el suelo
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-400, 0, -600);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(400, 0, -600);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(400, 0, 600);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-400, 0, 600);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-400, 0, -600);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(400, 0, 600);

	glEnd();
	glPopMatrix();
	glPopAttrib();

	draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

/*
 * Funcion que genera el movimiento de las ramas
 */
void animate(){
	if (lastTime == 0)
		lastTime = timeGetTime();

	elapsedTime = timeGetTime() - lastTime;

	// Change the angle to make it blow in the wind
	float numR = (float)rand() / RAND_MAX;

	if (ANGLE > 21.5){
		if (numR < 0.5){
			incr = -0.05;
		}
		else {
			incr = -0.01;
		}
	}
	else if (ANGLE < 18.5){
		if (numR > 0.5){
			incr = 0.05;
		}
		else {
			incr = 0.01;
		}
	}
	ANGLE += incr;

	if (depth < DEPTH)
		length += 0.001;

	if (elapsedTime - lastElapsedTime > 2000 && depth < DEPTH){
		depth++;
		lastElapsedTime = elapsedTime;
		cout << length << " ";
	}
	elapsedTime = elapsedTime / 5000;
	float t = (sin((elapsedTime*PI - PI / 2)) + 1) / 2;
	float p = (1 - t)*STARTX + t*ENDX;

	if (cam)
		eyeX = p;
	glutPostRedisplay();

}

/*
 * Funcion que lee por teclado
 */
void keyboard(unsigned char key, int x, int y){ //Se mueve la camara

	switch (key) {
	case 113:			// q - Exit the program
		exit(0);
		break;
	case 119:			// w - Reset the camera
		fieldOfView = 45;
		eyeX = 350;
		eyeY = 50;
		eyeZ = 200;
		lookX = 0;
		lookY = 50;
		lookZ = 0;
		break;
	case 122:			// z - Reduce the field of view of the camera
		fieldOfView -= 5;
		glutPostRedisplay();
		break;
	case 120:			// x - Increase the field of view of the camera
		fieldOfView += 5;
		glutPostRedisplay();
		break;
	case 115:			// s - Stop moving the camera
		cam = false;
		break;
	case 97:			// a - Move the camera
		cam = true;
		break;
	case 100:			// d - Increase camera X-coordinate
		eyeX++;
		break;
	case 102:			// f - Decrease camera X-coordinate
		eyeX--;
		break;
	case 103:			// g - Increase camera Y-coordinate
		eyeY++;
		break;
	case 104:			// h - Decrease camera Y-coordinate
		eyeY--;
		break;
	case 118:			// v - Increase camera Z-coordinate
		eyeZ++;
		break;
	case 98:			// b - Decrease camera Z-coordinate
		eyeZ--;
		break;
	case 'm':
		glutDestroyWindow(ventana);
		break;
	}
}

void keyboardArrow(int key, int x, int y) { //Nos movemos nosotros
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		//lookZ--;
		lookX++;
		break;
	case GLUT_KEY_LEFT:
		//lookZ++;
		lookX--;
		break;
	case GLUT_KEY_UP:
		lookY++;
		break;
	case GLUT_KEY_DOWN:
		lookY--;
		break;
	}
	glutPostRedisplay();
}

void Vcontroles(){

	gotoxy(10, 6); cout << "q - Salir del programa";
	gotoxy(10, 7); cout << "w - Reiniciar camara";
	gotoxy(10, 8); cout << "z - Reducir el campo de vision de la camara";
	gotoxy(10, 9); cout << "x - Incrementar el campo de vision de la camara";
	gotoxy(10, 10); cout << "s - Dejar de mover la camara";
	gotoxy(10, 11); cout << "a - Mueve la camara";
	gotoxy(10, 12); cout << "d - Aumentar la coordenada X de la camara";
	gotoxy(10, 13); cout << "f - Disminuir la coordenada X de la camara";
	gotoxy(10, 14); cout << "g - Aumentar la coordenada Y de la camara";
	gotoxy(10, 15); cout << "h - Disminuir la coordenada Y de la camara";
	gotoxy(10, 16); cout << "v - Aumentar la coordenada Z de la camara";
	gotoxy(10, 17); cout << "b - Disminuir la coordenada Z de la camara";
	gotoxy(10, 18); cout << "Flecha Arriba - Nos movemos hacia arriba";
	gotoxy(10, 19); cout << "Flecha Abajo - Nos movemos hacia abajo";
	gotoxy(10, 20); cout << "Flecha Derecha - Nos movemos hacia la derecha";
	gotoxy(10, 21); cout << "Flecha Izquierda - Nos movemos hacia la izquierda";
	gotoxy(10, 22); cout << "Otra tecla - Volver al menu principal";
	gotoxy(10, 24); system("pause");

}

void Mvariables(){
	system("cls");

	float tm, an;
	int op, ca, ch;

	do{
		system("cls");
		gotoxy(8, 7); cout << "Elige una opcion: ";
		gotoxy(10, 8); cout << "1.Tamano maximo del arbol(maximo 8). ";
		gotoxy(10, 9); cout << "2.Ancho del tronco y ramas (maximo 10). ";
		gotoxy(10, 10); cout << "3.Quitar hojas. ";
		gotoxy(10, 11); cout << "4.Colores del tronco. ";
		gotoxy(10, 12); cout << "5.Colores de las hojas. ";
		gotoxy(10, 13); cout << "6.volver para ejecutar. ";
		gotoxy(10, 15); cin >> op;
		switch (op){
		case 1:
			tm = -1.0;
			while (tm < 1 || tm > 8){
				system("cls");
				gotoxy(10, 8); cout << "Tamano del arbol (max 8): ";
				gotoxy(10, 9); cin >> tm;

				if (!cin){
					cin.clear();
					cin.ignore();
				}
			}

			DEPTH = tm;
			break;

		case 2:
			an = -1.0;
			while (an < 1 || an > 10){
				system("cls");
				gotoxy(10, 8); cout << "Ancho del arbol (max 10): ";
				gotoxy(35, 8); cin >> an;
				
				if (!cin){
					cin.clear();
					cin.ignore();
				}
			}
			lineWidth = an;
			break;

		case 3:
			system("cls");
			gotoxy(8, 8); cout << "Quitar hojas(s/n): ";
			cin >> c;
			if (c[0] == 's' || c[0] == 'S')
				quitarhojas = true;
			else
				quitarhojas = false;
			break;

		case 4:
			ca = 0;
			while (ca < 1 || ca > 3){
				system("cls");
				gotoxy(8, 8); cout << "Color tronco: ";
				gotoxy(10, 9); cout << "1.Marron ";
				gotoxy(10, 10); cout << "2.Negro ";
				gotoxy(10, 11); cout << "3.Blanco ";
				gotoxy(10, 12); cin >> ca;
				if (!cin){
					cin.clear();
					cin.ignore();
				}
			}

			colorT = ca;
			break;

		case 5:
			ch = 0;
			while (ch < 1 || ch > 3){
				system("cls");
				gotoxy(8, 8); cout << "Color Hojas: ";
				gotoxy(10, 9); cout << "1.Verde marron";
				gotoxy(10, 10); cout << "2.Rojo oscuro  ";
				gotoxy(10, 11); cout << "3.Verde fosforito ";
				gotoxy(10, 12); cin >> ch;
				if (!cin){
					cin.clear();
					cin.ignore();
				}
			}
			
			colorH = ch;
			break;
		}
	} while (op != 6);
}

int menu(){
	system("color 70"); //negro y cian 0B  

	// ESQUINAS //
	gotoxy(0, 24);
	cout << "*";
	gotoxy(100, 24);
	cout << "*";

	// A a B //
	for (int i = 1; i<100; i++){
		gotoxy(i, 0);
		cout << "-";
	}
	for (int i = 1; i<100; i++){
		gotoxy(i, 3);
		cout << "-";
	}

	// B a D //
	for (int l = 1; l<24; l++){
		gotoxy(100, l);
		cout << "|";
	}

	// C a D //
	for (int j = 1; j<100; j++){
		gotoxy(j, 24);
		cout << "-";
	}
	for (int j = 1; j<100; j++){
		gotoxy(j, 22);
		cout << "-";
	}

	// A a C //
	for (int k = 1; k<24; k++){
		gotoxy(0, k);
		cout << "|";
	}

	int opcion;
	gotoxy(2, 1); cout << "Grupo: ";
	gotoxy(10, 1); cout << "Jesus Delgado";
	gotoxy(30, 1); cout << "Jaime Puerta ";
	gotoxy(50, 1); cout << "Tomas Iglesias ";
	gotoxy(28, 3); cout << "-Realidad Virtual Arbol(L-System)";
	gotoxy(6, 6);  cout << "Elija una opcion: ";
	gotoxy(10, 8); cout << "1. Ver controles. ";
	gotoxy(10, 9); cout << "2. Modificar Arbol. ";
	gotoxy(10, 10); cout << "3. Salir. ";
	gotoxy(10, 11); cout << "4. Ejecutar. ";

	gotoxy(15, 14); cout << "Opcion: ";
	gotoxy(26, 13); cout << "______";
	gotoxy(26, 14); cout << "______";
	gotoxy(25, 14); cout << "|";
	gotoxy(25, 14); cout << "|";
	gotoxy(32, 14); cout << "|";
	gotoxy(32, 14); cout << "|";
	gotoxy(26, 14); cin >> opcion;

	return opcion;
}



int main(int argc, char** argv){

		int op = 0;
		do{
			system("cls");
			op = menu();
			switch (op)
			{
			case 1:
				system("cls");
				Vcontroles();
				break;
			case 2:
				Mvariables();
				system("cls");
				break;
			case 3:
				system("cls");
				break;
			default:
				break;
			}
			
		} while (op != 4 && op!=3);

		if (op == 4){
			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(1000, 600);
			glutInitWindowPosition(0, 0);
			ventana = glutCreateWindow("Practica RV: L-System");
			glClearColor(0.1922, 0.2314, 0.3059, 0.0); //Darle el color a toda la ventana

			textureId1 = Texturas("Textures/Hoja.jpg", textureId1);
			textureId2 = Texturas("Textures/Arbol.jpg", textureId2);
			textureId3 = Texturas("Textures/cesped.jpg", textureId3);

			fieldOfView = 45;
			eyeX = 250;
			eyeY = 50;
			eyeZ = 100;
			lookX = 0;
			lookY = 50;
			lookZ = 0;
			srand(time(NULL));
			num = (float)rand() / RAND_MAX;

			// set the lighting
			glShadeModel(GL_SMOOTH);
			GLfloat lightP[4] = { 0.0, 800.0, 0.0, 1.0 };
			glLightfv(GL_LIGHT0, GL_POSITION, lightP);

			// set the ambient light colour    
			GLfloat lightA[4] = { 0.0, 0.9, 0.9, 1 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightA);

			// set the specular light colour         
			GLfloat lightS[4] = { 0.9, 0.9, 0.9, 1.0 };
			glLightfv(GL_LIGHT0, GL_SPECULAR, lightS);

			// set the diffuse light colour
			GLfloat lightD[4] = { 0.9, 0.9, 0.9, 1.0 };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightD);

			glEnable(GL_LIGHTING);	
			glEnable(GL_LIGHT0);	

			/* Use depth buffering for hidden surface elimination. */
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);	//Activar Texturas

			glutDisplayFunc(display);
			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
			glutKeyboardFunc(keyboard);
			glutSpecialFunc(keyboardArrow);
			glutIdleFunc(animate);
			trees = new vector<string>();
			for (int i = 0; i <= DEPTH; i++){
				expand(num);
			}
			glutMainLoop();
			glutDestroyWindow(0);
		}
		
	system("pause");
	
	return 0;
}
