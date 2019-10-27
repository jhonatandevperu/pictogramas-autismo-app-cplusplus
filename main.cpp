#include <cstdio>
#include "LoadImage.h"
#include "Utils.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

Position posicionCamara = {3,1.5f, 2};
Position posicionFlechaIzquierda[3] = { { -3.5f, 3, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y+0.5f, 0 }, { posicionFlechaIzquierda[0].X+0.5f, posicionFlechaIzquierda[0].Y-0.5f, 0 } };
Position posicionFlechaDerecha[3] = { { -posicionFlechaIzquierda[0].X, posicionFlechaIzquierda[0].Y, posicionFlechaIzquierda[0].Z }, { -posicionFlechaIzquierda[1].X, posicionFlechaIzquierda[1].Y, posicionFlechaIzquierda[1].Z },  { -posicionFlechaIzquierda[2].X, posicionFlechaIzquierda[2].Y, posicionFlechaIzquierda[2].Z } };

int idArchivoImagenActual = 0;

void inicializar(void)
{
    FloatColorRGB colorClear = { 20, 20, 20 };
    glClearColor(colorClear.getRED(), colorClear.getGREEN(), colorClear.getBLUE(), 1);
    glEnable(GL_DEPTH_TEST);
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

void graficarFigura3D1()
{
    glPushMatrix();
    glTranslatef(-10,-4,0);
    glutWireCube(1);
    glPopMatrix();
}

void graficarFigura3D2()
{
    glPushMatrix();
    glTranslatef(-6,-4,0);
    glutWireCube(1);
    glPopMatrix();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicionCamara.X, posicionCamara.Y, posicionCamara.Z, 0, 0, 0, 0, 1, 0);

    graficarFigura3D1();
    graficarFigura3D2();
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
            }
        }
        //Clic en la flecha derecha
        if(XMouse<=1.05f && XMouse>=0.9f && YMouse<=1.05f && YMouse>=0.75f)
        {
            if(idArchivoImagenActual<nroArchivoImagenes-1)
            {
                idArchivoImagenActual++;
            }
        }
    }
}

void manejarTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':

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
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Proyecto Autismo");

    inicializar();

    //Realizar la inicialización de configuraciones para la librería DevIL
    if(!initGL() || !initDevIL())
    {
        printf( "No se puede inicializar la biblioteca de gráficos!\n" );
        return 1;
    }

    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(manejarTeclado);
    glutMouseFunc(manejadorMouse);
    glutMainLoop();

    return 0;
}
