//PROYECTO-ESTRUCTURA DE DATOS
//Desarrollo de un sistema de gestion de tareas y proyectos para alumnos

//INTEGRANTES
//Espiritu Campos Alejandro
//Javier Curi Dayana Jessica
//Ricaldi Solis Maylon Amilcar

//ENLACE AL DOCUMENTO: https://docs.google.com/document/d/1C8n3xzeQC1o4xC-KhelpdVggKCtqR4ZIJfgsI5aghu0/edit?usp=sharing

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Estructura para representar una tarea
struct Tarea {
    char *nombre;
    char *descripcion;
    bool completada;
};

// Estructura para representar un proyecto
struct Proyecto {
    char* nombre;
    char* descripcion;
    Tarea* tareas[10];
    int numTareas;
};

// Función para agregar una tarea a un proyecto
void agregarTarea(Proyecto& proyecto, const char* nombre, const char* descripcion) {
    if (proyecto.numTareas < 10) {
        Tarea *nuevaTarea = new Tarea;
        nuevaTarea->nombre = new char[strlen(nombre) + 1];
        strcpy(nuevaTarea->nombre, nombre);
        nuevaTarea->descripcion = new char[strlen(descripcion) + 1];
        strcpy(nuevaTarea->descripcion, descripcion);
        nuevaTarea->completada = false;
        proyecto.tareas[proyecto.numTareas] = nuevaTarea;
        proyecto.numTareas++;
        cout << "Tarea agregada al proyecto " << proyecto.nombre << "." << endl;
    } else {
        cout << "No se pueden agregar más tareas al proyecto, límite alcanzado." << endl;
    }
}

// Función para mostrar las tareas de un proyecto
void mostrarTareas(const Proyecto& proyecto) {
    cout << "Tareas en el proyecto " << proyecto.nombre << ":" << endl;
    for (int i = 0; i < proyecto.numTareas; i++) {
        cout << "Tarea " << i + 1 << ": " << proyecto.tareas[i]->nombre << endl;
        cout << "Descripción: " << proyecto.tareas[i]->descripcion << endl;
        cout << "Estado: " << (proyecto.tareas[i]->completada ? "Realizado" : "Pendiente") << endl;
    }
}

// Función para cambiar el estado de una tarea de manera recursiva
void cambiarEstadoTarea(Proyecto& proyecto) {
    int *indiceTarea=new int;
    cout << "Ingrese el índice de la tarea para cambiar su estado (1-" << proyecto.numTareas << "): ";
    cin >> *indiceTarea;

    if (*indiceTarea >= 1 && *indiceTarea <= proyecto.numTareas) {
        int indice = *indiceTarea - 1; // Ajustar el índice para usarlo en el arreglo
        proyecto.tareas[indice]->completada = !proyecto.tareas[indice]->completada;
        cout << "Estado de la Tarea " << *indiceTarea << " cambiado." << endl;

        char *respuesta = new char;
        cout << "¿Desea cambiar el estado de otra tarea? (S/N): ";
        cin >> *respuesta;
        if (*respuesta == 'S' || *respuesta == 's') {
            cambiarEstadoTarea(proyecto); // Llamada recursiva
        }
    } else {
        cout << "Índice de tarea inválido." << endl;
    }
}

int main() {
    Proyecto *miProyecto = new Proyecto;

    // Solicitar y asignar memoria para el nombre del proyecto
    miProyecto->nombre = new char[100];
    cout << "Ingrese el nombre del proyecto: ";
    cin.getline(miProyecto->nombre, 100);

    // Solicitar y asignar memoria para la descripción del proyecto
    miProyecto->descripcion = new char[200];
    cout << "Ingrese la descripción del proyecto: ";
    cin.getline(miProyecto->descripcion, 200);

    miProyecto->numTareas = 0;
    int *numTareas = new int;
    cout << "Ingrese la cantidad de tareas a agregar: ";
    cin >> *numTareas;

    cin.ignore(); // Limpiar el búfer de entrada

    for (int i = 0; i < *numTareas; i++) {
        char nombreTarea[100];
        char descripcionTarea[200];

        cout << "Ingrese el nombre de la Tarea " << i + 1 << ": ";
        cin.getline(nombreTarea, sizeof(nombreTarea));
        cout << "Ingrese la descripción de la Tarea " << i + 1 << ": ";
        cin.getline(descripcionTarea, sizeof(descripcionTarea));
        agregarTarea(*miProyecto, nombreTarea, descripcionTarea);
    }

    mostrarTareas(*miProyecto);

    char *respuesta = new char;
    do {
        cambiarEstadoTarea(*miProyecto);
        mostrarTareas(*miProyecto);
        cout << "¿Desea cambiar el estado de otra tarea? (S/N): ";
        cin >> *respuesta;
    } while (*respuesta == 'S' || *respuesta == 's');

    // Liberar la memoria de las tareas en el heap
    for (int i = 0; i < miProyecto->numTareas; i++) {
        delete[] miProyecto->tareas[i]->nombre;
        delete[] miProyecto->tareas[i]->descripcion;
        delete miProyecto->tareas[i];
    }

    // Liberar la memoria para el nombre y la descripción del proyecto
    delete[] miProyecto->nombre;
    delete[] miProyecto->descripcion;

    return 0;
}