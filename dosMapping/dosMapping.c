/*
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../MaxArraySizes.h"


int main(int argc, char *argv[] )
{
  double Tin, Tout;
  double lnDOS[MAX_NSQ+1]={0.0};

  double FEout[MAX_NSQ+1]={0.0};
  int currentFilePoints;
  int dum,i;
  int zero_point;
  float FEin;
  char invT_filename[100];

  FILE *inFilePtr;
  FILE *outFilePtr;
  


  // check correct number of arguments
  if(argc !=5){
    printf("Usage: dosMapping [int zero point][double T_in] [input filename] [double T_out]\n");
    printf("Example:dosMapping 200 0.446 128T.446B16j0.list.dat 0.5 > N128T0.5fromT0.446.dat\n");
    exit(EXIT_FAILURE);
  }


  
  zero_point = atoi( argv[1] );
  Tin   = atof(argv[2]);
  Tout = atof(argv[4]);
  fprintf(stderr,"T_in, T_out=%f, %f\n",Tin,Tout);

  sprintf(invT_filename,"%s.invT",argv[3]);

  
  
  
  if( ( inFilePtr = fopen( argv[3] , "r") ) == NULL ){
    fprintf(stderr,"Can't open file %s\n",argv[3]);
    exit(EXIT_FAILURE);
  }
  
  fprintf(stderr,"File open %s\n", argv[4] );
  
  //__________________Read data and count file length_________________________
  currentFilePoints=0;
  while( !feof( inFilePtr )){
    fscanf(inFilePtr,"%d %f",&dum, &FEin);
    currentFilePoints++;
    lnDOS[dum] = -FEin - dum/Tin;
    FEout[dum] = Tin/Tout  *  (-Tout/Tin * lnDOS[dum] - dum/Tin);
    //printf("%d %f %f\n",dum, FEin,FEout[dum]);
  }
  
  currentFilePoints--;
  fprintf(stderr,"Found %d points\n",dum+1);
  


  
  //_____Write FE data to std output___________  
  for(i=0; i<=dum; i++) printf("%d %f\n",i, FEout[i] - FEout[zero_point]);


  //_____Write 1/T data to output file___________
  outFilePtr = fopen( invT_filename , "w");
  for(i=1; i<=dum-1; i++)  fprintf(outFilePtr,"%d %f\n",i ,  -(lnDOS[i+1]-lnDOS[i-1])/2.0);
  fclose( outFilePtr);
  fprintf(stderr,"Written inverse Temp data to: %s\n",invT_filename);
				 
  return 0;
  
}
