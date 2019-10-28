#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include "LoadImage.h" //DeviL library
#include "Utils.h" //User Custom Data
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

Position posicionCamara = {3,1.5f, 2};
Position posicionFlechaIzquierda[3] = { { -3.5f, 3, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y+0.5f, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y-0.5f, 0 } };
Position posicionFlechaDerecha[3] = { { -posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z }, { -posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z },  { -posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z } };

int idArchivoImagenActual = 0;
int idWindow, idMenu, idSubMenu, opcion = 0;

GLMmodel* punteroM1 = NULL; //Asombrado
GLMmodel* punteroM2 = NULL; //Enojado
GLMmodel* punteroM3 = NULL; //Sorprendido

Texture	treeTextureAr[5];

bool LoadTreeTextures()
{
    int i;
    if (LoadTGA(&treeTextureAr[0], "modelos/textura.tga")) //&& LoadTGA(&treeTextureAr[1], "modelos/textura.tga"))
    {
        for (i = 0; i<1; i++)
        {
            glGenTextures(1, &treeTextureAr[i].texID);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[i].texID);
            glTexImage2D(GL_TEXTURE_2D, 0, treeTextureAr[i].bpp / 8, treeTextureAr[i].width, treeTextureAr[i].height, 0, treeTextureAr[i].type, GL_UNSIGNED_BYTE, treeTextureAr[i].imageData);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glEnable(GL_TEXTURE_2D);
            if (treeTextureAr[i].imageData)
            {
                free(treeTextureAr[i].imageData);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}


void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(idWindow);
        exit(0);
    }
    else
    {
        opcion = num;
    }
    glutPostRedisplay();
}

void crearMenu(void)
{
    idMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Reiniciar", 1);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void inicializar(void)
{
    FloatColorRGB colorClear = { 20, 20, 20 };
    glClearColor(colorClear.getRED(), colorClear.getGREEN(), colorClear.getBLUE(), 1);
    LoadTreeTextures();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void redimensionar(int w, int h)
{
    glutReshapeWindow( SCREEN_WIDTH, SCREEN_HEIGHT);
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / (float)h, 1, 500);
}

void graficarImagen2D(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1 );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //Inicio de dibujo de figura 2D
    if(loadMedia( "imagenes/emociones/" + archivosImagenes[idArchivoImagenActual].nombreArchivo ))
    {
        renderCenterInX(SCREEN_WIDTH, SCREEN_HEIGHT, 20);
    }
    //Fin de dibujo de figura 2D
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void graficarFlechaIzquierda2D(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 1, -1 );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //Inicio de dibujo de figura 2D
    glBegin(GL_TRIANGLES);
    glVertex3f(posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z);
    glVertex3f(posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z);
    glVertex3f(posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z);
    glEnd();
    //Fin de dibujo de figura 2D
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void graficarFlechaDerecha2D(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 1, -1 );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //Inicio de dibujo de figura 2D
    glBegin(GL_TRIANGLES);
    glVertex3f(posicionFlechaDerecha[0].X, posicionFlechaDerecha[0].Y, posicionFlechaDerecha[0].Z);
    glVertex3f(posicionFlechaDerecha[1].X, posicionFlechaDerecha[1].Y, posicionFlechaDerecha[1].Z);
    glVertex3f(posicionFlechaDerecha[2].X, posicionFlechaDerecha[2].Y, posicionFlechaDerecha[2].Z);
    glEnd();
    //Fin de dibujo de figura 2D
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void graficarAsombrado()
{
    glRotatef(-16, 0, 0, 1);
    glRotatef(70, 0, 1, 0);
    glRotatef(-30, 1, 0, 0);
    glScalef(0.15,0.15,0.15);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);
}

void graficarEnojado()
{
    glRotatef(-16, 0, 0, 1);
    glRotatef(70, 0, 1, 0);
    glRotatef(-30, 1, 0, 0);
    glScalef(0.15,0.15,0.15);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(punteroM2, GLM_SMOOTH | GLM_TEXTURE);
}

void graficarSorprendido()
{
    glRotatef(-1, 0, 0, 1);
    glRotatef(54, 0, 1, 0);
    glRotatef(-18, 1, 0, 0);
    glScalef(0.3,0.35,0.3);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(punteroM3, GLM_SMOOTH | GLM_TEXTURE);
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicionCamara.X, posicionCamara.Y, posicionCamara.Z, 0, 0, 0, 0, 1, 0);

    if(opcion==1)
    {
        opcion = 0;
        idArchivoImagenActual = 0;
        glutPostRedisplay();
    }

    glPushMatrix();
    glTranslatef(-0.5f,-0.5f,1.6f);
    graficarAsombrado();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.5f, 0.9f);
    graficarEnojado();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f, 0, 0.6f);
    graficarSorprendido();
    glPopMatrix();

    graficarImagen2D();
    graficarFlechaIzquierda2D();
    graficarFlechaDerecha2D();

    glutSwapBuffers();
}

void manejadorMouse(int button, int state, int x, int y)
{
    float XMouse = (x - SCREEN_WIDTH/2) * 3.0 / SCREEN_WIDTH;
    float YMouse = (SCREEN_HEIGHT/2 - y) * 3.0 / SCREEN_HEIGHT;
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //Clic en la flecha izquierda
        if(XMouse>=-1.05f && XMouse<=-0.9f && YMouse<=1.05f && YMouse>=0.75f)
        {
            if(idArchivoImagenActual>0)
            {
                idArchivoImagenActual--;
                glutPostRedisplay();
            }
        }
        //Clic en la flecha derecha
        if(XMouse<=1.05f && XMouse>=0.9f && YMouse<=1.05f && YMouse>=0.75f)
        {
            if(idArchivoImagenActual<nroArchivoImagenes-1)
            {
                idArchivoImagenActual++;
                glutPostRedisplay();
            }
        }
    }
}

void manejarTeclado(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'c':
    {
        break;
    }
    }
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion( 2, 1 );

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 10);
    idWindow = glutCreateWindow("Proyecto Autismo");

    inicializar();

    //Realizar la inicialización de configuraciones para la librería DevIL
    if(!initGL() || !initDevIL())
    {
        printf( "No se puede inicializar la biblioteca de gráficos!\n" );
        return 1;
    }

    punteroM1 = glmReadOBJ("modelos/asombrado.obj");
    punteroM2 = glmReadOBJ("modelos/enojado.obj");
    punteroM3 = glmReadOBJ("modelos/sorprendido.obj");

    crearMenu();
    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);
    glutMouseFunc(manejadorMouse);
    //glutKeyboardFunc(manejarTeclado);
    glutMainLoop();

    return 0;
}
