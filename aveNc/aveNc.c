#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEMPS 20
#define MAX_NC 500

int main(int argc, char *argv[])
{
  FILE *dataFile;
  char fileName[100];
  char customer[100];
  int nCol = 0, n=0;
  char *line;
  char *tempsOutFileName, *aveOutFileName;
  char entry[11];
  int tempNum=0, nc=0, ncCount=0;


  long int SN_Hist[MAX_TEMPS][MAX_NC]={0}; // SN_Hist[tempering level, energy level, SN order Param value]
  long int SN_OverTemps[MAX_NC]={0};// Sum of SN occupancies for all Temps at fixed NC
  long int TempNormConst[MAX_TEMPS]={0};// Sum over SN occupancues at fixed Temp for all NC (normalisation const)
  long int totalNorm=0;
 
  //====Check number of arguments====
  if(argc != 4){
    fprintf(stderr,"Produces nc distribution data:\n");
    fprintf(stderr,"Takes nc output data, normalises and produces average over all tempering levels\n");
    fprintf(stderr,"Usage: aveNC_sqW [nc histogram file] [temps output file][overall average outputfile]\n");
    fprintf(stderr,"Examp: aveNC_sqW Hist_100.dat \n");
    exit(EXIT_FAILURE);
  }

  //====Assign arguments to named variables====
  tempsOutFileName = argv[2];
  aveOutFileName = argv[3];
  

  //====count the number of columns====
  if((dataFile = fopen(argv[1], "r")) == NULL) {
    printf("Error Opening File: %s.\n", argv[1]);
    exit(1);
  }
  printf("File open %s\n",argv[1]);
  line = fgets(customer, sizeof(customer), dataFile);
  while(sscanf(line, "%10s%n", entry, &n ) == 1 ) {
    nCol++;
    line += n;
    }
  printf("Line 1 has %d column entries\n",nCol);
  fclose(dataFile);

  //====Read in the data file====
  if((dataFile = fopen(argv[1], "r")) == NULL) {
    printf("Error Opening File: %s.\n", argv[1]);
    exit(1);
  }
  while(!feof(dataFile)){
    fscanf(dataFile,"%d",&nc);
    for(tempNum=1; tempNum<nCol ; tempNum++) fscanf(dataFile,"%ld", &SN_Hist[tempNum-1][nc]);
  }
  ncCount = nc;
  fclose(dataFile);

  /*
  for(nc=0; nc<=ncCount ; nc++){
    printf("%d ",nc);
    for(tempNum=1; tempNum<nCol ; tempNum++) printf("%ld ",SN_Hist[tempNum-1][nc]);
    printf("\n");
  }
  */

  //====Sum each column, then each row then the total normalisation====
  for(nc=0; nc<=ncCount ; nc++){
    for(tempNum=0;   tempNum < nCol-1 ; tempNum++){
      SN_OverTemps[nc] += SN_Hist[tempNum][nc];
    }
  }
  for(tempNum=0;   tempNum < nCol-1 ; tempNum++){
    for(nc=0; nc<=ncCount ; nc++){
      TempNormConst[tempNum] += SN_Hist[tempNum][nc];
    }
  }
  for(tempNum=0;   tempNum < nCol-1 ; tempNum++) totalNorm +=  TempNormConst[tempNum];

  //====Write the data====
  dataFile = fopen(tempsOutFileName, "w");
  for(nc=0; nc<=ncCount ; nc++){
    fprintf(dataFile,"%d ",nc);
    for(tempNum=0;   tempNum < nCol-1 ; tempNum++){
      if(TempNormConst[tempNum] != 0)
	fprintf(dataFile,"%f ",SN_Hist[tempNum][nc]/(1.0*TempNormConst[tempNum]));
      else
	fprintf(dataFile,"0.0 ");
    }
    fprintf(dataFile,"\n");
  }
  fclose(dataFile);

  //====Write the data====
  dataFile = fopen(aveOutFileName, "w");
  for(nc=0; nc<=ncCount ; nc++){
    if(totalNorm != 0 && SN_OverTemps[nc] != 0 )
      fprintf(dataFile,"%d %f\n",nc,SN_OverTemps[nc]/(1.0*totalNorm));
  }
  fclose(dataFile);
  return 0;
  
}

