/* Driver for routine mglin */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define NSTEP 4
#define JMAX 33

int main(void)
{
	int i,j,midl=JMAX/2+1;
	double **f,**u;

	f=dmatrix(1,JMAX,1,JMAX);
	u=dmatrix(1,JMAX,1,JMAX);
	for (i=1;i<=JMAX;i++)
		for (j=1;j<=JMAX;j++)
			u[i][j]=0.0;
	u[midl][midl]=2.0;
	mglin(u,JMAX,2);
	printf("MGLIN solution:\n");
	for (i=1;i<=JMAX;i+=NSTEP) {
		for (j=1;j<=JMAX;j+=NSTEP) printf("%8.4f",u[i][j]);
		printf("\n");
	}
	printf("\n Test that solution satisfies difference equations:\n");
	for (i=NSTEP+1;i<JMAX;i+=NSTEP) {
		for (j=NSTEP+1;j<JMAX;j+=NSTEP)
			f[i][j]=u[i+1][j]+u[i-1][j]+u[i][j+1]+u[i][j-1]
				-4.0*u[i][j];
		printf("%7s"," ");
		for (j=NSTEP+1;j<JMAX;j+=NSTEP) printf("%8.4f",f[i][j]*(JMAX-1)*(JMAX-1));
		printf("\n");
	}
	free_dmatrix(u,1,JMAX,1,JMAX);
	free_dmatrix(f,1,JMAX,1,JMAX);
	return 0;
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software 7&X*. */
