#ifndef EDGEY_H_INCLUDED
#define EDGEY_H_INCLUDED
#include <iostream>
using namespace std;

template<class T>
void edgey(T*h)
{
    for(int i=0;i<194;i++)
    {
        h[i][0]=h[i][258-2];
        h[i][258-1]=h[i][1];
    }
}


#endif // EDGEY_H_INCLUDED
