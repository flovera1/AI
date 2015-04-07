/* ----------------------------------------------------------------------------
  ex1.C
  mbwall 28jul94
  Copyright (c) 1995-1996  Massachusetts Institute of Technology

 DESCRIPTION:
   Example program for the SimpleGA class and 2DBinaryStringGenome class.
This program tries to fill the 2Dgenome with alternating 1s and 0s. 
  This example uses the default crossover (single point), default mutator
(uniform random bit flip), and default initializer (uniform random) for the
2D genome.
  Notice that one-point crossover is not necessarily the best kind of crossover
to use if you want to generate a 'good' genome with this kind of objective 
function.  But it does work.
---------------------------------------------------------------------------- */
#include <ga/GAIncGA.h>	// el GA a usar
#include <ga/GA1DBinStrGenome.h> // and the 2D binary string genome
#include <ga/std_stream.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>


#define cout STD_COUT

using std::ifstream;
using std::string;
using std::stringstream;

#define MAX_NUM_UNOS 31
#define LONGITUD_REGLA 33
#define PROB_ADD_ALTERNATIVE 0.1
#define PROG_DROP_CONDITION 0.5

#define NUM_VALORES_SALIDA 3
#define NUM_ATRIBUTOS_PRECONDICION 9
#define SIZE_SET 300
#define NUM_MAXIMO_REGLAS SIZE_SET

int set[SIZE_SET][NUM_ATRIBUTOS_PRECONDICION];
int target[SIZE_SET];
	
int atributos [NUM_ATRIBUTOS_PRECONDICION] =   {0,4,8,12,16,18,20,24,28};
int tamAtributos [NUM_ATRIBUTOS_PRECONDICION] ={4,4,4, 4, 2, 2, 4,4,2};

float Objective(GAGenome &);	// This is the declaration of our obj function.
float ObjectiveOR(GAGenome &);	// This is the declaration of our obj function.
				// The definition comes later in the file.
				
void inicializador(GAGenome & c);

float ObjectiveEncuesta(GAGenome &);
int GABILCrossover(const GAGenome& p1, 
				   const GAGenome& p2, 
				   GAGenome* c1, 
				   GAGenome* c2){

	//cout << "Entrando\n";
	
	GA1DBinaryStringGenome &mom=(GA1DBinaryStringGenome &)p1;
	GA1DBinaryStringGenome &dad=(GA1DBinaryStringGenome &)p2;
	int nc=0;
	
	unsigned int aM;
	unsigned int bM;
	
	unsigned int d1;
	unsigned int d2;
	
	do {
		
		aM = GARandomInt(0, mom.length());
		bM = GARandomInt(aM+1, mom.length()); 
		
		// Calcular las distancias.
		
		d1 = aM % LONGITUD_REGLA;
		d2 = bM % LONGITUD_REGLA;
	} while (d2<=d1);
	
	// Encontrar <a,b> para el papá.
	unsigned int aD;
	unsigned int bD;
	
	/*
	cout <<"Entro en el ciclo\n";
	cout << "aM: " << aM << "\n";
	cout << "bM: " << bM << "\n";
		
	cout << "D1: " << d1 << "\n";
	cout << "D2: " << d2 << "\n";
	cout << "Size: " << dad.size() << "\n"; */
	do {
		aD = GARandomInt(0, dad.length());
		bD = GARandomInt(aD+1, dad.length()); 
	} while (aD % LONGITUD_REGLA != d1 || bD % LONGITUD_REGLA != d2);
	//cout <<"Salio del ciclo\n";
	
	// Hacer a la hermana
	if(c1){
		GA1DBinaryStringGenome &sis=(GA1DBinaryStringGenome &)*c1;

		// Definir el tamaño.

		sis.length((aM) + (bD-aD) + (mom.length() -bM ));
		
		//cout << sis.GA1DBinaryStringGenome::size() << "\n";
		
		// Copiar los bits.
		
		sis.copy(mom,0,0,aM);
		sis.copy(dad,aM,aD,bD-aD);
		sis.copy(mom,bD-aD+aM,bM,mom.length() -bM );
		/*
void copy (const GA1DBinaryStringGenome &, unsigned int xdest, unsigned int xsrc, unsigned
int length) */

		nc ++;
	}
	// Hacer al hermano. 
	if(c2){
		GA1DBinaryStringGenome &bro=(GA1DBinaryStringGenome &)*c2;

		// Definir el tamaño.

		bro.length((aD) + (bM-aM) + (dad.length() -bD ));
		//cout << bro.GA1DBinaryStringGenome::size() << "\n";
		// Copiar los bits.
		
		bro.copy(dad,0,0,aD);
		bro.copy(mom,aD,aM,bM-aM);
		bro.copy(dad,bM-aM+aD,bD,dad.length() -bD );

		nc ++;
	}
	//cout << "Saliendo\n";
	return nc;
}

// El crossover con las extensiones implementadas.


int GABILCrossoverExtensions(const GAGenome& p1, 
				   const GAGenome& p2, 
				   GAGenome* c1, 
				   GAGenome* c2){
					   
	int nc = GABILCrossover(p1,p2,c1,c2);

	double p = GARandomDouble(0,1);
	int condition;
	
	if (c1){
		
		GA1DBinaryStringGenome &bro=(GA1DBinaryStringGenome &)*c2;
		
		if (p< PROB_ADD_ALTERNATIVE){
			bro.GA1DBinaryStringGenome::gene(GARandomInt(0, bro.GA1DBinaryStringGenome::length()),1);
		}
		
		p = rand()/RAND_MAX;
		
		if (p< PROG_DROP_CONDITION){
			condition = GARandomInt(0,NUM_ATRIBUTOS_PRECONDICION);
			for (int i = 0; i< tamAtributos[condition];i++){
				bro.GA1DBinaryStringGenome::gene(atributos[condition]+i,0);
			}
		}
	}
	
	if (c2){
		
		GA1DBinaryStringGenome &sis=(GA1DBinaryStringGenome &)*c2;
		
		if (p< PROB_ADD_ALTERNATIVE){
			sis.GA1DBinaryStringGenome::gene(GARandomInt(0, sis.GA1DBinaryStringGenome::length()),1);
		}
		
		p = rand()/RAND_MAX;

		if (p< PROG_DROP_CONDITION){
			
			condition = GARandomInt(0,NUM_ATRIBUTOS_PRECONDICION);
			for (int i = 0; i< tamAtributos[condition];i++){
				sis.GA1DBinaryStringGenome::gene(atributos[condition]+i,0);
			}
		}
	}
	return nc;
}					 
int
main(int argc, char **argv)
{
	 /* initialize random seed: */
		srand ( time(NULL) );
		
  cout << "Example 1\n\n";
  cout << "This program tries to fill a 2DBinaryStringGenome with\n";
  cout << "alternating 1s and 0s using a SimpleGA\n\n"; cout.flush();
  
  // Cargar los datos de entrada
  
 	ifstream myfile ("trainingset");
	string line;
	
	if (myfile.is_open())
	{
		const int numPos4 = 4;
		const int numPos2 = 3;
		
		int pos4[numPos4] = {1,2,6,7};
		int pos2[numPos2] = {4,5,8};
		
		for (int i = 0; i< SIZE_SET;i++)
		{
			getline (myfile,line);
			stringstream str(line);
			string s[10];
		
			str >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5] >> s[6]
				>> s[7] >> s[8] >> s[9];
				
			// Primera columna (edad):
			
			
			if (atoi(s[0].c_str())<=25){
				set[i][0]= 0;
			} else
			if (atoi(s[0].c_str())<=31){
				set[i][0]= 1;
			} else
			if (atoi(s[0].c_str())<=38){
				set[i][0]= 2;
			} else		
				set[i][0]= 3;

			if (atoi(s[3].c_str())<=1){
				set[i][3]= 0;
			} else
			if (atoi(s[3].c_str())<=2){
				set[i][3]= 1;
			} else
			if (atoi(s[3].c_str())<=4){
				set[i][3]= 2;
			} else		
				set[i][3]= 3;
						
			for (int j=0; j<numPos4;j++){
				set[i][pos4[j]]=  atoi(s[pos4[j]].c_str())-1;
			}	
			
			for (int j=0; j<numPos2;j++){
				set[i][pos2[j]]=  atoi(s[pos2[j]].c_str());
			}				
			
			target[i] = atoi(s[9].c_str())-1;
						
		}
		myfile.close();
	}
	else 
		cout << "Unable to open file"; 

// See if we've been given a seed to use (for testing purposes).  When you
// specify a random seed, the evolution will be exactly the same each time
// you use that seed number.

  for(int ii=1; ii<argc; ii++) {
    if(strcmp(argv[ii++],"seed") == 0) {
      GARandomSeed((unsigned int)atoi(argv[ii]));
    }
  }

bool useExtension = false; // True si se quieren usar las extensiones.
bool useRoulette = true; // True si se quiere usar roulette. Sino se usa UniformRanking.
bool changeReplacement = true;
// Declare variables for the GA parameters and set them to some default values.

  int width    = LONGITUD_REGLA*3; 
  int popsize  = 5000;
  float convergence = .7;
  int numGenConvTest =100000;
  float pmut   = 0.04;
  float pcross = 0.8;
  
// Now create the GA and run it.  First we create a genome of the type that
// we want to use in the GA.  The ga doesn't operate on this genome in the
// optimization - it just uses it to clone a population of genomes.

  GA1DBinaryStringGenome genome(width,ObjectiveEncuesta);

	if (useExtension){
		genome.crossover(GABILCrossoverExtensions);
	} else{
		genome.crossover(GABILCrossover);
	}
	
// Now that we have the genome, we create the genetic algorithm and set
// its parameters - number of generations, mutation probability, and crossover
// probability.  And finally we tell it to evolve itself.

  genome.initializer(inicializador);
	
  GAIncrementalGA ga(genome);
  
  ga.pConvergence(convergence);
  ga.nConvergence(numGenConvTest);
  ga.terminator(GAGeneticAlgorithm::TerminateUponConvergence);
  //ga.nGenerations(numGenConvTest);
  ga.populationSize(popsize);
  ga.pMutation(pmut);
  ga.pCrossover(pcross);
  
	if (useRoulette){
		cout <<"ROULETTE\n";
		GARouletteWheelSelector selector;
		ga.selector(selector);
	}else{
		cout <<"NO ROULETTE\n";
		GATournamentSelector selector;
		ga.selector(selector);
	}

	if (changeReplacement){
		cout <<"LOS PADRES\n";
		ga.replacement(GAIncrementalGA::PARENT);
	} else {
		cout << "LOS PEORES\n";
		ga.replacement(GAIncrementalGA::WORST);
	}

	cout <<"EVOLUCION\n";
  ga.evolve();

// Now we print out the best genome that the GA found.

  cout << "The GA found:\n" << ga.statistics().bestIndividual() << "\n";
  cout << "Score:\n" << ga.statistics().bestIndividual().score() << "\n";
	
// That's it!
  return 0;
}
 

void inicializador(GAGenome & c){
	GA1DBinaryStringGenome & genome = (GA1DBinaryStringGenome &)c;
	GA1DBinaryStringGenome::UniformInitializer(c);
	
	int cantReglas = genome.length()/LONGITUD_REGLA;

	int num;
  
	for (int i =0; i < cantReglas;i++){
		genome.unset(i*LONGITUD_REGLA+(LONGITUD_REGLA-NUM_VALORES_SALIDA),3);
		num = rand() % 3;
		genome.gene(i*LONGITUD_REGLA+num+(LONGITUD_REGLA-NUM_VALORES_SALIDA),1);
		
	}

}

// This is the objective function.  All it does is check for alternating 0s and
// 1s.  If the gene is odd and contains a 1, the fitness is incremented by 1.
// If the gene is even and contains a 0, the fitness is incremented by 1.  No
// penalties are assigned. 
//   We have to do the cast because a plain, generic GAGenome doesn't have 
// the members that a GA2DBinaryStringGenome has.  And it's ok to cast it
// because we know that we will only get GA2DBinaryStringGenomes and
// nothing else.

float
ObjectiveEncuesta(GAGenome& g) {
GA1DBinaryStringGenome & genome = (GA1DBinaryStringGenome &)g;
	//cout << "\n" << genome << "\n";
	
	bool reglaPara[NUM_VALORES_SALIDA] = {false,false,false};
	bool regla[NUM_VALORES_SALIDA] = {false,false,false};
		
	// Penalizacion por ser muy grande.

	int cantReglas = genome.length()/LONGITUD_REGLA;
	
	if (cantReglas>=NUM_MAXIMO_REGLAS){
//		cout << "NUM REGLAS MUY ALTO \n";
		return 0;
	}
	// Penalización si hay reglas invalidas
	
	// Recorrer reglas
	int cont;
	int numUnos;
	for (int i = 0 ; i < cantReglas; i++){
		cont = 0;
		numUnos = 0;
		
		for (int j = 0; j<LONGITUD_REGLA; j++){
			if (genome.gene(j+(i*LONGITUD_REGLA))==1){
				numUnos++;
			}	
			
		}
		
		if (numUnos>MAX_NUM_UNOS){
			return 0;
		}	
		for (int j = 0; j<NUM_VALORES_SALIDA;j++){
			if (genome.gene(j+(LONGITUD_REGLA - NUM_VALORES_SALIDA)+(i*LONGITUD_REGLA))==1){
				cont ++;
				regla[j]=true;
			}	
		}
		if (cont !=1 || (!regla[0]||!regla[1]||!regla[2]))
			return 0;
	}
	
	float score=0.0;
	
	int numRegla;
	bool match;
	// Recorrer todo el conjunto de entrenamiento
	for (int i =0; i<SIZE_SET; i++){
		
		numRegla =0;
		
		// Recorrer cada atributo.
		for (int j = 0; j< NUM_ATRIBUTOS_PRECONDICION; j++){
			// Recorrer cada regla del individuo que se está probando.
			for (int k = numRegla; k< cantReglas; k++){	
				
				if (genome.gene((set[i][j]+atributos[j])+(k*LONGITUD_REGLA))==0){
					numRegla=k+1;
					j=0;
				} else{			
					numRegla =k;
				}
			}	
			
		}
		
		// Hizo match la precondicion.
		
		match = false;
		
		if (numRegla<cantReglas){
			int bitsPostcondicion=-1;
			
			for (int j = 0; j<NUM_VALORES_SALIDA;j++){
				if (genome.gene(j+(LONGITUD_REGLA - NUM_VALORES_SALIDA)+(numRegla*LONGITUD_REGLA))==1){
					bitsPostcondicion = j;
					break;
				}
			}  
			
			// Clasifica para una regla
			if (bitsPostcondicion==target[i]){
				// Hizo match.
				score +=1;
				//cout << bitsPostcondicion << " ";
				reglaPara[bitsPostcondicion]=true;
			}
			

		}
		
	}
	int numClases=0;
	for (int j = 0; j<NUM_VALORES_SALIDA;j++){
		if (reglaPara[j]){
			numClases++;		
		}
	}	
	
	return ((score/SIZE_SET)*(score/SIZE_SET));
}
