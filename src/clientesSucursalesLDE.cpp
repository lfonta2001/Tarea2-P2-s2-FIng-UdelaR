#include "../include/clientesSucursalesLDE.h"

struct rep_nodoClientesSucursalesLDE {
	TClientesABB clientesABB;
	int idSucursal;
	float edadPromedio;
	nodoClientesSucursalesLDE anterior, siguiente;
};

struct rep_clientesSucursalesLDE {
	nodoClientesSucursalesLDE inicio, final;
};

TClientesSucursalesLDE crearTClientesSucursalesLDEVacia(){
	TClientesSucursalesLDE nuevaSucursalLDE = new(rep_clientesSucursalesLDE);
	nuevaSucursalLDE->inicio = nuevaSucursalLDE->final = NULL;
	return nuevaSucursalLDE;
}

void insertarClientesABBTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, TClientesABB clientesABB, int idSucursal){
	nodoClientesSucursalesLDE nuevoNodo = new(rep_nodoClientesSucursalesLDE);
	nuevoNodo->clientesABB = clientesABB;
	nuevoNodo->idSucursal = idSucursal;
	nuevoNodo->edadPromedio = edadPromedioTClientesABB(clientesABB);
	nuevoNodo->anterior = NULL;
	nuevoNodo->siguiente = NULL;

	if (clientesSucursalesLDE->inicio == NULL) {
		clientesSucursalesLDE->inicio = nuevoNodo;
		clientesSucursalesLDE->final = nuevoNodo;
	} else {
		nodoClientesSucursalesLDE temp = clientesSucursalesLDE->inicio;

		if (nuevoNodo->edadPromedio < temp->edadPromedio) {
			nuevoNodo->siguiente = temp;
			temp->anterior = nuevoNodo;
			clientesSucursalesLDE->inicio = nuevoNodo;
		} else {
			while ((temp->siguiente != NULL) && (nuevoNodo->edadPromedio >= temp->edadPromedio)) {
				temp = temp->siguiente;
			}

			if (temp->siguiente == NULL && nuevoNodo->edadPromedio > temp->edadPromedio) {
				temp->siguiente = nuevoNodo;
				nuevoNodo->anterior = temp;
				clientesSucursalesLDE->final = nuevoNodo;
			} else {
				temp->anterior->siguiente = nuevoNodo;
				nuevoNodo->siguiente = temp;
				nuevoNodo->anterior = temp->anterior;
				temp->anterior = nuevoNodo;
			}
		}
	}
}

void liberarTClientesSucursalesLDE(TClientesSucursalesLDE &clientesSucursalesLDE) {
    nodoClientesSucursalesLDE actual = clientesSucursalesLDE->inicio;
    while (actual != NULL) {
        nodoClientesSucursalesLDE siguiente = actual->siguiente;

        liberarTClientesABB(actual->clientesABB);

        delete actual;
        actual = siguiente;
    }
    delete clientesSucursalesLDE;
    clientesSucursalesLDE = NULL;
}

void imprimirTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	nodoClientesSucursalesLDE temp = clientesSucursalesLDE->inicio;
	printf("clientesSucursalesLDE de grupos:\n");
	while (temp != NULL) {
		printf("Grupo con edad promedio %.2f:\n", temp->edadPromedio);
		imprimirTClientesABB(temp->clientesABB);
		temp = temp->siguiente;
	}
}

void imprimirInvertidoTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	nodoClientesSucursalesLDE temp = clientesSucursalesLDE->final;
	printf("clientesSucursalesLDE de grupos:\n");
	while (temp != NULL) {
		printf("Grupo con edad promedio %.2f:\n", temp->edadPromedio);
		imprimirTClientesABB(temp->clientesABB);
		temp = temp->anterior;
	}
}

nat cantidadTClientesABBClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	nat cantidad = 0;
	nodoClientesSucursalesLDE nodo = clientesSucursalesLDE->inicio;
	while (nodo != NULL) {
		cantidad++;
		nodo = nodo->siguiente;
	}
	return cantidad;
}

TClientesABB obtenerPrimeroClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	return clientesSucursalesLDE->inicio->clientesABB;
}

TClientesABB obtenerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
	nodoClientesSucursalesLDE nodo = clientesSucursalesLDE->inicio;
	while (n > 1 && nodo != NULL) {
		nodo = nodo->siguiente;
		n--;
	}
	return (nodo != NULL) ? nodo->clientesABB : NULL;
}

TClientesABB removerUltimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	TClientesABB cliente = clientesSucursalesLDE->final->clientesABB;
	if (clientesSucursalesLDE->inicio == clientesSucursalesLDE->final) {
		clientesSucursalesLDE->inicio = clientesSucursalesLDE->final = NULL;
	} else {
	clientesSucursalesLDE->final = clientesSucursalesLDE->final->anterior;
	clientesSucursalesLDE->final->siguiente = NULL;
	}

	return cliente;
}

TClientesABB removerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
	nat cantidadClientesABB = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);
	if (clientesSucursalesLDE->inicio == NULL || n <= 0 || n > (int)cantidadClientesABB) return NULL;
	TClientesABB cliente;
	if (clientesSucursalesLDE->inicio == clientesSucursalesLDE->final && n == 1) {
		cliente = clientesSucursalesLDE->inicio->clientesABB;
		clientesSucursalesLDE->inicio = clientesSucursalesLDE->final = NULL;
	} else {
		if (n == 1) {
			cliente = clientesSucursalesLDE->inicio->clientesABB;
			clientesSucursalesLDE->inicio = clientesSucursalesLDE->inicio->siguiente;
		} else {
			nodoClientesSucursalesLDE nodo = clientesSucursalesLDE->inicio;
			for (int contador = 1; contador < n && nodo != NULL; contador++) {
				nodo = nodo->siguiente;
			}
			if (nodo == NULL) return NULL;
			cliente = nodo->clientesABB;
			if (nodo->siguiente == NULL) {
				clientesSucursalesLDE->final = nodo->anterior;
				clientesSucursalesLDE->final->siguiente = NULL;
			} else {
				nodo->anterior->siguiente = nodo->siguiente;
				nodo->siguiente->anterior = nodo->anterior;
			}
		}
	}
	return cliente;
}

TCliente clienteMasRepetido(TClientesSucursalesLDE clientesSucursalesLDE) {
    struct clientes {
        int id;
        int cantidad;
        int idSucursal;
        clientes *siguiente;
    };

    if (clientesSucursalesLDE == NULL || clientesSucursalesLDE->inicio == NULL) {
        return NULL;
    }

    clientes *contadorClientes = NULL;

    nodoClientesSucursalesLDE nodo = clientesSucursalesLDE->inicio;
    while (nodo != NULL) {
        int cantidadClientes = cantidadClientesTClientesABB(nodo->clientesABB);

        for (int i = 1; i <= cantidadClientes; i++) {
			TCliente cliente = obtenerNesimoClienteTClientesABB(nodo->clientesABB, i);
			if (cliente == NULL) {
				continue;
			}
			int idCliente = idTCliente(cliente);

			clientes *tempClientes = contadorClientes, *anterior = NULL;
			while (tempClientes != NULL && tempClientes->id != idCliente) {
				anterior = tempClientes;
				tempClientes = tempClientes->siguiente;
			}

			if (tempClientes == NULL) {
				clientes *nuevoCliente = new clientes{idCliente, 1, nodo->idSucursal, NULL};
				if (anterior == NULL) {
					contadorClientes = nuevoCliente;
				} else {
					anterior->siguiente = nuevoCliente;
				}
			} else {
				tempClientes->cantidad++;
			}
		}
        nodo = nodo->siguiente;
    }
    int mayorContador = 0, mayorClienteID = 0, idSucursalQueEsta = 0;
    while (contadorClientes != NULL) {
        clientes *temp2 = contadorClientes;

        if (contadorClientes->cantidad > mayorContador || 
            (contadorClientes->cantidad == mayorContador && contadorClientes->id < mayorClienteID)) {
            mayorContador = contadorClientes->cantidad;
            mayorClienteID = contadorClientes->id;
            idSucursalQueEsta = contadorClientes->idSucursal;
        }

        contadorClientes = contadorClientes->siguiente;
        delete temp2;
    };

    nodoClientesSucursalesLDE buscandoCliente = clientesSucursalesLDE->inicio;
    while (buscandoCliente != NULL && buscandoCliente->idSucursal != idSucursalQueEsta) {
        buscandoCliente = buscandoCliente->siguiente;
    }
    if (buscandoCliente == NULL) {
        return NULL;
    }

    return obtenerTClienteTClientesABB(buscandoCliente->clientesABB, mayorClienteID);
}
