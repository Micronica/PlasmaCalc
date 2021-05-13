#include <iostream>
#include <cmath>
#include "edgey.h"
#include "edgex.h"
#include "transvalue.h"

using namespace std;

extern  double phi[194][258];
extern  double wi[194][258];
extern double dx;
extern double dy;
double eds=1e-10;
double zeros[194][258]={};

void Poisson()
{
    int counts=0;
    double w=1.97175;
    double maxdu,du;
    double temp[194][258];
    maxdu=0.0;
    do
    {
        for(int j=1;j<257;j++)
        {

            for(int i=1;i<193;i++)
            {
                temp[i][j]=phi[i][j];
                phi[i][j]=(1-w)*phi[i][j];
                phi[i][j]+=(w/2.)*(dx*dx*(phi[i][j-1]+phi[i][j+1])+dy*dy*(phi[i-1][j]+phi[i+1][j])-dx*dx*dy*dy*wi[i][j])/(dx*dx+dy*dy);
                du=temp[i][j]-phi[i][j];
                du=abs(du);
                if(du>maxdu)maxdu=du;
            }
        }
        counts++;
        edgey(phi);
    } while ((maxdu>eds)&&counts<3000);
    edgex(phi);
}
