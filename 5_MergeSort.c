#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

int count;
static int temp[MAX];   // shared auxiliary buffer, replaces per-call VLAs

void merge(int *arr, int beg, int mid, int end)
{
    int i = beg, j = mid + 1, k = beg;

    while (i <= mid && j <= end)
    {
        count++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= end)
        temp[k++] = arr[j++];

    for (i = beg; i <= end; i++)
        arr[i] = temp[i];
}

void mergeSort(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        mergeSort(arr, beg, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, beg, mid, end);
    }
}

// Builds the worst-case input for merge sort by recursively de-interleaving
// (reverse of what merge() does) -- done in-place using the same temp buffer.
void worst(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        int n1 = mid - beg + 1;
        int n2 = end - mid;

        for (int i = 0; i < n1; i++)
            temp[beg + i] = arr[beg + 2 * i];
        for (int j = 0; j < n2; j++)
            temp[mid + 1 + j] = arr[beg + 2 * j + 1];

        for (int k = beg; k <= end; k++)
            arr[k] = temp[k];

        worst(arr, beg, mid);
        worst(arr, mid + 1, end);
    }
}

void tester()
{
    static int arr[MAX];   // static memory allocation
    int n;

    printf("Enter the number of elements\n");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("Array size exceeds maximum limit of %d\n", MAX);
        return;
    }

    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("The elments of array before sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, 0, n - 1);

    printf("The elements of the array after sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void plotter()
{
    static int arr[MAX];   // static memory allocation
    int n;
    srand(time(NULL));
    FILE *f1, *f2, *f3, *f4;
    f1 = fopen("Mergebest.txt", "w");
    f2 = fopen("Mergeavg.txt", "w");
    f3 = fopen("Mergeworst.txt", "w");
    f4 = fopen("Worstdata.txt", "w");

    for (n = 2; n <= MAX; n = n * 2)
    {
        // best case: already sorted
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count = 0;
        mergeSort(arr, 0, n - 1);
        fprintf(f1, "%d\t%d\n", n, count);

        // average case: random data
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count = 0;
        mergeSort(arr, 0, n - 1);
        fprintf(f2, "%d\t%d\n", n, count);

        // worst case: deinterleaved sorted data
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        worst(arr, 0, n - 1);
        for (int i = 0; i < n; i++)
            fprintf(f4, "%d", arr[i]);
        fprintf(f4, "\n");
        count = 0;
        mergeSort(arr, 0, n - 1);
        fprintf(f3, "%d\t%d\n", n, count);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    printf("Data is entered into file\n");
}

int main()
{
    int ch;
    printf("Enter your choice: \n\n1.Tester\n2.Plotter\n\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice!!!\n\n");
    }
    return 0;
}
