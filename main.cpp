#include <cstdio>
#include <cmath>
#include "LoadImage.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

struct FloatColorRGB //Need #include "cmath" library
{
    int setRED;
    int setGREEN;
    int setBLUE;
    float getRED()
    {
        return roundf(((float)setRED / 255) * 100) / 100;
    };
    float getGREEN()
    {
        return roundf(((float)setGREEN / 255) * 100) / 100;
    };
    float getBLUE()
    {
        return roundf(((float)setBLUE / 255) * 100) / 100;
    };
};

struct Posicion
{
    float X;
    float Y;
    float Z;
} posicionCamara = {3,1.5f, 2};

struct ArchivoImagen
{
    std::string nombreArchivo;
    std::string nombreEmocion;
} const archivosImagenes[] =
{
    { "01.png", "Contento" },
    { "02.png", "Triste" },
    { "03.png", "Sorprendido" },
    { "04.png", "Contento" },
    { "05.png", "Asustado" },
    { "06.png", "Enfadado" },
    { "07.png", "Contento" },
    { "08.png", "Asustado" },
    { "09.png", "Enfadado" },
    { "10.png", "Triste" },
    { "11.png", "Triste" },
    { "12.png", "Contento" },
    { "13.png", "Contento" },
    { "14.png", "Aburrido" },
    { "15.png", "Enfadado" },
    { "16.png", "Contento" },
    { "17.png", "Aburrido" },
    { "18.png", "Sorprendido" },
    { "19.png", "Aburrido" },
    { "20.png", "Sorprendido"},
    { "21.png", "Aburrido" },
    { "22.png", "Enojado" },
    { "23.png", "Contento" },
    { "24.png", "Contento" },
    { "25.png", "Asustado" },
    { "26.png", "Aburrido" },
    { "27.png", "Contento" },
    { "28.png", "Triste" },
    { "29.png", "Asustado" },
    { "30.png", "Sorprendido"}
};

const int nroArchivoImagenes = sizeof(archivosImagenes)/sizeof(ArchivoImagen);
int idArchivoImagenActual = 0;

void inicializar(void)
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void redimensionar(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / (float)h, 1, 500);
}

void graficar2D()
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

void graficar3D()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glutWireCube(2);
    glPopMatrix();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicionCamara.X, posicionCamara.Y, posicionCamara.Z, 0, 0, 0, 0, 1, 0);

    graficar3D();
    graficar2D();

    glutSwapBuffers();
}


void manejarTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        if(idArchivoImagenActual<nroArchivoImagenes-1)
        {
            idArchivoImagenActual++;
        }
        else
        {
            idArchivoImagenActual = 0;
        }
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
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
    glutMainLoop();
    return 0;
}
