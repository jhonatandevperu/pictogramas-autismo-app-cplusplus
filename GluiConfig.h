#ifndef GLUICONFIG_H_INCLUDED
#define GLUICONFIG_H_INCLUDED

#include <GL/glui.h>
#include "Utils.h" //User Custom Library 1

const int ID_BTN_LIMPIAR_DATOS = 1;
const int ID_BTN_INICIAR = 2;
const int ID_BTN_REINICIAR = 3;
const int ID_BTN_SALIR = 4;

GLUI_Panel *panelInputsIngresoDatos, *panelButtonsIngresoDatos, *panelButtonsControl, *panelResultados;
GLUI_EditText *txtNombres, *txtApellidos;
GLUI_Spinner* spnEdad;
GLUI_Button *btnIniciar, *btnLimpiarDatos, *btnReiniciar, *btnSalir;
GLUI_TextBox *txtResultados;

InfoDatoUsuario infoDatoUsuario;

int idArchivoImagenActual = 0;
bool empezar = false;

void limpiarDatosEvent(void)
{
    txtNombres->set_text((char*)"");
    txtApellidos->set_text((char*)"");
    spnEdad->set_int_val(5);
}

void reiniciarEvent(void)
{
    idArchivoImagenActual = 0;
    empezar = false;
    infoDatoUsuario.infoResulto.aciertos = 0;
    infoDatoUsuario.infoResulto.desaciertos = 0;
    limpiarDatosEvent();
    panelInputsIngresoDatos->enable();
    btnReiniciar->disable();
    btnIniciar->enable();
    txtResultados->set_text("");
}

void mostrarResultadosEvent(void)
{
    txtResultados->set_text("Hola");
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
            MessageBox(NULL, (char*)"No ha ingresado datos del usuario.", (char*)"Error", MB_OK | MB_ICONERROR);
        }
        break;
    case ID_BTN_REINICIAR:
        reiniciarEvent();
        break;
    }
}

void gluiControls(GLUI *gluiForm)
{
    panelInputsIngresoDatos = new GLUI_Panel(gluiForm, "Datos del usuario");
    txtNombres = new GLUI_EditText(panelInputsIngresoDatos, "Nombres:", infoDatoUsuario.nombres);
    txtNombres->set_w(250);
    txtApellidos = new GLUI_EditText(panelInputsIngresoDatos, "Apellidos", infoDatoUsuario.apellidos);
    txtApellidos->set_w(250);
    spnEdad = new GLUI_Spinner(panelInputsIngresoDatos, "Edad:", &infoDatoUsuario.edad);
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
    txtResultados->set_w(370);
    txtResultados->set_h(48);
    txtResultados->disable();
}

#endif // GLUICONFIG_H_INCLUDED
