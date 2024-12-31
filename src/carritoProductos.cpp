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
    if (esVacioCarritoProductos(carritoProductos)) {
        carritoProductos->producto = producto;
        carritoProductos->sig = NULL;
    } else {
        int idProd, idCarro;
        idProd = idTProducto(producto);
        idCarro = idTProducto(carritoProductos->producto);
        if (!existeProductoCarritoProductos(carritoProductos, idProd)) {
            TCarritoProductos temp1, temp2;
            temp1 = carritoProductos;
            
            if (idProd < idCarro) {
                carritoProductos->producto = producto;
                carritoProductos->sig = temp1;
            } else {
                idCarro = idTProducto(temp1->sig->producto);
                while (temp1->sig != NULL && idProd > idCarro) {
                    temp1 = temp1->sig;
                    idCarro = idTProducto(temp1->sig->producto);
                }

                if (temp1->sig == NULL) {
                    temp1->sig->producto == producto;
                    temp1->sig->sig == NULL;
                } else {
                    temp2 = temp1->sig;
                    temp1->producto = producto;
                    temp1->sig = temp2;
                }
            }
        }
    }
}

void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    if(!esVacioCarritoProductos(carritoProductos)) {
        TCarritoProductos temp1 = carritoProductos;

        while (temp1 != NULL) {
            imprimirTProducto(temp1->producto);
            temp1 = temp1->sig;
        }
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    TCarritoProductos temp = carritoProductos;

    while (carritoProductos != NULL) {
        carritoProductos = carritoProductos->sig;
        liberarTProducto(temp->producto);
        delete temp;
        temp = carritoProductos;
    }
    delete temp;
    delete carritoProductos;
    carritoProductos = NULL;
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    bool vacio = carritoProductos == NULL;
    return vacio;
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    TCarritoProductos temp;
    temp = carritoProductos;
    int idCarro = idTProducto(temp->producto);
    while (temp != NULL && idProducto != idCarro) {
        temp = temp->sig;
        idCarro = idTProducto(temp->producto);
    }
    return temp != NULL;
}

TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    TProducto prod;
    if(existeProductoCarritoProductos(carritoProductos, idProducto)) {
        TCarritoProductos temp = carritoProductos;
        int idCarro = idTProducto(temp->producto);

        while (temp != NULL && idProducto != idCarro) {
            temp = temp->sig;
            idCarro = idTProducto(temp->producto);
        }
        
        prod = temp->producto;
    }
    return prod;
}

void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){
    if(existeProductoCarritoProductos(carritoProductos, idProducto)) {
        TCarritoProductos temp1, temp2, temp3;
        temp1 = carritoProductos;
        int idCarro = idTProducto(temp1->producto);
        bool encontrado = idProducto == idCarro;

        if (encontrado) {
            temp1 = carritoProductos;
            carritoProductos = carritoProductos->sig;
            liberarTProducto(temp1->producto);
            delete temp1;
        } else {
            idCarro = idTProducto(temp1->sig->producto);
            encontrado = idProducto == idCarro;
            while (temp1->sig != NULL && !encontrado) {
                temp1 = temp1->sig;
                idCarro = idTProducto(temp1->sig->producto);
                encontrado = idProducto == idCarro;
            }

            if (temp1->sig == NULL) {
                liberarTProducto(temp1->sig->producto);
                delete temp1;
            } else {
                temp2 = temp1->sig;
                temp3 = temp2->sig;
                temp1->sig = temp3;
                liberarTProducto(temp2->producto);
                delete temp2;
            }
        }
    }
}