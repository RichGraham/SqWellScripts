#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../MaxArraySizes.h"

int main(int argc, char *argv[] )
{

  //===Masterfile variables====
  int numTemps;
  char configsInput[400];
    char outputDir[400];
    //char weightFile[100];
  char VMDdir[400];
  char initCoords[400];
  char tempsFile[400];
  double LAMBDA;
  char moveSizesDir[400];
  FILE *inputPtr;
    double PHI_MAX;
  double ALPHA;
  double BETA;
  double GAMMA;
   int TEMP_INTEREST;
   int fileInput;
     char buffer[400];
     double sigma;
  int stretchStart;
  int stretchFinish;
 int Nmin;
  int Nmax;
  double kappa;
  double kappaRHS;
  double PRINT_INTERVAL;
  double PHI_UPDATE_INTERVAL;
  double UPDATE_INTERVAL;
  double SWAP_INTERVAL;
  int NUM_SWAPS;
  double NUM_SWAP_INTERVALS;
  double RESET_INTERVAL;
  double SMALL_ANGLE_MOVES;
  double REPTATION_MOVES;
  double CRANK_MOVES;
  double END_ROT_MOVES;
  double END_BRIDGE_MOVES;
    int update;
  double tolerance;

  
  //====Original variables
  char sdirTEMP[400], ddirTEMP[400], weightFileTEMP[400], weightFile[400], newWeightFileTEMP[400];
  int num_blocks;
  int N;
  int i, j, n;
  int startPoint;
  

  //====Check correct number of args and that input file exisits================
  if(argc != 4){
    printf("Usage: blockVary [input filename][int maxReadDepth][int startPoint]\n");
    exit(EXIT_FAILURE);
  }
 
  if((inputPtr = fopen(argv[1],"r")) == NULL){
    printf("Cannot open file %s\n",argv[1]);
    exit(EXIT_FAILURE);
  }


  //====Read in the input file====================================
  printf("Reading from the input file: %s\n", argv[1]);
  fscanf(inputPtr, "%d\n", &N);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &LAMBDA);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &TEMP_INTEREST);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &numTemps);
  fgets(buffer, 100, inputPtr);
  //fscanf(inputPtr, "%lf\n", &RAT);
  fscanf(inputPtr, "%s\n", tempsFile);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &fileInput);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n", configsInput);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n",moveSizesDir);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &PHI_MAX);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &ALPHA);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &BETA);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &GAMMA);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &sigma);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &stretchStart);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &stretchFinish);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &Nmin);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &Nmax);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &kappa);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &kappaRHS);
  fgets(buffer, 100, inputPtr);
  //fscanf(inputPtr, "%s\n", updateInfoDir);
  //fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &update);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &tolerance);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &PRINT_INTERVAL);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &PHI_UPDATE_INTERVAL);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &UPDATE_INTERVAL);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &SWAP_INTERVAL);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%d\n", &NUM_SWAPS);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &NUM_SWAP_INTERVALS);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%le\n", &RESET_INTERVAL);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &SMALL_ANGLE_MOVES);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &REPTATION_MOVES);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &CRANK_MOVES);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &END_ROT_MOVES);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%lf\n", &END_BRIDGE_MOVES);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n",outputDir);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n",weightFile);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n",VMDdir);
  fgets(buffer, 100, inputPtr);
  fscanf(inputPtr, "%s\n",initCoords);
  fgets(buffer, 100, inputPtr);
  fclose(inputPtr);
  
  num_blocks= atoi( argv[2]);
  startPoint= atoi( argv[3]);
  
  
  //printf("Enter the source directory: ");
  sprintf(sdirTEMP,"%s" ,outputDir);

  //N=5000;




  //====================Trim down the new weight file folder path====================
  //printf("Enter name for new weight file: weightFiles/");
  //scanf("%s",&newWeightFileTEMP);
  sprintf(newWeightFileTEMP,"%s",argv[1]);
  for(i = 1  ;   i <= 11   ;   i++)
    memmove(newWeightFileTEMP, newWeightFileTEMP+1, strlen(newWeightFileTEMP));
  //sprintf(newWeightFileTEMP,"outputFiles/weightFiles/%s",argv[1]);

  
  
  char sdir[400];
  char wdir[400];
  char ddir[400];
  char newWeightFile[400];
  char traceFile[400];
  sprintf(sdir,"%s/",sdirTEMP);
  sprintf(wdir,"%s/",sdirTEMP);
  // sprintf(ddir,"%s/",ddirTEMP);
  sprintf(ddir,"%s/collated/",sdirTEMP);
  sprintf(weightFile,"%s",weightFileTEMP);
  sprintf(newWeightFile,"outputFiles/weightFiles/%s",newWeightFileTEMP);

  printf("Source directory: %s\n", sdir);
  printf("Working directory: %s\n", wdir);
  printf("Number of blocks: %d\n", num_blocks);
  printf("Max no. of states: %d\n",MAX_NSQ);
  printf("Weight File for correction: %s\n",weightFile);
  printf("New weight file: %s\n",newWeightFile);
  printf("Number of Temps = %d\n",numTemps);

  
  if(numTemps >MAX_TEMPS){
    printf("********ERROR!\n NUM_TEMPS=%d is too large (>MAX_TEMPS).\n Edit MaxArraySizes.h and recompile\n",numTemps);
    exit(EXIT_FAILURE);
  }

  
  //return 0;

  long unsigned int occupanciesTEMP[MAX_TEMPS][MAX_NSQ]={0};
  long unsigned int occupancies[MAX_TEMPS][MAX_NSQ]={0};
  long unsigned int maxVal[MAX_TEMPS]={0};
  long unsigned int mode[MAX_TEMPS]={0};
  long  int minEl[MAX_TEMPS]={0};
  long  int maxEl[MAX_TEMPS]={0};
  long  int totalOcc[MAX_TEMPS]={0};
  long  int runningMean[MAX_TEMPS]={0};

  char occOutputFile[400];
  
  FILE  *weightPtr;
  FILE  *rangePtr[MAX_TEMPS];
  char blockFile[400];
  double bias[MAX_NSQ];


  //printf("Nmax=%d\n",N);

  //Need to open output files!!!

  for(j=0; j<numTemps ; j++){
    sprintf(occOutputFile,"%sRange%d.dat",sdir,j);
    printf("%s\n", occOutputFile);
    rangePtr[j] = fopen(occOutputFile,"w");
  }
  
  //====================Main loop========================
  for(n=startPoint;n<num_blocks;n++){
    sprintf(blockFile,"%soccupancies/block_%d.dat",sdir,n+1);
    if((inputPtr=fopen(blockFile,"r"))==NULL){
      printf("Cannot open file: %s\n", blockFile);
      printf("No more blocks to read from!\n");
      //exit(EXIT_FAILURE);
      break;
    }
    else{
      if (!(n % 100))
      printf("Reading from file: %s\n", blockFile);

    
    for(i = 0  ;   i <  MAX_TEMPS  ;   i++){
      //maxVal[i]=0;
      //mode[i]=0;
      minEl[i]=300000;
      maxEl[i]=0;
      totalOcc[i]=0;
      runningMean[i]=0;
    }
    

    
    i=0;
    for(i=0;i<MAX_NSQ;i++){
      for(j=0;j<numTemps;j++){
	fscanf(inputPtr,"%ld",&occupanciesTEMP[j][i]);
	
	totalOcc[j] += occupanciesTEMP[j][i];
	runningMean[j] += i* occupanciesTEMP[j][i];
	
	//printf("%d %d %ld\n",j,i, occupanciesTEMP[j][i]);
	if(   occupanciesTEMP[j][i]>10 &&  i > maxEl[j] ) maxEl[j]=i;
	if(  occupanciesTEMP[j][i]>10 &&   i < minEl[j] ) minEl[j]=i;
      }
    }

    for(j=0; j< numTemps ; j++){
      fprintf(rangePtr[j],"%d %f %ld %ld\n",n, runningMean[j]/(1.0*totalOcc[j]) ,  minEl[j] ,maxEl[j]);
      //printf("%d %d %d\n",n, minEl[j], maxEl[j]);
    }
    
    fclose(inputPtr);

    }
  }

  
  for(j=1; j<numTemps ; j++){
    fclose(rangePtr[j]);
  }

  /*

  long unsigned int totalSteps=0;
  double relOccupancies[MAX_TEMPS][MAX_NSQ];
  double FE[MAX_TEMPS][MAX_NSQ000];

  for(i=0;i<N;i++)
    totalSteps += occupancies[0][i];

  int  dummyInt;

  //printf("Nmax=%d\n",N);

  
 
  for(i=0;i<N;i++){
    for(j=0;  j<numTemps ;   j++){
      relOccupancies[j][i] = 1.0*occupancies[j][i]/(1.0*totalSteps);      
      if(relOccupancies[j][i]>0.0)
	FE[j][i] = -log(relOccupancies[j][i]/(exp(bias[i])));
	//FE[j][i] = -log(relOccupancies[j][i]);
      else
	FE[j][i] = FE[j][i-1];
      //printf("%d %d %f %f\n",j,i,relOccupancies[j][i], 	FE[j][i] );
    }
  }

  for(j=0; j<=numTemps; j++){
    for(i=1;i<N;i++)
      FE[j][i] -= FE[j][0];

    FE[j][0] = 0.0;
  }


  //printf("Num %d\n",numTemps);
  //printf("Number of Temps = %d\n",numTemps);
  
  FILE *occOutputPtr, *FEoutputPtr, *biasOutputPtr;
  char occOutputFile[400], FEoutputFile[400];
  for(j=0;j<numTemps;j++){
    //printf("%d\n",j);
    sprintf(occOutputFile,"%soccW_chain%d.dat",ddir,j);
    //printf("Occ out %s\n",occOutputFile );
    sprintf(FEoutputFile,"%sFE_chain%d.dat",ddir,j);
    //printf("FE out %s\n",FEoutputFile );
    occOutputPtr = fopen(occOutputFile,"w");
    FEoutputPtr = fopen(FEoutputFile, "w");


    if( j== TEMP_INTEREST){
      biasOutputPtr = fopen(newWeightFile,"w");
      for(i=0;i<N;i++)
	fprintf(biasOutputPtr,"%ld %f\n",i, FE[j][i]);
      fclose(biasOutputPtr);
    }

    for(i=0;i<N;i++){
      fprintf(occOutputPtr,"%ld %f\n", i, relOccupancies[j][i]);
      fprintf(FEoutputPtr,"%ld %f\n", i, FE[j][i]);
    }
    fclose(occOutputPtr);
    fclose(FEoutputPtr);

  }

  //printf("Finished!\n");
  */
  return 0;
}
