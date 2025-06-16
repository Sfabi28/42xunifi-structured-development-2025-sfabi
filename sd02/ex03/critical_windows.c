
#include "critical_windows.h"

static int case1(const int *readings, int index)
{
    int nbr = 0;

    for (int i = index; i < index + 5; i++)
    {
        if (readings[i] >= 70) {
            nbr++;
        }
    }
    
    return nbr >= 3;
}


static int case2(const int *readings, int index)
{
    for (int i = index; i < index + 5; i++)
    {
        if (readings[i] > 150) {
            return 0;
        }
    }
    
    return 1;
}

static int case3(const int *readings, int index)
{
    int avarage = 0;
    for (int i = index; i < index + 5; i++)
    {
        avarage += readings[i];
    }
    avarage /= 5;

    return avarage >= 90;
}


int count_critical_windows(const int *readings, int size)
{
    int count = 0;
    
    for (int i = 0; i < size - 4; i++) {
        if (case1(readings, i) && case2(readings, i) && case3(readings, i)) {
            count++;
        }
    }
    
    return count;
}
