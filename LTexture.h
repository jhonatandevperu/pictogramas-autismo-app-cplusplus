#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.
Link: http://lazyfoo.net/tutorials/OpenGL/06_loading_a_texture/index.php */
//Version: 002

#include <IL/il.h>
#include<cstdio>
#include <string>

class LTexture
{
public:
    /*
    Pre Condition:
     -None
    Post Condition:
     -Initializes member variables
    Side Effects:
     -None
    */
    LTexture()
    {
        //Initialize texture ID
        mTextureID = 0;

        //Initialize texture dimensions
        mTextureWidth = 0;
        mTextureHeight = 0;
    }

    /*
    Pre Condition:
    -None
    Post Condition:
    -Frees texture
    Side Effects:
    -None
    */
    ~LTexture()
    {
        //Free texture data if needed
        freeTexture();
    }

    /*
    Pre Condition:
    -A valid OpenGL context
    -Initialized DevIL
    Post Condition:
    -Creates a texture from the given file
    -Reports error to console if texture could not be created
    Side Effects:
    -Binds a NULL texture
    */
    bool loadTextureFromFile( std::string path )
    {
        //Texture loading success
        bool textureLoaded = false;

        //Generate and set current image ID
        ILuint imgID = 0;
        ilGenImages( 1, &imgID );
        ilBindImage( imgID );

        //Load image
        ILboolean success = ilLoadImage( path.c_str() );

        //Image loaded successfully
        if( success == IL_TRUE )
        {
            //Convert image to RGBA
            success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
            if( success == IL_TRUE )
            {
                //Create texture from file pixels
                textureLoaded = loadTextureFromPixels32( (GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) );
            }

            //Delete file from memory
            ilDeleteImages( 1, &imgID );
        }

        //Report error
        if( !textureLoaded )
        {
            printf( "Unable to load %s\n", path.c_str() );
        }

        return textureLoaded;
    }

    /*
    Pre Condition:
     -A valid OpenGL context
    Post Condition:
     -Creates a texture from the given pixels
     -Reports error to console if texture could not be created
    Side Effects:
     -Binds a NULL texture
    */
    bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height )
    {
        //Free texture if it exists
        freeTexture();

        //Get texture dimensions
        mTextureWidth = width;
        mTextureHeight = height;

        //Generate texture ID
        glGenTextures( 1, &mTextureID );

        //Bind texture ID
        glBindTexture( GL_TEXTURE_2D, mTextureID );

        //Generate texture
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

        //Set texture parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

        //Unbind texture
        glBindTexture( GL_TEXTURE_2D, 0 );

        //Check for error
        GLenum error = glGetError();
        if( error != GL_NO_ERROR )
        {
            printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
            return false;
        }

        return true;
    }

    /*
    Pre Condition:
     -A valid OpenGL context
    Post Condition:
     -Deletes texture if it exists
     -Sets texture ID to 0
    Side Effects:
     -None
    */
    void freeTexture()
    {
        //Delete texture
        if( mTextureID != 0 )
        {
            glDeleteTextures( 1, &mTextureID );
            mTextureID = 0;
        }

        mTextureWidth = 0;
        mTextureHeight = 0;
    }

    /*
    Pre Condition:
    -A valid OpenGL context
    -Active modelview matrix
    Post Condition:
    -Translates to given position and renders textured quad
    Side Effects:
    -Binds member texture ID
    */
    void render( GLfloat x, GLfloat y )
    {
        //If the texture exists
        if( mTextureID != 0 )
        {
            //Remove any previous transformations
            glLoadIdentity();

            //Move to rendering point
            glTranslatef( x, y, 0.f );

            //Set texture ID
            glBindTexture( GL_TEXTURE_2D, mTextureID );

            //Render textured quad
            glBegin( GL_QUADS );
            glTexCoord2f( 0.f, 0.f );
            glVertex2f(           0.f,            0.f );
            glTexCoord2f( 1.f, 0.f );
            glVertex2f( mTextureWidth,            0.f );
            glTexCoord2f( 1.f, 1.f );
            glVertex2f( mTextureWidth, mTextureHeight );
            glTexCoord2f( 0.f, 1.f );
            glVertex2f(           0.f, mTextureHeight );
            glEnd();
        }
    }

    /*
    Pre Condition:
     -None
    Post Condition:
     -Returns texture name/ID
    Side Effects:
     -None
    */
    GLuint getTextureID()
    {
        return mTextureID;
    }

    /*
    Pre Condition:
     -None
    Post Condition:
     -Returns texture width
    Side Effects:
     -None
    */
    GLuint textureWidth()
    {
        return mTextureWidth;
    }

    /*
    Pre Condition:
     -None
    Post Condition:
     -Returns texture height
    Side Effects:
     -None
    */
    GLuint textureHeight()
    {
        return mTextureHeight;
    }

private:
    //Texture name
    GLuint mTextureID;

    //Texture dimensions
    GLuint mTextureWidth;
    GLuint mTextureHeight;
};

#endif // LTEXTURE_H_INCLUDED
