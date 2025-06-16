
#include "segmented_runs.h"

int count_segments(const int *arr, int size)
{
    int count = 0;
    int seg_length = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] != -1) {
            if (seg_length == 0)
                seg_length = 1;
            else if (arr[i] == arr[i - 1] + 1)
                seg_length++;
            else {
                if (seg_length > 2)
                  count++;
                seg_length = 1;
            }
        } else {
            if (seg_length > 0) {
                if (seg_length > 2)
                    count++;
                seg_length = 0;
            }
        }
    }
    if (seg_length > 2)
        count++;
    return count;
}