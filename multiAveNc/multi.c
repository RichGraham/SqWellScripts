//Takes a list of nc histogram files, sums over all of them and outputs the normalised data


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEMPS 20
#define MAX_NC 500

int main(int argc, char *argv[])
{
  FILE *dataFile;
  char fileName[100];
  char customer[500];
  int nCol = 0, n=0;
  char *line;
  char *aveOutFileName, *inputFile;
  char entry[11];
  int tempNum=0, nc=0, ncCount=0;
  int inFileNumber;
  long int SN_OverTemps[MAX_NC]={0};// Sum of SN occupancies for all Temps at fixed NC



  long int TempNormConst[MAX_TEMPS]={0};// Sum over SN occupancues at fixed Temp for all NC (normalisation const)
  long int totalNorm=0;
 
  //====Check number of arguments====
  if(argc < 3){
    fprintf(stderr,"Produces nc distribution data averaged over several runs:\n");
    fprintf(stderr,"Usage: multiAveNc_sqW [list of nc histogram files] [average outputfile name]\n");
    fprintf(stderr,"Examp: multiAveNc_sqW outputFiles/128T.446B16j1-*/configs/Hist_100.dat data_Out.dat\n");
    exit(EXIT_FAILURE);
  }

  //====Assign arguments to named variables====
  aveOutFileName = argv[argc-1]; //The last argument is the outputfile name
  
  //******************Loop over input files *****************************
  for(inFileNumber = 1;  inFileNumber < argc-1 ; inFileNumber++){
    inputFile = argv[inFileNumber];

    //printf("Attempting file %s\n",inputFile);
  
    //====count the number of columns====
    if((dataFile = fopen(inputFile, "r")) == NULL) {
      printf("Multi.c: Error Opening File: %s\n", inputFile);
      exit(1);
    }
    nCol=0;
    n=0;
    line = fgets(customer, sizeof(customer), dataFile);
    while(sscanf(line, "%10s%n", entry, &n ) == 1 ) {
      nCol++;
      line += n;
    }
    //printf("%s has %d columns\n",inputFile,nCol);
    fclose(dataFile);
    
    
    
    //====Read in the data file====
    long int SN_Hist[MAX_TEMPS][MAX_NC]={0}; // SN_Hist[tempering level, energy level, SN order Param value]
    if((dataFile = fopen(inputFile, "r")) == NULL) {
      printf("Multi.c: Error Opening File: %s\n", inputFile);
      exit(1);
    }
    while(!feof(dataFile)){
      fscanf(dataFile,"%d",&nc);
      for(tempNum=1; tempNum<nCol ; tempNum++) fscanf(dataFile,"%ld", &SN_Hist[tempNum-1][nc]);
    }
    ncCount = nc;
    fclose(dataFile);
    
      
    
    //====Add each data point to the running total sum ====
    for(nc=0; nc<=ncCount ; nc++){
      for(tempNum=0;   tempNum < nCol-1 ; tempNum++){
	SN_OverTemps[nc] += SN_Hist[tempNum][nc];
      }
    }
   
  }
  //******************End loop over input files *****************************

  
  //====Compute the normalisation constant====
  for(nc=0;   nc < MAX_NC ; nc++) totalNorm += SN_OverTemps[nc];

  //====Write the data====
  dataFile = fopen(aveOutFileName, "w");
  for(nc=0; nc<MAX_NC ; nc++){
    if(totalNorm != 0 && SN_OverTemps[nc] != 0 )
      fprintf(dataFile,"%d %e\n",nc,SN_OverTemps[nc]/(1.0*totalNorm));
  }
  fclose(dataFile);
  return 0;
  
}

