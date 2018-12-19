#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define N 50000000
#define INI 1000

int p[N/10];
int thread_number;    // número de threads (pasado como argumento)
int nn;
int pp;        // posición actual de la lista de primos
pthread_mutex_t lock;
int num;

void * calculate_primes ( void * argument ); 
void QuickSort(int v[], int ini, int fin);

int main (int na, char * arg[])
{
    int i;
    int result_code;

    assert ( na == 3 );    // número de argumentos
    nn = atoi ( arg[1] );    // limita máximo
    thread_number = atoi ( arg[2] );    // número de threads    

    pthread_t threads [thread_number];
    int thread_args [thread_number];

    printf ("Tots els primers fins a %d\n",nn);

    p[0] = 2;        // precondiciones
    p[1] = 3;
    pp = 2;        // posición actual de la lista de primos
    num = 5;

    while ( pp < INI )
    {
        for ( i = 1; p[i] * p[i] <= num; i++ )
            if ( num % p[i] == 0 ) break;
        if ( p[i] * p[i] > num ) p[pp++] = num;
        num += 2;
    }

    // probar con PTHREAD_MUTEX_INITIALIZER; 
    if ( pthread_mutex_init ( &lock, NULL ) != 0 )
    {
        printf ( "\n mutex init failed\n" );
        return -1;
    }

    for ( i = 0; i < thread_number; i++ ) 
    {
        printf("Creant thread: %d.\n", i);
        thread_args[i] = i+1;
        result_code = pthread_create(&threads[i], NULL, calculate_primes, &thread_args[i]);
        assert(!result_code);
    }

    //wait for each thread to complete
    for ( i = 0; i < thread_number; i++) 
    {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        printf("Acabat thread: %d.\n", i);
    }

    pthread_mutex_destroy ( &lock );

    //QuickSort (p, INI, pp);
    printf ( "Hi ha %d primers\n", pp - 1 );
    printf ( "L'ultim primer trobat %d\n", p[pp - 1] );
    //for ( i = 0; i<pp; i++ ) printf ( "%d - ", p[i] );
    exit ( 0 );
}

void * calculate_primes ( void * argument ) 
{
    int div, i, num_own;

    for (num_own = num + ( (* ( ( int * ) argument )) - 1) * 2; num_own < nn; num_own += thread_number * 2)
    {
        div = 0;    // No divisible
        for ( i = 1; p[i] * p[i] <= num_own && !div; i++ )
            div = !( num_own % p[i] );
        if ( !div ) 
        {
        p[pp] = num_own;
        pthread_mutex_lock ( &lock );
        pp++;
        pthread_mutex_unlock ( &lock );
        }
    }
}

void QuickSort(int v[], int ini, int fin){
    //declaración de variable snecesarias para el ordenamiento.
    int mig, left, right, pivote, aux;

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
                        aux=v[left];
                    v[left]=v[right];
                    v[right]=aux;
                        left++;
                         if(left<right) right--;
                }
                else{
                       if (left<right) left++;
                }
        }
        // intercambio con el pivote.
        if (v[left]<pivote){
            aux=v[left];
            v[left]=v[right];
            v[right]=aux;
        }
        mig=left-1;
        // llamada recursiva a quicksort
        if (mig>=0) QuickSort(v,ini,mig);
        QuickSort(v,mig+1,fin);
    }
}



