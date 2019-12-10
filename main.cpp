#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "LoadImage.h" //DeviL library
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"
#include "GluiConfig.h"
#include "irrklang/irrKlang.h"

irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();

//Para la iluminación
const GLfloat light_ambient[] = {0.6f, 0.6f, 0.6f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};
const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;
const int XSCREENPOSITION = (GetSystemMetrics(SM_CXSCREEN)-SCREEN_WIDTH)/2;
const int YSCREENPOSITION = (GetSystemMetrics(SM_CYSCREEN)-SCREEN_HEIGHT)/2;

int idWindow, idMenu, idSubMenu;

Position posicionCamara = {3,1.5f, 2};
Position posicionFlechaIzquierda[3] = { { -3.5f, 3, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y+0.5f, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y-0.5f, 0 } };
Position posicionFlechaDerecha[3] = { { -posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z }, { -posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z },  { -posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z } };
Position posicionModeloContento = { -1.69f, -1.7f, 1.69f };
Position posicionModeloEnojado = { posicionModeloContento.X+0.71f, posicionModeloContento.Y+0.15f, posicionModeloContento.Z-0.71f };
Position posicionModeloSorprendido = { posicionModeloEnojado.X+0.68f, posicionModeloEnojado.Y+0.18f, posicionModeloEnojado.Z-0.68f };
Position posicionModeloAsustado = { posicionModeloSorprendido.X+0.58f, posicionModeloSorprendido.Y+0.23f, posicionModeloSorprendido.Z-0.58f };
Position posicionModeloTriste = { posicionModeloAsustado.X+0.55f, posicionModeloAsustado.Y+0.09f, posicionModeloAsustado.Z-0.55f };
Position posicionModeloAburrido = { posicionModeloTriste.X+0.52f, posicionModeloTriste.Y+0.03f, posicionModeloTriste.Z-0.52f };
Position posicionModeloAvergonzado = { posicionModeloTriste.X+0.50f, posicionModeloTriste.Y+0.3f, posicionModeloTriste.Z-0.50f };
Position posicionModeloMiedoso = { posicionModeloEnojado.X+0.68f, posicionModeloEnojado.Y+0.52f, posicionModeloEnojado.Z-0.68f };

Scale escalaModeloContento = { 0.38f, 0.51f, 0.38f };
Scale escalaModeloEnojado = { 0.4f, 0.46f, 0.4f };
Scale escalaModeloSorprendido = { 0.4f, 0.46f, 0.4f };
Scale escalaModeloAsustado = { 0.34f, 0.39f, 0.34f };
Scale escalaModeloTriste = { 0.32f, 0.4f, 0.32f };
Scale escalaModeloAburrido = { 0.29f, 0.392f, 0.29f };
Scale escalaModeloAvergonzado = { 0.265f, 0.36f, 0.265f };
Scale escalaModeloMiedoso = { 0.34f, 0.41f, 0.34f };

//Modelos Aburrido
GLMmodel *modeloCabezaAburrido = NULL;
GLMmodel *modeloBocaAburrido = NULL;

//Modelos Asustado
GLMmodel *modeloCabezaAsustado = NULL;
GLMmodel *modeloCejaDerechaAsustado = NULL;
GLMmodel *modeloCejaIzquierdaAsustado = NULL;
GLMmodel *modeloBocaAsustado = NULL;
GLMmodel *ModeloNarizAsustado = NULL;

//Modelos Contento
GLMmodel *modeloCabezaContento = NULL;
GLMmodel *modeloCejaDerechaContento = NULL;
GLMmodel *modeloCejaIzquierdaContento = NULL;
GLMmodel *modeloBocaContento = NULL;
GLMmodel *modeloNarizContento = NULL;
GLMmodel *modeloOjoIzquierdoContento = NULL;
GLMmodel *modeloOjoDerechoContento = NULL;

//Modelos Enojado
GLMmodel *modeloCabezaEnojado = NULL;
GLMmodel *modeloBocaEnojado = NULL;
GLMmodel *modeloNarizEnojado = NULL;
GLMmodel *modeloOjoDerechoEnojado = NULL;
GLMmodel *modeloOjoIzquierdoEnojado = NULL;

//Modelos Sorprendido
GLMmodel *modeloCabezaSorprendido = NULL;
GLMmodel *modeloCejaDerechaSorprendido = NULL;
GLMmodel *modeloCejaIzquierdaSorprendido = NULL;
GLMmodel *modeloBocaSorprendido = NULL;
GLMmodel *modeloNarizSorprendido = NULL;
GLMmodel *modeloOjoIzquierdoSorprendido = NULL;
GLMmodel *modeloOjoDerechoSorprendido = NULL;

//Modelos Triste
GLMmodel *modeloCabezaTriste = NULL;
GLMmodel *modeloCejaDerechaTriste = NULL;
GLMmodel *modeloCejaIzquierdaTriste = NULL;
GLMmodel *modeloBocaTriste = NULL;
GLMmodel *modeloNarizTriste = NULL;
GLMmodel *modeloOjoIzquierdoTriste = NULL;

//Modelos Avergonzado
GLMmodel *modeloCabezaAvergonzado = NULL;
GLMmodel *modeloCejaDerechaAvergonzado = NULL;
GLMmodel *modeloCejaIzquierdaAvergonzado = NULL;
GLMmodel *modeloBocaAvergonzado = NULL;
GLMmodel *modeloNarizAvergonzado = NULL;
GLMmodel *modeloOjoIzquierdoAvergonzado = NULL;
GLMmodel *modeloOjoDerechoAvergonzado = NULL;

//Modelos Miedoso
GLMmodel *modeloCabezaMiedoso = NULL;
GLMmodel *modeloCejaDerechaMiedoso = NULL;
GLMmodel *modeloCejaIzquierdaMiedoso = NULL;
GLMmodel *modeloManoMiedoso = NULL;
GLMmodel *modeloOjoIzquierdoMiedoso = NULL;
GLMmodel *modeloOjoDerechoMiedoso = NULL;

Texture	treeTextureAr[8];

bool LoadTreeTextures()
{
    int i;
    if (LoadTGA(&treeTextureAr[0], (char*)"modelos/ABURRIDO/aburrido.tga") && LoadTGA(&treeTextureAr[1], (char*)"modelos/ASUSTADO/asustado.tga") && LoadTGA(&treeTextureAr[2], (char*)"modelos/CONTENTO/contento.tga") && LoadTGA(&treeTextureAr[3], (char*)"modelos/ENFADADO/enfadado.tga") && LoadTGA(&treeTextureAr[4], (char*)"modelos/SORPRENDIDO/sorprendido.tga") && LoadTGA(&treeTextureAr[5], (char*)"modelos/TRISTE/triste.tga") && LoadTGA(&treeTextureAr[6], (char*)"modelos/AVERGONZADO/avergonzado.tga") && LoadTGA(&treeTextureAr[7], (char*)"modelos/MIEDOSO/miedoso.tga"))
    {
        for (i = 0; i<8; i++)
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

void myGlutIdle(void)
{
    if ( glutGetWindow() != idWindow )
    {
        glutSetWindow(idWindow);
    }
    glutPostRedisplay();
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
        opcionMenu = num;
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
    FloatColorRGB colorClear = { 30, 30, 30 };
    glClearColor(colorClear.getRED(), colorClear.getGREEN(), colorClear.getBLUE(), 1);
    LoadTreeTextures();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void redimensionar(int w, int h)
{
    glutReshapeWindow( SCREEN_WIDTH, SCREEN_HEIGHT);
    int  tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th ); //glViewport(0, 0, (GLsizei)w, (GLsizei)h);
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
    //Inicio de dibujo de figura 2D según en el nivel.
    switch(nivel)
    {
    case 1:
        if(loadMedia( "imagenes/emociones/" + archivosImagenesEmociones[idArchivoImagenActual].nombreArchivo ))
        {
            renderCenterInX(SCREEN_WIDTH, SCREEN_HEIGHT, 20);
        }
        break;
    case 2:
        if(loadMedia( "imagenes/situaciones/" + archivosImagenesSituaciones[idArchivoImagenActual].nombreArchivo ))
        {
            renderCenterInX(SCREEN_WIDTH, SCREEN_HEIGHT, 20);
        }
        break;
    default:
        printf("No se puede cargar las imagenes porque no se reconoce el nivel seleccionado!");
        break;
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

void graficarTexto2D(float x, float y, void *fuente, char *cadena)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1 );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //Inicio de dibujo de figura 2D
    char *c;
    glRasterPos3f(x, y, 0);
    for(c=cadena; *c !='\0'; c++)
    {
        glutBitmapCharacter(fuente, *c);
    }
    //Fin de dibujo de figura 2D
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void graficarInfoUsuario()
{
    char numero[10], resultado[200] = "";
    strcat(resultado, "Nombres: ");
    strcat(resultado, datosUsuario.nombres);
    graficarTexto2D(10,50,GLUT_BITMAP_HELVETICA_12, resultado);
    strcpy(resultado, "");
    strcat(resultado, "Apellidos: ");
    strcat(resultado, datosUsuario.apellidos);
    graficarTexto2D(10,75,GLUT_BITMAP_HELVETICA_12, resultado);
    strcpy(resultado, "");
    strcat(resultado, "Edad: ");
    strcat(resultado, itoa(datosUsuario.edad, numero, 10));
    strcat(resultado, " anios");
    graficarTexto2D(10,102,GLUT_BITMAP_HELVETICA_12, resultado);
    strcpy(resultado, "");
    strcat(resultado, "Aciertos: ");
    strcat(resultado, itoa(datosUsuario.aciertos, numero, 10));
    graficarTexto2D(10,128,GLUT_BITMAP_HELVETICA_12,resultado);
    strcpy(resultado, "");
    strcat(resultado, "Desaciertos: ");
    strcat(resultado, itoa(datosUsuario.desaciertos, numero, 10));
    graficarTexto2D(10,154,GLUT_BITMAP_HELVETICA_12,  resultado);
    strcpy(resultado, "");
    strcat(resultado, "Id imagen: ");
    strcat(resultado, itoa(idArchivoImagenActual+1, numero, 10));
    graficarTexto2D(10,180,GLUT_BITMAP_HELVETICA_12,  resultado);
    strcpy(resultado, "");
    strcat(resultado, "Nivel: ");
    strcat(resultado, itoa(nivel, numero, 10));
    graficarTexto2D(10,206,GLUT_BITMAP_HELVETICA_12,  resultado);
}

void rotarT1(int i)
{
    if(rotT1<180 && xd1 == 0)
    {
        rotT1 = rotT1 - 6;
    }
    else
    {
        xd1 = 1;
    }

    if (rotT1>-180 && xd1 ==1)
    {
        rotT1 = rotT1 + 6;
    }
    else
    {
        xd1 = 0;
    }
    glutPostRedisplay();
    GLUI_Master.set_glutTimerFunc(500,rotarT1,1);
}

void rotarT2(int i)
{
    if(rotT1<180 && xd1 == 0)
    {
        rotT2 = rotT2 + 6;
    }
    else
    {
        xd1 = 1;
    }

    if (rotT2>-180 && xd1 ==1)
    {
        rotT2 = rotT2 - 6;
    }
    else
    {
        xd1 = 0;
    }
    glutPostRedisplay();
    GLUI_Master.set_glutTimerFunc(500,rotarT2,2);
}

void rotarT3(int i)
{
    if(rotT3<15 && xd1 == 0)
    {
        rotT3 = rotT3 + 6;
    }
    else
    {
        xd1 = 1;
    }

    if (rotT3>-15 && xd1 ==1)
    {
        rotT3 = rotT3 - 6;
    }
    else
    {
        xd1 = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(500,rotarT3,3);
}

void controlarAnimacion(int i)
{
    rotT1 = 0;
    rotT2 = 0;
    rotT3 = 0;
    xd1 = 0;
    glutPostRedisplay();
    glutTimerFunc(20000,controlarAnimacion,4);
}

void graficarContento()
{
    glPushMatrix();
    glTranslatef(posicionModeloContento.X, posicionModeloContento.Y, posicionModeloContento.Z);
    glRotatef(75, 0, 1, 0);
    glScalef(escalaModeloContento.X, escalaModeloContento.Y, escalaModeloContento.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloCabezaContento, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloCejaDerechaContento, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloOjoDerechoContento, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloCejaIzquierdaContento, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloOjoIzquierdoContento, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,1,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloBocaContento, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloNarizContento, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarEnojado()
{
    glPushMatrix();
    glTranslatef(posicionModeloEnojado.X, posicionModeloEnojado.Y, posicionModeloEnojado.Z);
    glRotatef(70, 0, 1, 0);
    glScalef(escalaModeloEnojado.X, escalaModeloEnojado.Y, escalaModeloEnojado.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloCabezaEnojado, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloBocaEnojado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloNarizEnojado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloOjoDerechoEnojado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloOjoIzquierdoEnojado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarSorprendido()
{
    glPushMatrix();
    glTranslatef(posicionModeloSorprendido.X, posicionModeloSorprendido.Y, posicionModeloSorprendido.Z);
    glRotatef(63, 0, 1, 0);
    glScalef(escalaModeloSorprendido.X, escalaModeloSorprendido.Y, escalaModeloSorprendido.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloCabezaSorprendido, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloCejaDerechaSorprendido, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloOjoDerechoSorprendido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloCejaIzquierdaSorprendido, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloOjoIzquierdoSorprendido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloBocaSorprendido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloNarizSorprendido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarAsustado()
{
    glPushMatrix();
    glTranslatef(posicionModeloAsustado.X, posicionModeloAsustado.Y, posicionModeloAsustado.Z);
    glRotatef(-15, 0, 1, 0);
    glScalef(escalaModeloAsustado.X, escalaModeloAsustado.Y, escalaModeloAsustado.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(modeloCabezaAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(modeloCejaIzquierdaAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(modeloCejaDerechaAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(modeloBocaAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(ModeloNarizAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();
}

void graficarTriste()
{
    glPushMatrix();
    glTranslatef(posicionModeloTriste.X, posicionModeloTriste.Y, posicionModeloTriste.Z);
    glRotatef(40, 0, 1, 0);
    glScalef(escalaModeloTriste.X, escalaModeloTriste.Y, escalaModeloTriste.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloCabezaTriste, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloCejaDerechaTriste, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloCejaIzquierdaTriste, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloOjoIzquierdoTriste, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloBocaTriste, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloNarizTriste, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarAburrido()
{
    glPushMatrix();
    glTranslatef(posicionModeloAburrido.X, posicionModeloAburrido.Y, posicionModeloAburrido.Z);
    glRotatef(35, 0, 1, 0);
    glScalef(escalaModeloAburrido.X, escalaModeloAburrido.Y, escalaModeloAburrido.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(modeloCabezaAburrido, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(modeloBocaAburrido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarAvergonzado()
{
    glPushMatrix();
    glTranslatef(posicionModeloAvergonzado.X, posicionModeloAvergonzado.Y, posicionModeloAvergonzado.Z);
    glRotatef(35, 0, 1, 0);
    glScalef(escalaModeloAvergonzado.X, escalaModeloAvergonzado.Y, escalaModeloAvergonzado.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloCabezaAvergonzado, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloCejaIzquierdaAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPushMatrix();
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloOjoIzquierdoAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloCejaDerechaAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPushMatrix();
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloOjoDerechoAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glRotatef(0, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloBocaAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
    glmDraw(modeloNarizAvergonzado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficarMiedoso()
{
    glPushMatrix();
    glTranslatef(posicionModeloMiedoso.X, posicionModeloMiedoso.Y, posicionModeloMiedoso.Z);
    glRotatef(63, 0, 1, 0);
    glScalef(escalaModeloMiedoso.X, escalaModeloMiedoso.Y, escalaModeloMiedoso.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloCabezaMiedoso, GLM_SMOOTH | GLM_TEXTURE);

    glPushMatrix();
    glRotatef(rotT2,0,0,0);
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloCejaIzquierdaMiedoso, GLM_SMOOTH | GLM_TEXTURE);
    glPushMatrix();
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloOjoIzquierdoMiedoso, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT1,0,0,0);
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloCejaDerechaMiedoso, GLM_SMOOTH | GLM_TEXTURE);
    glPushMatrix();
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloOjoDerechoMiedoso, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotT3,0,0,0);
    glRotatef(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
    glmDraw(modeloManoMiedoso, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPopMatrix();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicionCamara.X, posicionCamara.Y, posicionCamara.Z, 0, 0, 0, 0, 1, 0);

    if(opcionMenu==1)
    {
        reiniciarEvent(1);
        glutPostRedisplay();
    }

    if(empezar && datosUsuario.resultados.size()==(unsigned int)totalImagenesActual)
    {
        mostrarResultadosEvent();
    }

    if(empezar)
    {
        //Objetos 3D
        switch(nivel)
        {
        case 1:
            graficarContento();
            graficarEnojado();
            graficarSorprendido();
            graficarAsustado();
            graficarTriste();
            graficarAburrido();
            break;
        case 2:
            graficarContento();
            graficarEnojado();
            graficarMiedoso();
            graficarAsustado();
            graficarTriste();
            graficarAvergonzado();
            break;
        default:
            printf("No se puede cargar los objetos 3D porque no se reconoce el nivel seleccionado!");
            break;
        }

        //Objetos 2D
        graficarImagen2D();
        graficarFlechaIzquierda2D();
        graficarFlechaDerecha2D();
        graficarInfoUsuario();

        if(!datosUsuario.resultadoRegistrado(idArchivoImagenActual))
        {
            switch(nivel)
            {
            case 1:
                graficarTexto2D((SCREEN_WIDTH/2)-85,(SCREEN_HEIGHT/2),GLUT_BITMAP_TIMES_ROMAN_24,(char*)"Como se siente?");
                graficarTexto2D(50,(SCREEN_HEIGHT/2)+234,GLUT_BITMAP_8_BY_13,(char*)"<Contento>         <Enojado>         <Sorprendido>         <Asustado>         <Triste>         <Aburrido>");
                break;
            case 2:
                graficarTexto2D((SCREEN_WIDTH/2)-85,(SCREEN_HEIGHT/2),GLUT_BITMAP_TIMES_ROMAN_24,(char*)"Como se siente?");
                graficarTexto2D(50,(SCREEN_HEIGHT/2)+234,GLUT_BITMAP_8_BY_13,(char*)"<Contento>           <Enojado>                            <Asustado>          <Triste>         <Avergonzado>");
                graficarTexto2D(363,(SCREEN_HEIGHT/2)+256,GLUT_BITMAP_8_BY_13,(char*)"<Miedoso>");
                break;
            default:
                printf("No se puede cargar los textos 2D porque no se reconoce el nivel seleccionado!");
                break;
            }
        }
        else
        {
            graficarTexto2D((SCREEN_WIDTH/2)-138,(SCREEN_HEIGHT/2)+275,GLUT_BITMAP_8_BY_13,(char*)"Respuesta registrada correctamente.");
        }
    }
    else
    {
        switch(nivel)
        {
        case 1:
            graficarTexto2D((SCREEN_WIDTH/2)-252,(SCREEN_HEIGHT/2),GLUT_BITMAP_TIMES_ROMAN_24,(char*)"Presiona la opcion 'Iniciar' para comenzar el nivel 1");
            break;
        case 2:
            graficarTexto2D((SCREEN_WIDTH/2)-252,(SCREEN_HEIGHT/2),GLUT_BITMAP_TIMES_ROMAN_24,(char*)"Presiona la opcion 'Iniciar' para comenzar el nivel 2");
            break;
        default:
            printf("No se puede mostrar el mensaje de inicio porque no se reconoce el nivel seleccionado!");
            break;
        }
    }
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
                gLoadedTexture.freeTexture();
                idArchivoImagenActual--;
                glutPostRedisplay();
            }
        }

        //Clic en la flecha derecha
        if(XMouse<=1.05f && XMouse>=0.9f && YMouse<=1.05f && YMouse>=0.75f)
        {
            if(idArchivoImagenActual<totalImagenesActual-1)
            {
                gLoadedTexture.freeTexture();
                idArchivoImagenActual++;
                glutPostRedisplay();
            }
        }

        //Clic en cualquiera de las caras 3D
        if(empezar && idArchivoImagenActual>=0 && idArchivoImagenActual<totalImagenesActual)
        {
            if(!datosUsuario.resultadoRegistrado(idArchivoImagenActual))
            {
                InfoResultado resultado;
                resultado.idImagen = idArchivoImagenActual;
                resultado.nombreEmocion = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion;
                if(XMouse>=-1.47f && XMouse<=-1.0f && YMouse<=0.12f && YMouse>=-0.57f)  //Contento
                {
                    resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Contento")==0;
                }
                else if(XMouse>=-0.97f && XMouse<=-0.50f && YMouse<=0.12f && YMouse>=-0.57f)   //Enojado
                {
                    resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Enojado")==0;
                }
                else if(XMouse>=-0.47f && XMouse<=-0.003f && YMouse<=0.12f && YMouse>=-0.57f)   //Sorprendido
                {
                    switch(nivel)
                    {
                    case 1:
                        resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Sorprendido")==0;
                        break;
                    case 2:
                        resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Miedoso")==0;
                        break;
                    }
                }
                else if(XMouse>=0.02f && XMouse<=0.49f && YMouse<=0.12f && YMouse>=-0.57f)   //Asustado
                {
                    resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Asustado")==0;
                }
                else if(XMouse>=0.52f && XMouse<=0.97f && YMouse<=0.12f && YMouse>=-0.57f)   //Triste
                {
                    resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Triste")==0;
                }
                else if(XMouse>=1.0f && XMouse<=1.45f && YMouse<=0.12f && YMouse>=-0.57f)   //Aburrido o Avergonzado
                {
                    switch(nivel)
                    {
                    case 1:
                        resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Aburrido")==0;
                        break;
                    case 2:
                        resultado.acertado = archivosImagenesEmociones[idArchivoImagenActual].nombreEmocion.compare("Avergonzado")==0;
                        break;
                    }
                }
                else
                {
                    return;
                }
                if(resultado.acertado)
                {
                    datosUsuario.aciertos++;
                    SoundEngine->play2D((char*)"audio/acierto.wav", GL_FALSE);
                }
                else
                {
                    datosUsuario.desaciertos++;
                    SoundEngine->play2D((char*)"audio/desacierto.wav", GL_FALSE);
                }
                datosUsuario.resultados.push_back(resultado);
                glutPostRedisplay();
            }
        }
    }
}


void manejarTeclado(unsigned char key, int x, int y)
{
    switch(key)
    {
    case '1':
        gLoadedTexture.freeTexture();
        reiniciarEvent(1);
        break;
    case '2':
        gLoadedTexture.freeTexture();
        reiniciarEvent(2);
        break;
    default :
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion( 2, 1 );

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(XSCREENPOSITION, YSCREENPOSITION-20);
    idWindow = glutCreateWindow("COGRAVI - Proyecto Autismo");

    inicializar();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //Realizar la inicialización de configuraciones para la librería DevIL
    if(!initGL() || !initDevIL())
    {
        printf( "No se puede inicializar la biblioteca de graficos!\n" );
        return 1;
    }
    else
    {
        printf( "Biblioteca de graficos cargado correctamente!\n" );
    }

    if(!SoundEngine)
    {
        printf( "No se puede inicializar la biblioteca de sonido!\n" );
        return 1;
    }
    else
    {
        printf( "Biblioteca de sonido cargado correctamente!\n" );
    }

    //Modelos Aburrido
    modeloCabezaAburrido = glmReadOBJ((char*)"modelos/ABURRIDO/cabezabored2.obj");
    modeloBocaAburrido = glmReadOBJ((char*)"modelos/ABURRIDO/bocabored.obj");

    //Modelos Asustado
    modeloCabezaAsustado = glmReadOBJ((char*)"modelos/ASUSTADO/cabezascared.obj");
    modeloCejaIzquierdaAsustado = glmReadOBJ((char*)"modelos/ASUSTADO/cejaderechascared.obj");
    modeloCejaDerechaAsustado = glmReadOBJ((char*)"modelos/ASUSTADO/cejaizquierdascared.obj");
    modeloBocaAsustado = glmReadOBJ((char*)"modelos/ASUSTADO/bocascared.obj");
    ModeloNarizAsustado = glmReadOBJ((char*)"modelos/ASUSTADO/narizscared.obj");

    //Modelos Contento
    modeloCabezaContento = glmReadOBJ((char*)"modelos/CONTENTO/cabezahappy.obj");
    modeloCejaDerechaContento = glmReadOBJ((char*)"modelos/CONTENTO/cejaderechahappy.obj");
    modeloCejaIzquierdaContento = glmReadOBJ((char*)"modelos/CONTENTO/cejaizquierdahappy.obj");
    modeloBocaContento = glmReadOBJ((char*)"modelos/CONTENTO/bocahappy.obj");
    modeloNarizContento = glmReadOBJ((char*)"modelos/CONTENTO/narizhappy.obj");
    modeloOjoIzquierdoContento = glmReadOBJ((char*)"modelos/CONTENTO/ojoizquierdohappy.obj");
    modeloOjoDerechoContento = glmReadOBJ((char*)"modelos/CONTENTO/ojoderechohappy.obj");

    //Modelos Enojado
    modeloCabezaEnojado = glmReadOBJ((char*)"modelos/ENFADADO/cabezaangry.obj");
    modeloBocaEnojado = glmReadOBJ((char*)"modelos/ENFADADO/bocaangry.obj");
    modeloNarizEnojado = glmReadOBJ((char*)"modelos/ENFADADO/narizangry.obj");
    modeloOjoDerechoEnojado = glmReadOBJ((char*)"modelos/ENFADADO/ojoderechoangry.obj");
    modeloOjoIzquierdoEnojado = glmReadOBJ((char*)"modelos/ENFADADO/ojoizquierdoangry.obj");

    //Modelos Sorprendido
    modeloCabezaSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/cabezasurprise.obj");
    modeloCejaDerechaSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/cejaderechasurprise.obj");
    modeloCejaIzquierdaSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/cejaizquierdasurprise.obj");
    modeloBocaSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/bocasurprise.obj");
    modeloNarizSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/narizsurprise.obj");
    modeloOjoIzquierdoSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/ojoizquierdosurprise.obj");
    modeloOjoDerechoSorprendido = glmReadOBJ((char*)"modelos/SORPRENDIDO/ojoderechosurprise.obj");

    //Modelos Triste
    modeloCabezaTriste = glmReadOBJ((char*)"modelos/TRISTE/cabezasad.obj");
    modeloCejaDerechaTriste = glmReadOBJ((char*)"modelos/TRISTE/cejaderechasad.obj");
    modeloCejaIzquierdaTriste = glmReadOBJ((char*)"modelos/TRISTE/cejaizquierdasad.obj");
    modeloBocaTriste = glmReadOBJ((char*)"modelos/TRISTE/bocasad.obj");
    modeloNarizTriste = glmReadOBJ((char*)"modelos/TRISTE/narizsad.obj");
    modeloOjoIzquierdoTriste = glmReadOBJ((char*)"modelos/TRISTE/ojoizquierdosad.obj");

    //Modelos Avergonzado
    modeloCabezaAvergonzado = glmReadOBJ("modelos/AVERGONZADO/cabezaashamed.obj");
    modeloCejaDerechaAvergonzado = glmReadOBJ("modelos/AVERGONZADO/cejaderechaashamed.obj");
    modeloCejaIzquierdaAvergonzado = glmReadOBJ("modelos/AVERGONZADO/cejaizquierdaashamed.obj");
    modeloBocaAvergonzado = glmReadOBJ("modelos/AVERGONZADO/bocaashamed.obj");
    modeloNarizAvergonzado = glmReadOBJ("modelos/AVERGONZADO/narizashamed.obj");
    modeloOjoIzquierdoAvergonzado = glmReadOBJ("modelos/AVERGONZADO/ojoizquierdoashamed.obj");
    modeloOjoDerechoAvergonzado = glmReadOBJ("modelos/AVERGONZADO/ojoderechoashamed.obj");

    //Modelos Miedoso
    modeloCabezaMiedoso = glmReadOBJ("modelos/MIEDOSO/cabezafearful.obj");
    modeloCejaDerechaMiedoso = glmReadOBJ("modelos/MIEDOSO/cejaderechafearful.obj");
    modeloCejaIzquierdaMiedoso = glmReadOBJ("modelos/MIEDOSO/cejaizquierdafearful.obj");
    modeloManoMiedoso = glmReadOBJ("modelos/MIEDOSO/manofearful.obj");
    modeloOjoIzquierdoMiedoso = glmReadOBJ("modelos/MIEDOSO/ojoizquierdofearful.obj");
    modeloOjoDerechoMiedoso = glmReadOBJ("modelos/MIEDOSO/ojoderechofearful.obj");

    GLUI_Master.set_glutTimerFunc(500,rotarT1,1);
    GLUI_Master.set_glutTimerFunc(500,rotarT2,2);
    GLUI_Master.set_glutTimerFunc(500,rotarT3,3);
    GLUI_Master.set_glutTimerFunc(20000,controlarAnimacion,4);

    crearMenu();

    GLUI_Master.set_glutDisplayFunc(graficar);
    GLUI_Master.set_glutReshapeFunc(redimensionar);
    GLUI_Master.set_glutMouseFunc(manejadorMouse);
    GLUI_Master.set_glutKeyboardFunc(manejarTeclado);

    GLUI *gluiForm = GLUI_Master.create_glui_subwindow( idWindow, GLUI_SUBWINDOW_BOTTOM);

    gluiControls(gluiForm);//Controles GLUI

    gluiForm->set_main_gfx_window(idWindow);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);

    glutMainLoop();

    return 0;
}
