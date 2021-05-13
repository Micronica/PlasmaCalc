#ifndef MEAN_H_INCLUDED
#define MEAN_H_INCLUDED

template<class T>
void mean(double* h1,T* g)
{
     for(int i=1; i<=194; i++)
    {
        h1[i-1]=0.0;
        for(int j=1; j<=258; j++) { h1[i-1]+=g[i-1][j-1]; }
        h1[i-1]/=258.;
    }
}

#endif // MEAN_H_INCLUDED
