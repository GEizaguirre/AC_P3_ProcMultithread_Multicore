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
int initial_values;

void * calculate_primes ( void * argument );
void calculate_margins ( int argument , int * low, int * up);
void ordSeleccio (int v[], int nelem); 
void MergeSort(int v[], int ini, int fin);
int insertSorted(int nelem, int key);

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

	initial_values = INI;
    if ( ( ( num - 2 ) * ( num - 2 ) ) < nn )
    {
	printf (" S'ha fet una ampliació dels calculs inicials ");
        char sufficent_ampliation = 0;
	while (!sufficent_ampliation)
	{
		for ( ; ( ( p[i] * p[i] <= num ) && ( !sufficent_ampliation ) ); i++ )
		if ( num % p[i] == 0 ) break;
		if ( p[i] * p[i] > num )
		{
			p[pp++] = num;
			initial_values ++;
			if ( ( ( num - 2 ) * ( num - 2 ) ) >= nn ) sufficent_ampliation = 1;
		}
		num += 2;
	}
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

    printf ( "Hi ha %d primers\n", pp - 1 );
    printf ( "L'ultim primer trobat %d\n", p[pp - 1] );
    //for ( i = 0; i<pp; i++ ) printf ( "%d - ", p[i] );
    exit ( 0 );
}

void * calculate_primes ( void * argument ) 
{
    int p_own [initial_values]; 
    int div, i, num_own;

    num_own = num + ( (* ( ( int * ) argument )) - 1) * 2;

    for (i = 0; i < initial_values; i++) 
    {
        p_own [i] = p[i];
    }

    for (; num_own < nn; num_own += thread_number * 2)
    {
        div = 0;    // No divisible
        for ( i = 1; p_own[i] * p_own[i] <= num_own && !div; i++ )
            div = !( num_own % p_own[i] );
        if ( !div ) 
        {
		pthread_mutex_lock ( &lock );
		p[pp++] = num_own;
		pthread_mutex_unlock ( &lock );
        }
    }
}

void ord_selection (int v[], int start, int end) 
{
    int i, j, pos, minim;
    for ( i = start; i < end; i++ ) 
    {
        minim = v[i];
        pos = i;
        for ( j = i + 1; j < end; j++ ) 
        {
            if ( v[j] < minim ) 
            {
                minim = v[j];
                pos = j;
            }
        } /* fpor */
        v[pos] = v[i];
        v[i] = minim;
    } /* fpor*/
} /* facción */


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
 
int insertSorted(int nelem, int data) 
{   
    int i; 
    for (i = nelem - 1; ( i >= 0  && p[i] > data); i-- ) 
       p[i + 1] = p[i]; 
  
    p[ i + 1 ] = data; 
  
    return ( nelem + 1 ); 
} 
