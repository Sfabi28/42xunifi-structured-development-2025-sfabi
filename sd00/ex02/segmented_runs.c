
#include "segmented_runs.h"

int count_segments(const int *arr, int size)
{
    int count = 0;
    int seg_length = 0;
    int prev = 0;
    bool in_segment = false;

    for (int i = 0; i < size; i++) {
        if (arr[i] != -1) {
            if (!in_segment) {
                seg_length = 1;
                in_segment = true;
            } else if (arr[i] == prev + 1) {
                seg_length++;
            } else {
                
                if (seg_length >= 3)
                    count++;
                seg_length = 1;
            }
            prev = arr[i];
        } else {
            if (in_segment && seg_length >= 3)
                count++;
            in_segment = false;
            seg_length = 0;
        }
    }
    
    if (in_segment && seg_length >= 3)
        count++;

    return count;
}

