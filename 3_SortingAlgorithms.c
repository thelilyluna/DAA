void plotter1()
{
    static int arr[MAX];   // static memory allocation
    int n;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("Bubblebest.txt", "w");
    f2 = fopen("Bubbleavg.txt", "w");
    f3 = fopen("Bubbleworst.txt", "w");
    n = 10;
    while (n <= MAX)
    {
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        bubblesort(arr, n); // best case
        fprintf(f1, "%d\t%d\n", n, count);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        bubblesort(arr, n); // average case
        fprintf(f2, "%d\t%d\n", n, count);

        for (int i = 0; i < n; i++)
            arr[i] = n - i;
        bubblesort(arr, n); // worst case
        fprintf(f3, "%d\t%d\n", n, count);

        if (n < 10000)
            n *= 10;
        else
            n += 10000;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void plotter2()
{
    static int arr[MAX];   // static memory allocation
    int n;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("Insertionbest.txt", "w");
    f2 = fopen("Insertionavg.txt", "w");
    f3 = fopen("Insertionworst.txt", "w");
    n = 10;
    while (n <= MAX)
    {
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        insertionSort(arr, n); // best case
        fprintf(f1, "%d\t%d\n", n, count);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        insertionSort(arr, n); // average case
        fprintf(f2, "%d\t%d\n", n, count);

        for (int i = 0; i < n; i++)
            arr[i] = n - i;
        insertionSort(arr, n); // worst case
        fprintf(f3, "%d\t%d\n", n, count);

        if (n < 10000)
            n *= 10;
        else
            n += 10000;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}
