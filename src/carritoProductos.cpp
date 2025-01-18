#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    TCarritoProductos sig;
};


TCarritoProductos crearCarritoProductosVacio(){
    TCarritoProductos carrito = NULL;
    return carrito;
}

void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    int idProd = idTProducto(producto);

    if (esVacioCarritoProductos(carritoProductos)) {
        carritoProductos = new rep_carritoProductos;
        carritoProductos->producto = producto;
        carritoProductos->sig = NULL;
    } else {
            TCarritoProductos temp = carritoProductos, nuevoNodo;

            nuevoNodo = new rep_carritoProductos;
            nuevoNodo->producto = producto;
            nuevoNodo->sig = NULL;
            
            if (idProd < idTProducto(carritoProductos->producto)) {
                nuevoNodo->sig = carritoProductos;
                carritoProductos = nuevoNodo;
            } else {
                while (temp->sig != NULL && idProd > idTProducto(temp->sig->producto)) {
                    temp = temp->sig;
                }
                nuevoNodo->sig = temp->sig;
                temp->sig = nuevoNodo;
            }
        }
    }


void imprimirCarritoProductos(TCarritoProductos carritoProductos) {
    if(esVacioCarritoProductos(carritoProductos)) return;
    TCarritoProductos temp1 = carritoProductos;

    while (temp1 != NULL) {
        imprimirTProducto(temp1->producto);
        temp1 = temp1->sig;
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos) {
    TCarritoProductos temp;

    while (carritoProductos != NULL) {
        temp = carritoProductos;
        carritoProductos = carritoProductos->sig;
        liberarTProducto(temp->producto);
        delete temp;
    }

    carritoProductos = NULL;
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos) {
    return (carritoProductos == NULL);
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    while (carritoProductos != NULL) {
        if (idTProducto(carritoProductos->producto) == idProducto) {
            return true;
        }
        carritoProductos = carritoProductos->sig;
    }
    return false;
}

TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    int idCarro = idTProducto(carritoProductos->producto);

    while (carritoProductos != NULL && idProducto != idCarro) {
        carritoProductos = carritoProductos->sig;
        idCarro = idTProducto(carritoProductos->producto);
    }
    return carritoProductos->producto;
}

void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto) {
    TCarritoProductos temp = carritoProductos, anterior = NULL;

    while (temp != NULL && idTProducto(temp->producto) != idProducto) {
        anterior = temp;
        temp = temp->sig;
    }

    if (temp != NULL) {
        if (anterior == NULL) {
            carritoProductos = temp->sig;
        } else {
            anterior->sig = temp->sig;
        }

        liberarTProducto(temp->producto);
        delete temp;
    }
}
