#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    TClientesABB izquierda;
    TClientesABB derecha;
};

TClientesABB crearTClientesABBVacio(){
    return NULL;
}

void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente){
    if (clientesABB == NULL) {
        clientesABB = new(rep_clientesABB);
        clientesABB->cliente = cliente;
        clientesABB->izquierda = NULL;
        clientesABB->derecha = NULL;
    } else {
        int clienteId = idTCliente(cliente);
        if (clienteId < idTCliente(clientesABB->cliente)) {
            insertarTClienteTClientesABB(clientesABB->izquierda, cliente);
        } else if (clienteId > idTCliente(clientesABB->cliente)) {
            insertarTClienteTClientesABB(clientesABB->derecha, cliente);
        }
    }
}

void imprimirTClientesABB(TClientesABB clientesABB){
    if (clientesABB != NULL) {
        imprimirTClientesABB(clientesABB->izquierda);
        imprimirTCliente(clientesABB->cliente);
        imprimirTClientesABB(clientesABB->derecha);
    }
}

void liberarTClientesABB(TClientesABB &clientesABB){
    if(clientesABB != NULL) {
        liberarTClientesABB(clientesABB->izquierda);
        liberarTClientesABB(clientesABB->derecha);
        liberarTCliente(clientesABB->cliente);
        delete clientesABB;
        clientesABB = NULL;
    }
}

bool existeTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if (clientesABB == NULL) return false;
    int idABB = idTCliente(clientesABB->cliente);
    if (idABB == idCliente) {
        return true;
    } else if (idCliente < idABB) {
        return existeTClienteTClientesABB(clientesABB->izquierda, idCliente);
    } else if (idCliente > idABB) {
        return existeTClienteTClientesABB(clientesABB->derecha, idCliente);
    }
}

TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    int idABB = idTCliente(clientesABB->cliente);
    if (idABB == idCliente) {
        return clientesABB->cliente;
    } else if (idCliente < idABB) {
        return obtenerTClienteTClientesABB(clientesABB->izquierda, idCliente);
    } else if (idCliente > idABB) {
        return obtenerTClienteTClientesABB(clientesABB->derecha, idCliente);
    }
}

nat alturaTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) return 0;

    int alturaIzq = alturaTClientesABB(clientesABB->izquierda);
    int alturaDer = alturaTClientesABB(clientesABB->derecha);

    return (alturaIzq > alturaDer ? alturaIzq : alturaDer) + 1;
}

TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB){
    if (clientesABB->derecha != NULL) {
        return maxIdTClienteTClientesABB(clientesABB->derecha);
    }
    return clientesABB->cliente;
}

void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente){
    if (clientesABB == NULL) return;

    int idGrupo = idTCliente(clientesABB->cliente);

    if (idCliente < idGrupo) {
        removerTClienteTClientesABB(clientesABB->izquierda, idCliente);
    } else if (idCliente > idGrupo) {
        removerTClienteTClientesABB(clientesABB->derecha, idCliente);
    } else {
        if (clientesABB->izquierda == NULL && clientesABB->derecha == NULL) {
            liberarTCliente(clientesABB->cliente);
            delete clientesABB;
            clientesABB = NULL;
        } else if (clientesABB->izquierda == NULL) {
            TClientesABB temp = clientesABB;
            clientesABB = clientesABB->derecha;
            liberarTCliente(temp->cliente);
            delete temp;
        } else if (clientesABB->derecha == NULL) {
            TClientesABB temp = clientesABB;
            clientesABB = clientesABB->izquierda;
            liberarTCliente(temp->cliente);
            delete temp;
        } else {
            TClientesABB mayorIzquierdo = clientesABB->izquierda, padreMayorIzquierdo = clientesABB;

            while (mayorIzquierdo->derecha != NULL) {
                padreMayorIzquierdo = mayorIzquierdo;
                mayorIzquierdo = mayorIzquierdo->derecha;
            }

            clientesABB->cliente = mayorIzquierdo->cliente;

            if(padreMayorIzquierdo->derecha == mayorIzquierdo) {
                padreMayorIzquierdo->derecha = mayorIzquierdo->izquierda;
            } else {
                padreMayorIzquierdo->izquierda = mayorIzquierdo->izquierda;
            }
            delete mayorIzquierdo;
        }
    }
}

int cantidadClientesTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) return 0;
    return cantidadClientesTClientesABB(clientesABB->izquierda) + cantidadClientesTClientesABB(clientesABB->derecha) + 1;
}

void calcularEdadYCantidad(TClientesABB clientesABB, int &sumaEdades, int &cantidadClientes) {
    if (clientesABB == NULL) return;

    calcularEdadYCantidad(clientesABB->izquierda, sumaEdades, cantidadClientes);

    sumaEdades += edadTCliente(clientesABB->cliente);
    cantidadClientes++;

    calcularEdadYCantidad(clientesABB->derecha, sumaEdades, cantidadClientes);
}

float edadPromedioTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) return 0;
    
    int edadTotal = 0, cantidadClientes = 0;

    calcularEdadYCantidad(clientesABB, edadTotal, cantidadClientes);

    return (cantidadClientes > 0) ? (float)edadTotal / cantidadClientes : 0;
}


TCliente obtenerNesimoClienteAux(TClientesABB clientesABB, int n, int &indiceActual) {
    if (clientesABB == NULL) return NULL;
    TCliente resultado = obtenerNesimoClienteAux(clientesABB, n, indiceActual);
    if (resultado != NULL) {
        return resultado;
    }

    indiceActual++;
    if (indiceActual == n){
        return clientesABB->cliente;
    }

    return obtenerNesimoClienteAux(clientesABB->derecha, n, indiceActual);
}

TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n){
    int indiceActual = 0;
    return obtenerNesimoClienteAux(clientesABB, n, indiceActual);
}
