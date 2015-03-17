/**
* @Fernando Lovera :)
* @Caracas Friday 13 March 2015
* Genetic Algorithm(algoritmo genetico), which handles the
* individual process and creation of a population
*/
#define POBLACION 100
#define LONG_COD 20
#define LIMITE -5.12
#define PROB_CRUCE 0.3
#define PROB_MUTACION 0.001
#define INTERVALO 10.24/pow(2,LONG_COD/2)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct {
    int genotipo[LONG_COD];
    double aptitud;
} Individual;
void decoder (double *, double *, int *);
double fitness (double, double);
int generateBinary (void);
Individual generateIndividual (void);
Individual * generatePopulation (void);
Individual * tornamentSelection(Individual * pob);
void sonMutation (Individual *);
void crossSelection (Individual *);
Individual elite(Individual *);
void AG();
void printPopulation (Individual *);
void imprimeGenotipo(Individual);
void generateGraphic(void);

/** 
 *---------------------------------------
 * decode the genotype(array with 0's and 1's) and generate the 
 * Converting two numbers in his decimal equivalent.
 * @param x        : space to store the first part of the number(genome).
 * @param y        : space to store the second part of the number(genome).
 * @param genotipo : genome with the genetic information of the individual.
 */
void decoder (double * x, double * y, int * genotype){
    int i;
    *x = 0.0; 
    *y = 0.0; 
    // first decimal computed.
    for(i = 0; i < LONG_COD/2; i++){
        *x += genotype[i] * pow(2, (LONG_COD/2)-(i+1));
    }
    *x = (*x) * INTERVALO + LIMITE;
    //second decimal computed.
    for(;i<LONG_COD;i++){
        *y += genotype[i] * pow(2, LONG_COD-(i+1));
    }
    *y = (*y) * INTERVALO + LIMITE;
}
/**
 *-----------------------------------
 * Fitness function the received two values the represent an individual
 */
double fitness (double p1, double p2){
    return pow(p1,2) + pow(p2,2);
}
/**
 *------------------------------------
 * returns an int value between 0 and 1. 
 * individuals will be generated with a random genome at the beginning.
 */
int generateBinary (void) {
    if (1 + (int) (10.0*rand()/(RAND_MAX+1.0)) > 5)
        return 1;
    else
        return 0;
}
/**
 *-----------------------------------------------
 * Process that generates an individual using random values, 
 * first creates the bits chain using generateBinary and then evaluate the aptitude of the individual
 * using the decoder function and then obtain its fitness
 */
Individual generateIndividual (void){
    Individual ind;
    int i;
    double x, y;
    //fill the genotype
    for (i=0; i < LONG_COD; i++){
        ind.genotipo[i] = generateBinary();
    }
    //decode the fitness function and the aptitude
    decoder(&x, &y, ind.genotipo);
    ind.aptitud         = fitness(x,y);
    return ind;
}
/**   
 *-----------------------------------------------
 * procedure that generates the population with the quantity of individuals.
 * To generate the each individual generateIndividual is used. 
 * at the end a pointer to the individual is used.
 */
Individual * generatePopulation(void){
    Individual * population;
    int i;
    population       = (Individual *) malloc(sizeof(Individual)*POBLACION);
    for(i = 0;i < POBLACION;i++)
        population[i] = generateIndividual();
    return population;
}
/** 
 *---------------------------------------------
 * procedure that creates a new vector of individuals which will contain the 
 * selected individuals for the crossover. The selection is done by the individual
 * with better aptitude. 
 * 
 */
Individual * tornamentSelection (Individual * population){
    Individual candidato_a, candidato_b;
    int i;
    Individual * selection = (Individual *) malloc (sizeof(Individual)*POBLACION);
    for (i=0; i < POBLACION-1; i++){
        candidato_a       = population[(int) (((double) POBLACION)*rand()/(RAND_MAX+1.0))];
        candidato_b       = population[(int) (((double) POBLACION)*rand()/(RAND_MAX+1.0))];
        if (candidato_a.aptitud < candidato_b.aptitud)
            selection[i]  = candidato_a;
        else
            selection[i]  = candidato_b;
    }
    return selection;
}
/**
 *------------------------------------------
 * it applies the the mutation depending on the probability PROB_MUTACION
 * recieves the vector of individuals in which the first two must be sons
 * corresponding to the cross. The genotype of each individual is search through
 * calculating the probability that the bit mute and chaining it in the corresponding case.
 */
 void sonMutation (Individual * sons){//sons is a population! :D
    int i, j;
 
    for(i=0; i<2; i++)
        for(j=0; j<LONG_COD; j++)
            if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
            {
                if(sons[i].genotipo[j])
                    sons[i].genotipo[j]  = 0;
                else sons[i].genotipo[j] = 1;
            }
}
 
/**
 *------------------------------------------------
 * procedure that cross two individuals. The selection is ordered 
 * then the individuals are crossed two by two. In case that the 
 * individuals are crossed, a point of cross is made and the vectors
 * are interchanged.
 */
void crossSelection (Individual * selection){
    int i, j, punto, aux;
    double x, y;
    for(i = 0; i < POBLACION-1; i += 2){
        if((double) rand()/(RAND_MAX+1.0) < PROB_CRUCE){
            punto = (int) (((double) LONG_COD)*rand()/(RAND_MAX+1.0));
 
            for(j = punto; j<LONG_COD; j++){
                aux                        = selection[i].genotipo[j];
                selection[i].genotipo[j]   = selection[i+1].genotipo[j];
                selection[i+1].genotipo[j] = aux;
            }
 
            sonMutation(&selection[i]);
 
            decoder(&x, &y, selection[i].genotipo);
            selection[i].aptitud = fitness(x,y);
 
            decoder(&x, &y, selection[i+1].genotipo);
            selection[i+1].aptitud = fitness(x,y);
        }
    }
}
 
/**
 *------------------------------------------------
 * function that returns the best individual of a population. This
 * individual is the one with best fitness, which means the lowest aptitude.
 */
Individual elite (Individual * population){
    int i;
    Individual best = population[0];
 
    for(i=0; i<POBLACION; i++)
        if(best.aptitud > population[i].aptitud)
            best = population[i];
 
    return best;
}
 
/**
 *------------------------------------------------------
 * Algorithm:
 * 1) Generate the population.
 * 2) Select the individuals to cross.
 * 3) Cross the individuals(mutation is included in this step).
 * 4) Include the best of the last generation in the new generation.
 * 5) Repeat.
 */
void AG (void){
    Individual * selection, * population = generatePopulation();
    Individual best;
    int generacion                       = 0;
    double x, y;
    do{
        selection              = tornamentSelection(population);
        crossSelection(selection);
        printf("Population after cross over: \n");
		printPopulation(selection);
		printf("Generacion: ");
		printf("%d", generacion);
        selection[POBLACION-1] = elite(population);
        free(population);
        population             = selection;
        generacion++;
    } while (elite(population).aptitud > pow(10,-2));
 
    best = elite(population);
    free(population);
    decoder(&x, &y, best.genotipo);
    printf (" - En el punto (%.5f, %.5f)\n", x, y);
    printf (" - Su fenotipo es %.5f\n", best.aptitud);
    printf (" - Es la generacion numero %i\n", generacion);
}
/**   
 *-----------------------------------------------------
 * print in the standard output related to the population passed as an argument
 */
void printPopulation (Individual * pob){
    int i;
    double x, y;
 
    for(i=0;i<POBLACION;i++)
    {
        decoder(&x, &y, pob[i].genotipo);
        printf ("Individual NUMERO %i \t", i+1);
        printf ("(%f,", x);
        printf (" %f)", y);
        printf ("\tAptitud = %.20f\n", pob[i].aptitud);
    }
}
 
/* PROC imprimeGenotipo (Individual x)                           DEV (void)
 * MODIFICA nada
 * EFECTO esta funcion se encarga de imprimir por pantalla el genotipo asociado a
 *  un Individual que se pasa como argumento. recorre el genotipo por medio de
 *  un bucle for y no necesita funciones auxiliares 
 */ 
void imprimeGenotipo (Individual x){
    int i;
    for(i=0; i<LONG_COD; i++){
        printf ("%i  ", x.genotipo[i]);
    }
    printf ("\n");
}

/**
 *---------------------------------------------------
 * function used to generate files with points used in GNUPLOT 
 * to draw. 
 * media variable used to calculate the aptitude every 10 generations
 */
void generateGraphic(){
    FILE *f;
    int generacion, j;
    double media;
    Individual *selection, *poblacion = generatePopulation();
    f=fopen("Puntos.dat", "at");
    fprintf (f, "\n0 %.40f\n", elite(poblacion).aptitud);
    for(generacion = 1; generacion<2000;){
        media      = 0;
        for(j=0; j<10; j++, generacion++){
            selection              = tornamentSelection(poblacion);
            crossSelection(selection);
            selection[POBLACION-1] = elite(poblacion);
            media                 += elite(poblacion).aptitud;
            free(poblacion);
            poblacion              = selection;
        }
        media                     /= j;
        fprintf (f, "%i %.40f\n", generacion, media);
    }
 
    fprintf (f, "\n\n");
    fclose(f);
}

int main(){
 
    //srand( (unsigned int) time(NULL) );
    AG();
    generateGraphic();
    return 0;
}