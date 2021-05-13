#ifndef GIVEVALUE_H
#define GIVEVALUE_H

#include "edgex.h"
#include "edgey.h"

template<class T>
void givevalue(double*h1,T*g,T*k)//
{
    for(int i=1; i<=194; i++)
    {
       for(int j=1; j<=258; j++)
       {
           k[i-1][j-1]=g[i-1][j-1]-h1[i-1];
        }
    }
    edgex(k);
    edgey(k);
}
#endif // GIVEVALUE_H
