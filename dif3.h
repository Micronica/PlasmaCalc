#ifndef DIF3_H_INCLUDED
#define DIF3_H_INCLUDED

extern double dx;
extern double dy;
extern double dif;
extern double tau;

template<class T>
void dif3(T* h,T* g)
{
     for(int i=2; i<=194-1; i++)
     {
         for(int j=2; j<=258-1; j++)
         {
             h[i-1][j-1]=(g[i][j-1]+g[i-2][j-1]-2*g[i-1][j-1])*dif*tau/(dx*dx);
             h[i-1][j-1]+=(g[i-1][j]+g[i-1][j-2]-2*g[i-1][j-1])*dif*tau/(dy*dy);
         }
     }
}

#endif // DIF3_H_INCLUDED
