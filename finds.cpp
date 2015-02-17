/*
 *  Find-S Machine Exercise
 *  Template created by Tristan M. Basa
 *  Department of Computer Science
 *  University of the Philippines, Diliman
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ILEN  50   //Instance Length
#define ALEN  10   //Attribute Length
#define DELIMITERS "<,>"

char *generate_example(char *example) {
	char sky[3][ALEN]={"Sunny","Cloudy","Rainy"};
	char airtemp[2][ALEN]={"Warm","Cold"};
	char humidity[2][ALEN]={"Normal","High"};
	char wind[2][ALEN]={"Strong","Weak"};
	char water[2][ALEN]={"Warm","Cool"};
	char forecast[2][ALEN]={"Same","Change"};

	sprintf(example,"<%s,%s,%s,%s,%s,%s>",sky[rand()%3],airtemp[rand()%2],humidity[rand()%2],wind[rand()%2],water[rand()%2],forecast[rand()%2]);
	
	return example;
}

int consistent(char *targcon,char *instance) {
	int i,ret=1;
	char attr[6][ALEN],*token,*temp;
	
	temp=(char*)malloc(sizeof(char)*ILEN);
    strcpy(temp,targcon);
	sprintf(attr[0],"%s",strtok(temp,DELIMITERS));
	for (i=1; i<6; i++) 
		sprintf(attr[i],"%s",strtok(NULL,DELIMITERS));
	
	strcpy(temp,instance);
    token=strtok(temp,DELIMITERS);
	for (i=0; ret && i<6; i++) {
		if (strcmp(attr[i],token) && strcmp(attr[i],"?"))
			ret=0;
		token=strtok(NULL,DELIMITERS);
	}
	free(temp);
	
	return ret;
}

char *FindS(char *hypothesis,char *example,char *target) {
	int i;
	
	char attr[6][ALEN], hattr[6][ALEN], *temp, *hyp;
	temp=(char*)malloc(sizeof(char)*ILEN);
	hyp=(char*)malloc(sizeof(char)*ILEN);
	
	if(consistent(target, example)){
		strcpy(temp, example);
		sprintf(attr[0],"%s",strtok(temp,DELIMITERS));
		for (i=1; i<6; i++) 
		sprintf(attr[i],"%s",strtok(NULL,DELIMITERS));
		
		strcpy(hyp, hypothesis);
		sprintf(hattr[0],"%s",strtok(hyp,DELIMITERS));
		for (i=1; i<6; i++)
		sprintf(hattr[i],"%s",strtok(NULL,DELIMITERS));
		
		for(i=0; i<6; i++){
			if(strcmp(hattr[i], "0") == 0) strcpy(hattr[i], attr[i]);
			else if(strcmp(hattr[i], attr[i])) strcpy(hattr[i], "?");
		}
		
		
		sprintf(hypothesis, "<%s,%s,%s,%s,%s,%s>",hattr[0], hattr[1], hattr[2], hattr[3], hattr[4], hattr[5]);
	}
	
	free(temp); free(hyp);
	return hypothesis;
}


int main(int argc,char *argv[]) 
{
	int i,n,epoch=20;
	double sum=0;
    char *hypothesis,*example,target[ILEN]={"<Sunny,Warm,?,?,?,?>"};
	
	srand(time(0));
	
    if (argc>1)
        epoch=atoi(argv[1]);
    
    hypothesis=(char*)malloc(sizeof(char)*ILEN);
	example=(char*)malloc(sizeof(char)*ILEN);
	for (i=0; i<epoch; i++) {
		n=0;
	    strcpy(hypothesis,"<0,0,0,0,0,0>");		
		do {
			example=generate_example(example);
			hypothesis=FindS(hypothesis,example,target);
			n++;
		} while (strcmp(hypothesis,target));
		sum=sum+n;
		printf("Experiment #%i: %i examples\n",i+1,n);
	}
	free(hypothesis);
    free(example);
	
	printf("\nAverage number of examples before convergence: %.2lf\n\n",sum/epoch);

	return 0;
}