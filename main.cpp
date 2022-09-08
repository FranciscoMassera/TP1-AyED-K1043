#include <iostream>
#include <fstream>

using namespace std;

const int dclie{8}; //Dimension codigo de cliente
const int dtprod{5}; //Dimension codigo de tipo de producto

void lista1(float pesos[][dtprod], string clientes[], string tipoprod [] ) //Punto 1
{
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;
    for (int i = 0; i < dclie; i++){
        cout << clientes[i] << ":";
        for (int j = 0; j < dtprod; j++){
        if(pesos[i][j] > 13000){
                cout << tipoprod[j] << ", ";
                }
    }
    cout << endl;
    }
}

int maximo(float pesos[][dtprod]) //Punto 2. Encontrar el cliente con mayor tipos de produtos con mas de 13000kg
{
    int ntde{};//Cantidad de tipo de entregas
    int pmax{};//Posicion maxima de tipo de entregas
    for (int i = 0; i < dclie; ++i){
            int aux{};//Auxiliar
        for (int j = 0; j < dtprod; ++j){
        if(pesos[i][j] > 13000){
                aux++;
                }
        if(aux > ntde){
            ntde = aux;
            pmax = i;
        }
        }
    }
        return pmax;

}

void lista2(float distancia[][dtprod], int pmax, string tipoprodaux[]) //Punto 2. Ordeno ascendente y al auxiliar igual
                                                                       //que la matriz con las distancias
{
	int i, pos, imax;

	for (pos = dtprod - 1; pos >= 0 ; pos--) {
		imax = pos;
		for (i = dtprod - 1 ; i > 0  ; i--)
			if (distancia[pmax][i] < distancia[pmax][imax])
				imax = i;
		swap(distancia[pmax][pos], distancia[pmax][imax]);
		swap(tipoprodaux[pos], tipoprodaux[imax]);
	}
}

int main()
{
    int iclie, itprod;//Codigo de cliente y tipo de producto
    int pmax; //Posicion maxima de cliente con mas tipo de productos mayores a 13000kg
    float peso, dist;
    float pesos[dclie][dtprod]{}; //Matriz con codigo de cleinte por
                                  //codigo de tipo de producto y pesos
    float distancia[dclie][dtprod]{};
    string ntpdmax; //Punto 3. Nombre del tipo de producto con mayor km recorridos
    int cantentregas[dtprod]; //Punto 3
    int pmaxtdp;//Punto 3. Posicion del tipo de producto con mayor km recorridos

    ifstream datos;
    datos.open("Datos.txt");
    if (!datos){
        cout << "Error al abrir el arhivo" << endl;
        return 1;
    };
    while (datos >> iclie >> itprod >> peso >> dist) {
        pesos[iclie][itprod] += peso;
        distancia[iclie][itprod] += dist;
        cantentregas[itprod]++;
    }
    datos.close();

    ifstream nombres;
    nombres.open("Nombres.txt");
    if (!nombres){
        cout << "Error al abrir el arhivo" << endl;
        return 1;
    }
    string nomcl, nomtp;
    string clientes [dclie]{};//Vector nombre de clientes
    string tipoprod [dtprod]{};//Vector nombre de tipo de productos
    string tipoprodaux [dtprod]{};//Punto 2. Vector nombre de tipo de productos auxiliar
    for (int i = 0; i < dclie && nombres >> clientes[i]; ++i);
	for (int i = 0; i < dtprod && nombres >> tipoprod[i]; ++i);
	for(int i = 0; i < dtprod; i++)//Copia del vector auxiliar
        tipoprodaux[i]=tipoprod[i];
	nombres.close();

	cout << "Punto 1:" << endl;
    lista1(pesos, clientes, tipoprod);//Punto 1
    cout << endl;

    cout << "Punto 2:" << endl;//Punto 2
    pmax=maximo(pesos);
    lista2(distancia, pmax, tipoprodaux);
    cout << "Listado de Km recorridos por tipo de producto (ascendente): " << endl;
    for(int j = 0; j < dtprod; ++j){
        cout << tipoprodaux[j] << ": "<< distancia[pmax][j] << endl;
    }
    cout << endl;

    cout << "Punto 3:" << endl; //Punto 3
    ntpdmax=tipoprodaux[dtprod-1];//Como se que esta ordenado ascendentemente el mayor es el ultimo
    int i;
    for(int i = 0; i < dtprod; i++){//Busco el codigo del tipo de producto en el original
    if (tipoprod[i]==ntpdmax){
    pmaxtdp=i;
    }
    }
    cout << pmaxtdp << endl;
    int cantent; //Cantidad de entregas para el tipo de producto
    cantent=cantentregas[pmaxtdp];
    cout << "Cantidad de entregas para el tipo de producto " << tipoprod[pmaxtdp] << " : "  << cantent << endl;
    }
