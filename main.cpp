#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "LoadImage.h" //DeviL library
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"
#include "GluiConfig.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;
const int XSCREENPOSITION = (GetSystemMetrics(SM_CXSCREEN)-SCREEN_WIDTH)/2;
const int YSCREENPOSITION = (GetSystemMetrics(SM_CYSCREEN)-SCREEN_HEIGHT)/2;

int idWindow, idMenu, idSubMenu, opcionMenu = 0;

Position posicionCamara = {3,1.5f, 2};
Position posicionFlechaIzquierda[3] = { { -3.5f, 3, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y+0.5f, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y-0.5f, 0 } };
Position posicionFlechaDerecha[3] = { { -posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z }, { -posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z },  { -posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z } };
Position posicionModeloContento = { -1.55f, -1.0f, 1.55f };
Position posicionModeloEnojado = { posicionModeloContento.X+0.55f, posicionModeloContento.Y+0.11f, posicionModeloContento.Z-0.55f };
Position posicionModeloSorprendido = { posicionModeloEnojado.X+0.55f, posicionModeloEnojado.Y+0.11f, posicionModeloEnojado.Z-0.55f };
Position posicionModeloAsustado = { posicionModeloSorprendido.X+0.55f, posicionModeloSorprendido.Y+0.11f, posicionModeloSorprendido.Z-0.55f };
Position posicionModeloTriste = { posicionModeloAsustado.X+0.55f, posicionModeloAsustado.Y+0.11f, posicionModeloAsustado.Z-0.55f };
Position posicionModeloAburrido = { posicionModeloTriste.X+0.55f, posicionModeloTriste.Y+0.11f, posicionModeloTriste.Z-0.55f };

Scale escalaObjetos = { 0.25f, 0.3f, 0.25f };

GLMmodel *modeloContento = NULL, *modeloEnojado = NULL, *modeloSorprendido = NULL, *modeloAsustado = NULL, *modeloTriste = NULL, *modeloAburrido = NULL;

Texture	treeTextureAr[6];

bool LoadTreeTextures()
{
    int i;
    if (LoadTGA(&treeTextureAr[0], (char*)"modelos/aburrido.tga") && LoadTGA(&treeTextureAr[1], (char*)"modelos/asustado.tga") && LoadTGA(&treeTextureAr[2], (char*)"modelos/contento.tga") && LoadTGA(&treeTextureAr[3], (char*)"modelos/enfadado.tga") && LoadTGA(&treeTextureAr[4], (char*)"modelos/sorprendido.tga") && LoadTGA(&treeTextureAr[5], (char*)"modelos/triste.tga"))
    {
        for (i = 0; i<6; i++)
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
}
//&& LoadTGA(&treeTextureAr[2], (char*)"modelos/contento.tga") && LoadTGA(&treeTextureAr[3], (char*)"modelos/enfadado.tga") && LoadTGA(&treeTextureAr[4], (char*)"modelos/sorprendido.tga") && LoadTGA(&treeTextureAr[5], (char*)"modelos/triste.tga"))
void graficarContento()
{
    glPushMatrix();
    glTranslatef(posicionModeloContento.X, posicionModeloContento.Y, posicionModeloContento.Z);
    glRotatef(65, 0, 1, 0);
    glScalef(escalaObjetos.X, escalaObjetos.Y, escalaObjetos.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
    glmDraw(modeloContento, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
}

void graficarEnojado()
{
    glPushMatrix();
    glTranslatef(posicionModeloEnojado.X, posicionModeloEnojado.Y, posicionModeloEnojado.Z);
    glRotatef(65, 0, 1, 0);
    glScalef(escalaObjetos.X, escalaObjetos.Y, escalaObjetos.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
    glmDraw(modeloEnojado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
}

void graficarSorprendido()
{
    glPushMatrix();
    glTranslatef(posicionModeloSorprendido.X, posicionModeloSorprendido.Y, posicionModeloSorprendido.Z);
    glRotatef(60, 0, 1, 0);
    glScalef(escalaObjetos.X, escalaObjetos.Y, escalaObjetos.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
    glmDraw(modeloSorprendido, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
}

void graficarAsustado()
{
    glPushMatrix();
    glTranslatef(posicionModeloAsustado.X, posicionModeloAsustado.Y, posicionModeloAsustado.Z);
    glRotatef(-10, 0, 1, 0);
    glScalef(escalaObjetos.X, escalaObjetos.Y, escalaObjetos.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
    glmDraw(modeloAsustado, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
}

void graficarTriste()
{
    glPushMatrix();
    glTranslatef(posicionModeloTriste.X, posicionModeloTriste.Y, posicionModeloTriste.Z);
    glRotatef(45, 0, 1, 0);
    glScalef(escalaObjetos.X, escalaObjetos.Y, escalaObjetos.Z);
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
    glmDraw(modeloTriste, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
}

void graficarAburrido()
{
    glPushMatrix();
    glTranslatef(posicionModeloAburrido.X, posicionModeloAburrido.Y, posicionModeloAburrido.Z);
    glRotatef(40, 0, 1, 0);
    glScalef(escalaObjetos.X-0.02f, escalaObjetos.Y-0.01f, escalaObjetos.Z-0.02f);  //Default { 0.25f, 0.3f, 0.25f }
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
    glmDraw(modeloAburrido, GLM_SMOOTH | GLM_TEXTURE);
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
        opcionMenu = 0;
        reiniciarEvent();
        glutPostRedisplay();
    }

    if(empezar && datosUsuario.resultados.size()==nroArchivoImagenes)
    {
        mostrarResultadosEvent();
    }

    if(empezar)
    {
        //Coordenadas de objetos 3D
        /*
        printf("Enojado: %f, %f, %f\n", posicionModeloEnojado.X, posicionModeloEnojado.Y, posicionModeloEnojado.Z);
        printf("Sorprendido: %f, %f, %f\n", posicionModeloSorprendido.X, posicionModeloSorprendido.Y, posicionModeloSorprendido.Z);
        printf("Asustado: %f, %f, %f\n", posicionModeloAsustado.X, posicionModeloAsustado.Y, posicionModeloAsustado.Z);
        printf("Triste: %f, %f, %f\n", posicionModeloTriste.X, posicionModeloTriste.Y, posicionModeloTriste.Z);
        printf("Aburrido: %f, %f, %f\n", posicionModeloAburrido.X, posicionModeloAburrido.Y, posicionModeloAburrido.Z);
        */

        //Objetos 3D
        graficarContento();
        graficarEnojado();
        graficarSorprendido();
        graficarAsustado();
        graficarTriste();
        graficarAburrido();

        //Objetos 2D
        graficarImagen2D();
        graficarFlechaIzquierda2D();
        graficarFlechaDerecha2D();
        graficarInfoUsuario();

        if(!datosUsuario.resultadoRegistrado(idArchivoImagenActual))
        {
            graficarTexto2D(4,(SCREEN_HEIGHT/2)+310,GLUT_BITMAP_8_BY_13,(char*)"tecla c <Contento>, tecla e <Enojado>, tecla s <Sorprendido>, tecla a <Asustado>, tecla t <Triste>, tecla h <Aburrido>");
        }
        else
        {
            graficarTexto2D(4,(SCREEN_HEIGHT/2)+310,GLUT_BITMAP_8_BY_13,(char*)"Respuesta registrada correctamente.");
        }
    }
    else
    {
        graficarTexto2D((SCREEN_WIDTH/2)-215,(SCREEN_HEIGHT/2),GLUT_BITMAP_TIMES_ROMAN_24,(char*)"Presiona la opcion 'Iniciar' para comenzar.");
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
    case 'c' :
    case 'e' :
    case 's' :
    case 'a' :
    case 't' :
    case 'h' :
        if(empezar && idArchivoImagenActual>=0 && idArchivoImagenActual<nroArchivoImagenes)
        {
            if(!datosUsuario.resultadoRegistrado(idArchivoImagenActual))
            {
                InfoResultado resultado;
                resultado.idImagen = idArchivoImagenActual;
                resultado.nombreEmocion = archivosImagenes[idArchivoImagenActual].nombreEmocion;
                switch(key)
                {
                case 'c':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Contento")==0;
                    break;
                case 'e':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Enojado")==0;
                    break;
                case 's':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Sorprendido")==0;
                    break;
                case 'a':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Asustado")==0;
                    break;
                case 't':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Triste")==0;
                    break;
                case 'h':
                    resultado.acertado = archivosImagenes[idArchivoImagenActual].nombreEmocion.compare("Aburrido")==0;
                    break;
                }
                if(resultado.acertado)
                {
                    datosUsuario.aciertos++;
                }
                else
                {
                    datosUsuario.desaciertos++;
                }
                datosUsuario.resultados.push_back(resultado);
            }
        }
        break;
    case 'j' :
        posicionModeloEnojado.Y+=0.01f;
        break;
    case 'k' :
        posicionModeloSorprendido.Y+=0.01f;
        break;
    case 'l' :
        posicionModeloAsustado.Y+=0.01f;
        break;
    case 'b' :
        posicionModeloEnojado.Y-=0.01f;
        break;
    case 'n' :
        posicionModeloSorprendido.Y-=0.01f;
        break;
    case 'm' :
        posicionModeloAsustado.Y-=0.1f;
        break;
    case 'u' :
        posicionModeloTriste.Y-=0.01f;
        break;
    case 'i' :
        posicionModeloTriste.Y-=0.1f;
        break;
    case 'o' :
        posicionModeloAburrido.Y-=0.01f;
        break;
    case 'p' :
        posicionModeloAburrido.Y-=0.1f;
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

    //Realizar la inicialización de configuraciones para la librería DevIL
    if(!initGL() || !initDevIL())
    {
        printf( "No se puede inicializar la biblioteca de gráficos!\n" );
        return 1;
    }

    modeloContento = glmReadOBJ((char*)"modelos/contento.obj");
    modeloEnojado = glmReadOBJ((char*)"modelos/enfadado.obj");
    modeloSorprendido = glmReadOBJ((char*)"modelos/sorprendido.obj");
    modeloAsustado = glmReadOBJ((char*)"modelos/asustado.obj");
    modeloTriste = glmReadOBJ((char*)"modelos/triste.obj");
    modeloAburrido = glmReadOBJ((char*)"modelos/aburrido.obj");

    crearMenu();

    GLUI_Master.set_glutDisplayFunc(graficar);//glutDisplayFunc(graficar);
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
