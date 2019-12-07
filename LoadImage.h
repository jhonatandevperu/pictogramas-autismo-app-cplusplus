#ifndef LOADIMAGE_H_INCLUDED
#define LOADIMAGE_H_INCLUDED

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <cstdio>
#include "LTexture.h"

//File loaded texture
LTexture gLoadedTexture;

struct ArchivoImagen
{
    std::string nombreArchivo;
    std::string nombreEmocion;
} const archivosImagenesEmociones[] =
{
    { "01.png", "Contento" },
    { "02.png", "Triste" },
    { "03.png", "Sorprendido" },
    { "04.png", "Contento" },
    { "05.png", "Asustado" },
    { "06.png", "Enojado" },
    { "07.png", "Contento" },
    { "08.png", "Asustado" },
    { "09.png", "Enojado" },
    { "10.png", "Triste" },
    { "11.png", "Triste" },
    { "12.png", "Contento" },
    { "13.png", "Contento" },
    { "14.png", "Aburrido" },
    { "15.png", "Enojado" },
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
}, archivosImagenesSituaciones[] =
{
    { "01.jpeg", "Contento" },
    { "02.jpeg", "Triste" },
    { "03.jpeg", "Asustado" },
    { "04.jpeg", "Avergonzado" },
    { "05.jpeg", "Contento" },
    { "06.jpeg", "Enojado" },
    { "07.jpeg", "Triste" },
    { "08.jpeg", "Contento" },
    { "09.jpeg", "Triste" },
    { "10.jpeg", "Contento" },
    { "11.jpeg", "Avergonzado" },
    { "12.jpeg", "Enojado" }
};

const int nroArchivoImagenesEmociones = sizeof(archivosImagenesEmociones)/sizeof(ArchivoImagen);
const int nroArchivoImagenesSituaciones = sizeof(archivosImagenesSituaciones)/sizeof(ArchivoImagen);

/*
Pre Condition:
 -A valid OpenGL context
Post Condition:
 -Initializes viewport, matrices and clear color
 -Initializes DevIL
 -Reports to console if there was an OpenGL error
 -Reports to console if there was a DevIL error
 -Returns false if there was an error in initialization
Side Effects:
 -Sets viewport to the fill rendering area
 -Projection matrix is set to an orthographic matrix
 -Modelview matrix is set to identity matrix
 -Matrix mode is set to modelview
 -Clear color is set to black
 -Texturing is enabled
 -Sets DevIL clear color to transparent white
*/
bool initGL() //Custom from Official
{
    //Enable texturing
    glEnable( GL_TEXTURE_2D );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    return true;
}

bool initDevIL() //Custom from Official
{
    //Initialize DevIL
    ilInit();
    ilClearColour( 255, 255, 255, 000 );

    //Check for error
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        printf( "Error initializing DevIL! %s\n", iluErrorString( ilError ) );
        return false;
    }

    return true;
}

/*
Pre Condition:
 -A valid OpenGL context
Post Condition:
 -Loads media to use in the program
 -Reports to console if there was an error in loading the media
 -Returns true if the media loaded successfully
Side Effects:
 -None
*/
bool loadMedia(std::string imageSrc) //Custom from Official
{
    //Load texture
    if( !gLoadedTexture.loadTextureFromFile( imageSrc ) )
    {
        printf( "Unable to load file texture!\n" );
        return false;
    }
    return true;
}

/*
Pre Condition:
 -None
Post Condition:
 -Does per frame logic
Side Effects:
 -None
*/
void update()
{
}

/*
Pre Condition:
 -A valid OpenGL context
 -Active modelview matrix
Post Condition:
 -Renders the scene
Side Effects:
 -Clears the color buffer
 -Swaps the front/back buffer
*/
void renderCenter(int SCREEN_WIDTH, int SCREEN_HEIGHT) //Custom from Official
{
    //Calculate centered offsets
    GLfloat x = ( SCREEN_WIDTH - gLoadedTexture.textureWidth() ) / 2.f;
    GLfloat y = ( SCREEN_HEIGHT - gLoadedTexture.textureHeight() ) / 2.f;

    //Render texture
    gLoadedTexture.render( x, y );
}

void renderInPosition(int SCREEN_WIDTH, int SCREEN_HEIGHT, GLfloat x = 0, GLfloat y = 0) //Custom from Official
{
    //Render texture
    gLoadedTexture.render( x, y );
}

void renderCenterInX(int SCREEN_WIDTH, int SCREEN_HEIGHT, GLfloat y = 0) //Custom from Official
{
    //Calculate centered offsets
    GLfloat x = ( SCREEN_WIDTH - gLoadedTexture.textureWidth() ) / 2.f;

    //Render texture
    gLoadedTexture.render( x, y );
}

void renderCenterInY(int SCREEN_WIDTH, int SCREEN_HEIGHT, GLfloat x = 0) //Custom from Official
{
    //Calculate centered offsets
    GLfloat y = ( SCREEN_HEIGHT - gLoadedTexture.textureHeight() ) / 2.f;

    //Render texture
    gLoadedTexture.render( x, y );
}

#endif // LOADIMAGE_H_INCLUDED
