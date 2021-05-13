#ifndef SVE_H_INCLUDED
#define SVE_H_INCLUDED

#include "edgey.h"
#include <iostream>

using namespace std;

extern  double phi[194][258];
extern  double dx1p5;
extern  double dy1p5;
extern  double vx[194][258];
extern  double vy[194][258];

void sve()
{
    for(int i=1; i<194-1; i++)
    {
        for(int j=1; j<258-1; j++)
        {
            vy[i][j]=dx1p5*(phi[i+1][j]-phi[i-1][j]);
         }
    }
    for(int i=0; i<194-1; i++)
    {
        for(int j=1; j<258-1; j++)
        {
            vx[i][j]=dy1p5*(phi[i][j-1]-phi[i][j+1]);
        }
    }
    edgey(vy);
    edgey(vx);
}

#endif // SVE_H_INCLUDED
