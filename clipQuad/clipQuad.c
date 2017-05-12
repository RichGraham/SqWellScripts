#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_LENGTH 3000


int main(int argc, char *argv[] )
{


  
  //====Original variables
  char  newWeightFileTEMP[400];
  int num_blocks;
  int N;
  int i, j, n, lower, upper;
  int  dummyInt;
  double bias[MAX_LENGTH]={8000.0};
  FILE *inputPtr, *weightPtr, *outPtr;
  double edgeBias;
  double upperBias, lowerBias;
  double kappa, kappa_low, kappa_upper;
  int kMin;


  //====Check correct number of args and that input file exisits================
  if(argc != 6){
    printf("Attempts to create a biasing function that's localised around the density of states'bottle-neck'\n");
    printf("Takes an estimate of the free energy landscape and subtracts a quadratic with centre and strength specified below\n");
    printf("Also flattens the biasing function at upper and lower limit to avoid exploring extreme edges.\n");
    printf("Usage: clipQuad [weight filename][int lower limit ][int upper limit][int quadratic minimum][float edge biasing value]\n");
    printf("Example: clipQuad N40Test.list.dat 0 110 75 2\n");
    exit(EXIT_FAILURE);
  }

  lower = atoi( argv[2]);
  upper = atoi( argv[3]);
  kMin = atoi( argv[4]);
  edgeBias = atof ( argv[5]);


  printf("lower %d, upper %d, kMin %d, edge %f\n",lower, upper, kMin, edgeBias);

  if( lower > upper || lower>kMin || kMin> upper){
    printf("ERROR!!!:  Check ordering of lower, upper and middle!!!!!!\n");
    return 0;
  }

  //compute kappa based on desired biasing at edge of region
  kappa_low = edgeBias/(lower-kMin)/(lower-kMin);
  kappa_upper = edgeBias/(upper-kMin)/(upper-kMin);
  kappa = MIN( kappa_upper, kappa_low);

  //Choose maximum point to write based on upper
  N = 1.5 * upper;
  if( N > MAX_LENGTH){
    printf("ERROR!!!:  Attempting to write beyond MAX_LENGTH. N=%d vs %d!!!!!!\n",N,MAX_LENGTH);
    printf("Increase MAX_LENGTH in source code and recompile\n");
    return 0;
  }
  
  sprintf(newWeightFileTEMP,"%s",argv[1]);

  
  memcpy(newWeightFileTEMP, argv[1], strlen(argv[1]) - 4);
  newWeightFileTEMP[strlen(argv[1]) - 4] = '\0';

  sprintf(newWeightFileTEMP,"%sc%dk%.2e.dat",newWeightFileTEMP,kMin,kappa);
  
  printf("%s %s\n",argv[1],newWeightFileTEMP);

  //first pass to determine the biasing at edges
  if((weightPtr=fopen(argv[1],"r"))==NULL)
    printf("Cannot open weight file: %s\n", argv[1]);
  else{
    for(i=0;i<N;i++){
      fscanf(weightPtr,"%d %lf",&dummyInt, &bias[i]);
      
    }
  }
  fclose(weightPtr);

  
  //second pass to write the data
  if((weightPtr=fopen(argv[1],"r"))==NULL)
    printf("Cannot open weight file: %s\n", argv[1]);
  else{
    outPtr = fopen( newWeightFileTEMP, "w");
    for(i=0;i<N;i++){
      fscanf(weightPtr,"%d %lf",&dummyInt, &bias[i]);
      if( dummyInt > upper) bias[i]=bias[upper];
      if( dummyInt < lower) bias[i]=bias[lower];
      //printf("%d %f\n",i,bias[i]-kappa*(i-kMin)*(i-kMin));
      fprintf(outPtr,"%d %f\n",i,bias[i]-kappa*(i-kMin)*(i-kMin));
    }
  }
  fclose(weightPtr);

  /*
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
  
  
  //printf("Enter the source directory: ");
  sprintf(sdirTEMP,"%s" ,outputDir);

  N=500;




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
  printf("Max no. of states: %d\n",N);
  printf("Weight File for correction: %s\n",weightFile);
  printf("New weight file: %s\n",newWeightFile);
  printf("Number of Temps = %d\n",numTemps);

  //return 0;

  long unsigned int occupanciesTEMP[18][1000]={0};
  long unsigned int occupancies[18][1000]={0};
  long unsigned int maxVal[18]={0};
  long unsigned int mode[18]={0};
  long  int minEl[18]={0};
  long  int maxEl[18]={0};

  char occOutputFile[400];
  
  FILE  *weightPtr;
  FILE  *rangePtr[18];
  char blockFile[400];
  double bias[1000];


  //printf("Nmax=%d\n",N);

  //Need to open output files!!!

  for(j=0; j<numTemps ; j++){
    sprintf(occOutputFile,"%sRange%d.dat",sdir,j);
    printf("%s\n", occOutputFile);
    rangePtr[j] = fopen(occOutputFile,"w");
  }
  
  //====================Main loop========================
  for(n=0;n<num_blocks;n++){
    sprintf(blockFile,"%soccupancies/block_%d.dat",sdir,n+1);
    if((inputPtr=fopen(blockFile,"r"))==NULL){
      printf("Cannot open file: %s\n", blockFile);
      printf("No more blocks to read from!\n");
      //exit(EXIT_FAILURE);
      break;
    }
    else{
      printf("Reading from file: %s\n", blockFile);

    
    for(i = 0  ;   i <  18  ;   i++){
      //maxVal[i]=0;
      //mode[i]=0;
      minEl[i]=300000;
      maxEl[i]=0;
    }
    

    
    i=0;
    for(i=0;i<N;i++){
      for(j=0;j<numTemps;j++){
	fscanf(inputPtr,"%ld",&occupanciesTEMP[j][i]);
	//printf("%d %d %ld\n",j,i, occupanciesTEMP[j][i]);
	if(   occupanciesTEMP[j][i]>100 &&  i > maxEl[j] ) maxEl[j]=i;
	if(  occupanciesTEMP[j][i]>100 &&   i < minEl[j] ) minEl[j]=i;
      }
    }

    for(j=0; j< numTemps ; j++){
      fprintf(rangePtr[j],"%d %f %d %d\n",n, minEl[j] + 0.5*(maxEl[j]-minEl[j]) ,  minEl[j] ,maxEl[j]);
      //printf("%d %d %d\n",n, minEl[j], maxEl[j]);
    }
    
    fclose(inputPtr);

    }
  }

  
  for(j=1; j<numTemps ; j++){
    fclose(rangePtr[j]);
  }
  */
  /*

  long unsigned int totalSteps=0;
  double relOccupancies[18][1000];
  double FE[18][1000];

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
