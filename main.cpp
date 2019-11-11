#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "LoadImage.h" //DeviL library
#include "Utils.h" //User Custom Library 1
//#include "stdafx.h"
#include "glm.h"
#include "Texture.h"
#include <GL/glui.h>
#include "tinyfiledialogs.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;
const int XSCREENPOSITION = (GetSystemMetrics(SM_CXSCREEN)-SCREEN_WIDTH)/2;
const int YSCREENPOSITION = (GetSystemMetrics(SM_CYSCREEN)-SCREEN_HEIGHT)/2;

int idWindow, idMenu, idSubMenu, opcionMenu = 0;

Position posicionCamara = {3,1.5f, 2};
Position posicionFlechaIzquierda[3] = { { -3.5f, 3, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y+0.5f, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y-0.5f, 0 } };
Position posicionFlechaDerecha[3] = { { -posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z }, { -posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z },  { -posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z } };

int idArchivoImagenActual = 0;

const int ID_BTN_ENVIAR_DATOS = 1;
const int ID_BTN_LIMPIAR_DATOS = 2;
GLUI_Panel *panelInputsIngresoDatos;
GLUI_Panel *panelButtonsIngresoDatos;
GLUI_EditText *txtNombres;
GLUI_EditText *txtApellidos;
GLUI_Spinner* spnEdad;
GLUI_Button *btnEnviarDatos;
GLUI_Button *btnLimpiarDatos;

InfoDatoUsuario infoDatoUsuario;

GLMmodel* punteroM1 = NULL; //Asombrado
GLMmodel* punteroM2 = NULL; //Enojado
GLMmodel* punteroM3 = NULL; //Sorprendido

Texture	treeTextureAr[5];

bool LoadTreeTextures()
{
    int i;
    if (LoadTGA(&treeTextureAr[0], (char*)"modelos/textura.tga")) //&& LoadTGA(&treeTextureAr[1], "modelos/textura.tga"))
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

void manejadorButtons(int idButton)
{
    switch(idButton)
    {
    case ID_BTN_ENVIAR_DATOS:
        if(strlen(txtNombres->get_text())>0 && strlen(txtApellidos->get_text())>0)
        {
            printf("Nombres: %s\n", infoDatoUsuario.nombres);
            printf("Apellidos: %s\n", infoDatoUsuario.apellidos);
            printf("Edad: %i\n\n", infoDatoUsuario.edad);
        }
        //tinyfd_messageBox("mensaje", "Hola Mundo", "ok", "info", 1);
        break;
    case ID_BTN_LIMPIAR_DATOS:
        txtNombres->set_text((char*)"");
        txtApellidos->set_text((char*)"");
        spnEdad->set_int_val(6);
        break;
    }
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

    if(opcionMenu==1)
    {
        opcionMenu = 0;
        idArchivoImagenActual = 0;
        glutPostRedisplay();
    }

    /*
    glPushMatrix();
    glTranslatef(-0.5f,-0.5f,1.6f);
    graficarAsombrado();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.5f, 0.9f);
    graficarEnojado();
    glPopMatrix();
    */

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
    glutInitWindowPosition(XSCREENPOSITION, YSCREENPOSITION-20);

    idWindow = glutCreateWindow("Proyecto Autismo");

    inicializar();

    //Realizar la inicialización de configuraciones para la librería DevIL
    if(!initGL() || !initDevIL())
    {
        printf( "No se puede inicializar la biblioteca de gráficos!\n" );
        return 1;
    }

    //punteroM1 = glmReadOBJ((char*)"modelos/asombrado.obj");
    //punteroM2 = glmReadOBJ((char*)"modelos/enojado.obj");
    punteroM3 = glmReadOBJ((char*)"modelos/sorprendido.obj");

    crearMenu();

    GLUI_Master.set_glutDisplayFunc(graficar);//glutDisplayFunc(graficar);
    GLUI_Master.set_glutReshapeFunc(redimensionar);
    GLUI_Master.set_glutMouseFunc(manejadorMouse);
    //GLUI_Master.set_glutKeyboardFunc(manejarTeclado);

    GLUI *gluiForm = GLUI_Master.create_glui_subwindow( idWindow, GLUI_SUBWINDOW_BOTTOM);

    //-->Controles GLUI
    panelInputsIngresoDatos = new GLUI_Panel(gluiForm, "Ingreso de datos");

    txtNombres = new GLUI_EditText(panelInputsIngresoDatos, "Nombres:", infoDatoUsuario.nombres);
    txtNombres->set_w(250);
    txtApellidos = new GLUI_EditText(panelInputsIngresoDatos, "Apellidos", infoDatoUsuario.apellidos);
    txtApellidos->set_w(250);
    spnEdad = new GLUI_Spinner(panelInputsIngresoDatos, "Edad:", &infoDatoUsuario.edad);
    spnEdad->set_int_limits(6,17);

    gluiForm->add_column_to_panel(panelInputsIngresoDatos, false);
    panelButtonsIngresoDatos = new GLUI_Panel(panelInputsIngresoDatos, "", false);
    btnEnviarDatos = new GLUI_Button(panelButtonsIngresoDatos, "Enviar", ID_BTN_ENVIAR_DATOS, manejadorButtons);
    btnLimpiarDatos = new GLUI_Button(panelButtonsIngresoDatos, "Limpiar", ID_BTN_LIMPIAR_DATOS, manejadorButtons);

    //Salir BTN_SALIR, (GLUI_Update_CB)exit

    gluiForm->set_main_gfx_window(idWindow);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);

    glutMainLoop();

    return 0;
}
