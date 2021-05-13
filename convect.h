#ifndef CONVECT_H_INCLUDED
#define CONVECT_H_INCLUDED

extern  double vx[194][258];
extern  double vy[194][258];
extern double dx;
extern double dy;
extern double tau;
extern double arho;

template<class T>
void convect(T*h,T*g)
{
     for(int i=2; i<=194-1; i++)
     {
         for(int j=2; j<=258-1; j++)
         {
            h[i-1][j-1]=(vx[i][j-1]*g[i][j-1]-vx[i-2][j-1]*g[i-2][j-1])*arho*tau/(2.*dx);
            h[i-1][j-1]+=(vy[i-1][j]*g[i-1][j]-vy[i-1][j-2]*g[i-1][j-2])*arho*tau/(2.*dy);
         }
     }
}


#endif // CONVECT_H_INCLUDED
