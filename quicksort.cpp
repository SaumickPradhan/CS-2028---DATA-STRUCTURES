#include "sortingalgos.h"
#include <iostream>

#include <cstdlib>

using namespace std;

int dopart(int *array,int start,int end)
{
    int pv=array[end];

    int pvind=start;

    int i,z;

    for(i=start;i<end;i++)
    {
        if(array[i]<=pv)
        {
            z=array[i];

            array[i]=array[pvind];

            array[pvind]=z;

            pvind++;
        }

    }

    z=array[end];

    array[end]=array[pvind];

    array[pvind]=z;

    return pvind;

}

void QuickSort(int *array,int start,int end)
{
    if(start<end)
    {

        int partindex=dopart(array,start,end);

        QuickSort(array,start,partindex-1);

        QuickSort(array,partindex+1,end);

    }

}
