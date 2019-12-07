#ifndef GLUICONFIG_H_INCLUDED
#define GLUICONFIG_H_INCLUDED

#include <GL/glui.h>
#include "Utils.h" //User Custom Library 1

const int ID_BTN_LIMPIAR_DATOS = 1;
const int ID_BTN_INICIAR = 2;
const int ID_BTN_REINICIAR = 3;
const int ID_BTN_SALIR = 4;
const int ID_BTN_MOSTRAR_RESULTADO = 5;

GLUI_Panel *panelInputsIngresoDatos, *panelButtonsIngresoDatos, *panelButtonsControl, *panelResultados;
GLUI_EditText *txtNombres, *txtApellidos;
GLUI_Spinner* spnEdad;
GLUI_Button *btnIniciar, *btnLimpiarDatos, *btnReiniciar, *btnSalir, *btnGuardarResultado;
GLUI_TextBox *txtResultados;

InfoDatoUsuario datosUsuario;

int idArchivoImagenActual = 0, nivel = 1, totalImagenesActual = nroArchivoImagenesEmociones, opcionMenu = 0;

float rotT1 = 0, rotT2 = 0, rotT3 = 0;
bool  xd1 = 0;

bool empezar = false;

void limpiarDatosEvent(void)
{
    txtNombres->set_text((char*)"");
    txtApellidos->set_text((char*)"");
    spnEdad->set_int_val(5);
}

void reiniciarEvent(int id_nivel = 1)
{
    opcionMenu = 0;
    rotT1 = 0;
    rotT2 = 0;
    rotT3 = 0;
    xd1 = 0;
    nivel = id_nivel;
    switch(nivel)
    {
    case 1:
        totalImagenesActual = nroArchivoImagenesEmociones;
        break;
    case 2:
        totalImagenesActual = nroArchivoImagenesSituaciones;
        break;
    default:
        totalImagenesActual = 0;
        break;
    }
    idArchivoImagenActual = 0;
    empezar = false;
    datosUsuario.aciertos = 0;
    datosUsuario.desaciertos = 0;
    datosUsuario.resultados.clear();
    limpiarDatosEvent();
    panelInputsIngresoDatos->enable();
    btnReiniciar->disable();
    btnIniciar->enable();
    txtResultados->set_text((char*)"");
    btnGuardarResultado->disable();
}

void mostrarResultadosEvent(void)
{
    char resultadoFinal[800] = "", numero[10] = "";
    for(unsigned int i=0; i<datosUsuario.resultados.size(); i++)
    {
        int n = datosUsuario.resultados[i].nombreEmocion.length();
        char tempNombreEmocion[n+1];
        strcpy(tempNombreEmocion, datosUsuario.resultados[i].nombreEmocion.c_str());
        strcat(resultadoFinal, "Id Imagen: ");
        strcat(resultadoFinal, itoa(datosUsuario.resultados[i].idImagen+1, numero, 10));
        strcat(resultadoFinal, ", ");
        strcat(resultadoFinal, "Emocion: ");
        strcat(resultadoFinal, tempNombreEmocion);
        strcat(resultadoFinal, ", ");
        strcat(resultadoFinal, "Acertado: ");
        if(datosUsuario.resultados[i].acertado)
        {
            strcat(resultadoFinal, "Si");
        }
        else
        {
            strcat(resultadoFinal, "No");
        }
        strcat(resultadoFinal, "\n");
    }
    txtResultados->set_text(resultadoFinal);
    btnGuardarResultado->enable();
}

void manejadorButtons(int idButton)
{
    switch(idButton)
    {
    case ID_BTN_LIMPIAR_DATOS:
        limpiarDatosEvent();
        break;
    case ID_BTN_INICIAR:
        if(strlen(txtNombres->get_text())>0 && strlen(txtApellidos->get_text())>0)
        {
            panelInputsIngresoDatos->disable();
            btnReiniciar->enable();
            btnIniciar->disable();
            empezar = true;
        }
        else
        {
            MessageBox(NULL, (char*)"No ha ingresado datos del usuario.", (char*)"Error", MB_ICONERROR | MB_OK);
        }
        break;
    case ID_BTN_REINICIAR:
        reiniciarEvent();
        break;
    case ID_BTN_MOSTRAR_RESULTADO:
        MessageBox(NULL, txtResultados->get_text(), (char*)"Resultados", MB_ICONINFORMATION | MB_OK);
        break;
    }
}

void gluiControls(GLUI *gluiForm)
{
    panelInputsIngresoDatos = new GLUI_Panel(gluiForm, "Datos del usuario");
    txtNombres = new GLUI_EditText(panelInputsIngresoDatos, "Nombres:", datosUsuario.nombres);
    txtNombres->set_w(250);
    txtApellidos = new GLUI_EditText(panelInputsIngresoDatos, "Apellidos", datosUsuario.apellidos);
    txtApellidos->set_w(250);
    spnEdad = new GLUI_Spinner(panelInputsIngresoDatos, "Edad:", &datosUsuario.edad);
    spnEdad->set_int_limits(5,12);
    gluiForm->add_column_to_panel(panelInputsIngresoDatos, false);
    panelButtonsIngresoDatos = new GLUI_Panel(panelInputsIngresoDatos, "", false);
    btnLimpiarDatos = new GLUI_Button(panelButtonsIngresoDatos, "Limpiar", ID_BTN_LIMPIAR_DATOS, manejadorButtons);


    gluiForm->add_column(false);

    panelButtonsControl = new GLUI_Panel(gluiForm, "Controles");
    btnIniciar = new GLUI_Button(panelButtonsControl, "Iniciar", ID_BTN_INICIAR, manejadorButtons);
    btnReiniciar = new GLUI_Button(panelButtonsControl, "Reiniciar", ID_BTN_REINICIAR, manejadorButtons);
    btnReiniciar->disable();
    btnSalir = new GLUI_Button(panelButtonsControl, "Salir", ID_BTN_SALIR, (GLUI_Update_CB)exit);

    gluiForm->add_column(false);

    panelResultados = new GLUI_Panel(gluiForm, "Resultados");
    txtResultados = new GLUI_TextBox(panelResultados, true);
    txtResultados->set_w(300);
    txtResultados->set_h(48);
    txtResultados->disable();

    gluiForm->add_column_to_panel(panelResultados, false);

    btnGuardarResultado = new GLUI_Button(panelResultados, "Mostrar", ID_BTN_MOSTRAR_RESULTADO, manejadorButtons);
    btnGuardarResultado->set_w(64);
    btnGuardarResultado->disable();
}

#endif // GLUICONFIG_H_INCLUDED
