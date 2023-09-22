#include <iostream>
#include <string>
#include <cstring>
using namespace std;
// Estructura para representar una tarea
struct Tarea {
    char nombre[100];
    char descripcion[200];
    bool completada;
};
// Estructura para representar un proyecto
struct Proyecto {
    char nombre[100];
    char descripcion[200];
    Tarea* tareas[10];
    int numTareas;
};
// Función para agregar una tarea a un proyecto
void agregarTarea(Proyecto& proyecto, const char* nombre, const char* descripcion) {
    if (proyecto.numTareas < 10) {
        Tarea* nuevaTarea = new Tarea;
        strcpy(nuevaTarea->nombre, nombre);
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
    int indiceTarea;
    cout << "Ingrese el índice de la tarea para cambiar su estado (1-" << proyecto.numTareas << "): ";
    cin >> indiceTarea;

    if (indiceTarea >= 1 && indiceTarea <= proyecto.numTareas) {
        int indice = indiceTarea - 1; // Ajustar el índice para usarlo en el arreglo
        proyecto.tareas[indice]->completada = !proyecto.tareas[indice]->completada;
        cout << "Estado de la Tarea " << indiceTarea << " cambiado." << endl;

        char respuesta;
        cout << "¿Desea cambiar el estado de otra tarea? (S/N): ";
        cin >> respuesta;
        if (respuesta == 'S' || respuesta == 's') {
            cambiarEstadoTarea(proyecto); // Llamada recursiva
        }
    } else {
        cout << "Índice de tarea inválido." << endl;
    }
}

int main() {
    Proyecto miProyecto;
    cout << "Ingrese el nombre del proyecto: ";
    cin.getline(miProyecto.nombre, sizeof(miProyecto.nombre));
    cout << "Ingrese la descripción del proyecto: ";
    cin.getline(miProyecto.descripcion, sizeof(miProyecto.descripcion));
    miProyecto.numTareas = 0;
    int numTareas;
    cout << "Ingrese la cantidad de tareas a agregar: ";
    cin >> numTareas;

    cin.ignore(); // Limpiar el búfer de entrada

    for (int i = 0; i < numTareas; i++) {
        char nombreTarea[100];
        char descripcionTarea[200];

        cout << "Ingrese el nombre de la Tarea " << i + 1 << ": ";
        cin.getline(nombreTarea, sizeof(nombreTarea));
        cout << "Ingrese la descripción de la Tarea " << i + 1 << ": ";
        cin.getline(descripcionTarea, sizeof(descripcionTarea));
        agregarTarea(miProyecto, nombreTarea, descripcionTarea);
    }

    mostrarTareas(miProyecto);

    char respuesta;
    do {
        cambiarEstadoTarea(miProyecto);
        mostrarTareas(miProyecto);
        cout << "¿Desea cambiar el estado de otra tarea? (S/N): ";
        cin >> respuesta;
    } while (respuesta == 'S' || respuesta == 's');

    // Liberar la memoria de las tareas en el heap
    for (int i = 0; i < miProyecto.numTareas; i++) {
        delete miProyecto.tareas[i];
    }
    return 0;
}