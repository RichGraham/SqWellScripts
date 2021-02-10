/*
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../MaxArraySizes.h"

#define NLARGE 2500


int main(int argc, char *argv[] )
{
  double Tin, Tout;
  double lnDOS[NLARGE+1]={0.0};
  static double PncE[NLARGE+1][NLARGE+1]={0.0};
  double Pnc[NLARGE+1]={0.0};

  double FEout[NLARGE+1]={0.0};
  int currentFilePoints;
  int eMax,eMax2, ncMax;
  int dum,i, nc, eCurrent;
  int zero_point;
  float FEin;
  char nc_filename[100];
  char *landscapeIn_filename;
  char *folderIn_name;
  char outFileName[200];

   struct stat st;

  FILE *inFilePtr;
  FILE *outFilePtr;
  


  // check correct number of arguments
  if(argc !=6){
    printf("Usage: OP_mapping [int zero point][double T_in][landscape input filename][P(nc|E) input folder][double T_out]\n");
    printf("Exmpl: OP_mapping 0 0.446 128T.446B16j1.list.dat.FE.stc 128T.446B16k0/ 0.446\n");
    exit(EXIT_FAILURE);
  }

  //====Assign arguments====
  zero_point = atoi( argv[1] );
  Tin   = atof(argv[2]);
  landscapeIn_filename = argv[3];
  folderIn_name = argv[4];
  Tout = atof(argv[5]);
  fprintf(stderr,"T_in, T_out=%f, %f\n",Tin,Tout);


  
  
  
  if( ( inFilePtr = fopen( landscapeIn_filename , "r") ) == NULL ){
    fprintf(stderr,"Can't open file %s\n",landscapeIn_filename);
    exit(EXIT_FAILURE);
  }
  
  fprintf(stderr,"File open %s\n", landscapeIn_filename );
  
  //__________________Read data and count file length_________________________
  // Read landscape file 
  currentFilePoints=0;
  while( !feof( inFilePtr )){
    fscanf(inFilePtr,"%d %f",&dum, &FEin);
    currentFilePoints++;
    lnDOS[dum] = -FEin - dum/Tin;
    FEout[dum] = Tin/Tout  *  (-Tout/Tin * lnDOS[dum] - dum/Tin);
    //printf("%d %f %f\n",dum, FEin,FEout[dum]);
  }
  fclose( inFilePtr);
  currentFilePoints--;
  eMax = dum;
  fprintf(stderr,"Found %d points\n",dum+1);

  // Read P(nc|E) files
  eMax2=-100;
  i=0;
  ncMax = -100;
  while(eMax2 < -5){
    i++;
    sprintf( nc_filename,"%s/BatchAve_%d.dat",folderIn_name,i); 
    if( ( inFilePtr = fopen( nc_filename , "r") ) == NULL ){
      eMax2 = i-1;
      fprintf(stderr,"Read files 1...%d\n",eMax2);
      fprintf(stderr,"Can't open file %s\n",nc_filename);
    }else{
      //fprintf(stderr,"File %s open\n",nc_filename);
      //Check the file is not empty
      stat(nc_filename, &st);
      if( st.st_size > 0 ){
	while( !feof( inFilePtr )){
	  fscanf(inFilePtr,"%d %f",&nc, &FEin);
	  //fprintf(stderr,"%d %d %e\n",i, nc , FEin);	
	  PncE[nc][i]= FEin;
	}
	if(nc > ncMax ) ncMax = nc;
      }
      fclose( inFilePtr);
    }
  }
  fprintf(stderr,"Maximum OP value found = %d\n",ncMax);

  
  // Print P(nc|E) data for debugging
  //for(nc = 0  ;   nc <=  ncMax  ;   nc++)  fprintf(stderr,"%d %e\n",nc , PncE[nc][431]);
  

  //====Compute P(nc,T)===== (un-normalised)
  for(nc =0; nc <= ncMax ; nc++){
    for( eCurrent=0; eCurrent <= eMax ; eCurrent++)
      Pnc[nc]  +=  exp(lnDOS[eCurrent] + (1.0*eCurrent)/Tout) * PncE[nc][eCurrent];
  }
  
  
  
  //_____Write FE data to file___________

  sprintf(outFileName,"%s%s%s.nc",argv[5],folderIn_name,landscapeIn_filename);
  fprintf(stderr,"Trying to openfile %s\n",outFileName);
  if( ( outFilePtr = fopen( outFileName , "w") ) == NULL ){
    fprintf(stderr,"Can't open output file\n");
    exit(EXIT_FAILURE);
  }else{
    for(nc=0; nc<=ncMax; nc++){
      if( Pnc[nc] > 0 ){
	fprintf(outFilePtr,"%d %e\n",nc, -log(Pnc[nc]/Pnc[zero_point])  );
      }
    }
    fclose(outFilePtr);
    fprintf(stderr,"Wrote to file %s\n",outFileName);
  }

				 
  return 0;
  
}
