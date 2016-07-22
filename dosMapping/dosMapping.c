/*
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NLARGE 500


int main(int argc, char *argv[] )
{
  double Tin, Tout;
  double lnDOS;
  double FEout[NLARGE+1]={0.0};
  int currentFilePoints;
  int dum,i;
  int zero_point;
  float FEin;

  FILE *inFilePtr;


  // check correct number of arguments
  if(argc !=5){
    printf("Usage: dosMapping [int zero point][[double T_in] [linput filename] [double T_out]\n");
    exit(EXIT_FAILURE);
  }


  
  zero_point = atoi( argv[1] );
  Tin   = atof(argv[2]);
  Tout = atof(argv[4]);
  fprintf(stderr,"T_in, T_out=%f, %f\n",Tin,Tout);

  


  
  
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
      lnDOS = -FEin - dum/Tin;
      FEout[dum] = Tin/Tout  *  (-Tout/Tin * lnDOS - dum/Tin);
      //printf("%d %f %f\n",dum, FEin,FEout[dum]);
    }

    currentFilePoints--;
    fprintf(stderr,"Found %d points\n",dum+1);

    for(i=0; i<=dum; i++) printf("%d %f\n",i, FEout[i] - FEout[zero_point]);

  return 0;
  
}
