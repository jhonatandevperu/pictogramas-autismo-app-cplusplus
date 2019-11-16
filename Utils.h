#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <cmath>
#include <vector>

struct FloatColorRGB //Need #include "cmath" library
{
    unsigned int setRED;
    unsigned int setGREEN;
    unsigned int setBLUE;
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

struct Position
{
    float X;
    float Y;
    float Z;
};

struct InfoResultado
{
    int idImagen;
    std::string nombreEmocion;
    bool acertado;
};

struct InfoDatoUsuario
{
    char nombres[60];
    char apellidos[60];
    int edad;
    std::vector<InfoResultado> resultados;
    int aciertos;
    int desaciertos;
    bool resultadoRegistrado(int &idImagen)
    {
        for(unsigned int i=0; i<resultados.size(); i++)
        {
            if(resultados[i].idImagen==idImagen)
            {
                return true;
            }
        }
        return false;
    }
};

#endif // UTILS_H_INCLUDED
