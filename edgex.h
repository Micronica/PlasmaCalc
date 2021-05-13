#ifndef EDGEX_H_INCLUDED
#define EDGEX_H_INCLUDED

#include <iostream>

using namespace std;

template<class T>
void edgex(T* h)
{
   for(int j=0; j<258; j++)
   {
       h[0][j]=0;
       h[194-1][j]=0;
   }
}

#endif // EDGEX_H_INCLUDED
