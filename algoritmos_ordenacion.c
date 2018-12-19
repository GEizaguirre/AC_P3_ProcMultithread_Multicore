#include <stdbool.h>
#include <stdio.h>
#include "funciones_complementarias.h"



/**********************************************************
ordSeleccion
Método para ordenar un vector pasado como parámetro median-
te una ordenación por selección (no recursiva).
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void ordSeleccio (int v[], int nelem) {
    int i, j, pos, minim;
    for (i=0; i<nelem-1; i++) {
        minim=v[i];
        pos=i;
        for (j=i+1; j<nelem; j++) {
            if (v[j]<minim) {
                minim = v[j];
                pos=j;
            }
        } /* fpor */
        v[pos]=v[i];
        v[i]=minim;
    } /* fpor*/
} /* facción */

/**********************************************************
ordBombolla
Método para ordenar un vector pasado como parámetro median-
te una ordenación burbuja (no recursiva).
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void ordBombolla(int v[], int nelem) {
    int i=1, j;
    bool ordenat;
    ordenat=false;
    while (!ordenat) {
        ordenat=true;
        for (j=0; j<nelem-i; j++) {
            if (v[j]>v[j+1]) {
                ordenat=false;
                swap(v, j, j+1);
            } /* fsi */
        } /* fpor */
        i++;
    } /* fmientras */
} /* facción */

/**********************************************************
ordSeleccion
Método para ordenar un vector pasado como parámetro median-
te una ordenación por inserción (no recursiva).
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void ordInsercio(int v[], int nelem) {
    int i, j, aux;
    for (i=1; i<nelem; i++) {
        aux=v[i];
        j=i-1;
        while (j>=0 && aux<v[j]) {
            v[j+1] = v[j];
            j--;
        } /* fmientras */
        v[j+1]=aux;
    } /* fpor */
} /* facción */

/**********************************************************
QuickSort
Método para ordenar un vector pasado como parámetro median-
te una ordenación por Quicksort (recursiva). Utiliza el
primer elemento del vector procesado como pivote.
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void QuickSort(int v[], int ini, int fin){
    //declaración de variable snecesarias para el ordenamiento.
    int mig, left, right, pivote;

    if (ini == fin)
    { // Caso directo
        return;
    }
    else // if ini<fin - caso recursivo
    {
        // pivote= primer elemento del vector en el rango del quicksort
        pivote = v[ini];
        // ordenamos el resto de elementos en base al pivote
        left=ini+1;
        right=fin;
        while(left!=right){
                // Desplazamiento de valores según el pivote.
                while ((left<right)&&((v[left]>pivote)&&(v[right]>pivote))) right--;
                while ((left<right)&&((v[left]<pivote)&&(v[right]<pivote))) left++;
                if ((v[left]>pivote)&&(v[right]<=pivote)){
                        // intercambio de valores.
                        swap(v, left, right);
                        left++;
                         if(left<right) right--;
                }
                else{
                       if (left<right) left++;
                }
        }
        // intercambio con el pivote.
        if (v[left]<pivote){
            swap(v, left, ini);
        }
        mig=left-1;
        // llamada recursiva a quicksort
        if (mig>=0) QuickSort(v,ini,mig);
        QuickSort(v,mig+1,fin);
    }
}

/**********************************************************
MergeSort
Método para ordenar un vector pasado como parámetro median-
te una ordenación por MergeSort (recursiva). Divide el vector por
la mitad de forma recursiva y hace el merge de forma ordenada y
recursiva de los subvectores generados.
Parámetros:
v: vector de int a ordenar.
ini: indice de inicio del vector o subvector de v
ini: indice final del vector o subvector de v
**********************************************************/

void MergeSort(int v[], int ini, int fin){

   int mig;

   if (ini<fin){

       mig=(fin+ini)/2;             //Obtener posición del medio
       MergeSort(v, ini, mig);   //Ordenar subvectores de forma recursiva
       MergeSort(v, mig+1, fin);

       int vOrd[fin-ini]; //Vector axuiliar
       int i=0;           // Indice del vector auxiliar
       int p1=ini;        //punteros para realizar el merge
       int p2=mig+1;

       while (p1<=mig && p2<=fin){                 //Minetras los 2 vectores tengan elementos
	    if (v[p1]<v[p2])  vOrd[i++]=v[p1++];    //Comparar elementos y añadir el  siguente más pequeño
           else vOrd[i++]=v[p2++];
      }

      while (p1<=mig) vOrd[i++]=v[p1++];          //Añadir los elementos sobrantes ya ordenados
      while (p2<=fin) vOrd[i++]=v[p2++];

      int j=0;
      for (i=ini; i<=fin; i++ )     v[i]=vOrd[j++];  // Sobreescribir vector original

    }

}

/**********************************************************
QuickSortRandomPivote
Método para ordenar un vector pasado como parámetro median-
te una ordenación por Quicksort (recursiva). Utiliza un
elemento aleatorio del vector procesado como pivote.
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void QuickSortRandomPivote(int v[], int ini, int fin){
    int mig, left, right, pivote, pos_pivote;

    if (ini == fin)
    { // Caso directo
        return;
    }
    else // if ini<fin - caso recursivo
    {
        pos_pivote=numeroAleatorio(ini, fin);
        pivote=v[pos_pivote];
        left=ini;
        right=fin;
        while(left!=right){
                // Desplazamiento de valores según el pivote.
                while ((left<right)&&((v[left]>pivote)&&(v[right]>pivote))) right--;
                while ((left<right)&&((v[left]<=pivote)&&(v[right]<pivote))) left++;
                if ((v[left]>pivote)&&(v[right]<=pivote)){
                        // intercambio de valores.
                        swap(v, left, right);
                        left++;
                         if(left<right) right--;
                }
                else{
                       if (left<right) left++;
                }
        }
        // intercambio con el pivote.
        if (v[left]<pivote){
            swap(v, left, pos_pivote);
        }
        mig=left-1;
        // llamada recursiva a quicksort
        if (mig>=0) QuickSortRandomPivote(v,ini,mig);
        if (mig<fin) QuickSortRandomPivote(v,mig+1,fin);
    }
}

/**********************************************************
QuickSortPivoteCentrado
Método para ordenar un vector pasado como parámetro median-
te una ordenación por Quicksort (recursiva). Utiliza el
elemento del centro del vector procesado como pivote.
Parámetros:
v: vector de int a ordenar.
nelem: número de elementos en el vector.
**********************************************************/
void QuickSortPivoteCentrado(int v[], int ini, int fin){
    int mig, left, right, pivote, pos_pivote;

    if (ini == fin)
    { // Caso directo
        return;
    }
    else // if ini<fin - caso recursivo
    {
        pos_pivote=((fin-ini)/2)+ini;
        pivote=v[pos_pivote];
        left=ini;
        right=fin;
        while(left!=right){
                // Desplazamiento de valores según el pivote.
                //imprimirVector(v, 8);
                //printf("\n");
                while ((left<right)&&((v[left]>pivote)&&(v[right]>pivote))) right--;
                while ((left<right)&&((v[left]<=pivote)&&(v[right]<pivote))) left++;
                if ((v[left]>pivote)&&(v[right]<=pivote)){
                        // intercambio de valores.
                        swap(v, left, right);
                        left++;
                         if(left<right) right--;
                }
                else{
                       if (left<right) left++;
                }
        }
        // intercambio con el pivote.
        if (v[left]<pivote){
            swap(v, left, pos_pivote);
        }
        mig=left-1;
        // llamada recursiva a quicksort
        if (mig>=0) QuickSortPivoteCentrado(v,ini,mig);
        if (mig<fin) QuickSortPivoteCentrado(v,mig+1,fin);
    }
}

