#ifndef TRANSVALUE_H_INCLUDED
#define TRANSVALUE_H_INCLUDED

template<class T>
void transvalue(T* a,T* b)
{
    for(int i=1; i<=194; i++)
    {
        for(int j=1; j<=258; j++)
        {
            a[i-1][j-1]=b[i-1][j-1];
         }
     }
}

#endif // TRANSVALUE_H_INCLUDED
