float average(const int *arr, int size)
{
    if (size <= 0 || arr == NULL) {
        return 0.0f;
    }

    int sum = 0;
    int ignored = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0 || arr[i] <= 100)
            sum += arr[i];
        else
            ignored++;
    }
    return (float)sum / (size - ignored);
}