/*------------------------------------------------------------------------
 *   generate P-wave source at source nodes
 *
 *  ----------------------------------------------------------------------*/

#include "fd.h"
#include "data_structures.h"

void psource(int nt, Tensor3d *s,
float **  srcpos_loc, float ** signals, int nsrc, int * stype){


	extern float DX, DY, DZ;
	//extern float DT;
	extern int NT;

	int i, j, k, l;
	float amp=0.0;

        float ***sxx = s->xx;
        float ***syy = s->yy;
        float ***szz = s->zz;

	/* adding source wavelet to stress components 
	   (explosive source) at source points */


	for (l=1;l<=nsrc;l++) {
	    if(stype[l]==1){
		i=(int)srcpos_loc[1][l];
		j=(int)srcpos_loc[2][l];
		k=(int)srcpos_loc[3][l];

		//amp=signals[l][nt]; //unscaled explosive source
		//amp=(signals[l][nt])/(DX*DY*DZ); //scaled explosive source with respect to spatial discretization, seismic Moment = 1 Nm

		//scaled explosive source with respect to spatial and temporal discretization, seismic Moment = 1 Nm
		// -> additional temporal derivation
		if(nt==1){amp=signals[l][nt+1]/(2.0*DX*DY*DZ);}
		if((nt>1)&&(nt<NT)){amp=(signals[l][nt+1]-signals[l][nt-1])/(2.0*DX*DY*DZ);}
		if(nt==NT){amp=-signals[l][nt-1]/(2.0*DX*DY*DZ);}

		sxx[j][i][k]+=amp;
		syy[j][i][k]+=amp;
		szz[j][i][k]+=amp;
	    }
	}

}