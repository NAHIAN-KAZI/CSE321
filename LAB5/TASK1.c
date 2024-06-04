#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

int checkP2(int x);
int* dTob(int n, int l);
int bTod(int a[], int l);

int main() {
    int pgs = 4; 
    int ms = 32; 
    int nof = ms / pgs; 
    int offset_bit; 
    int m; 
    int pg_num_bit; 

    int la[] = { 8, 4, 3, 2, 15, 18, 25 }; 
    int pmt[] = { 3, 6, 8, 12, 2 }; 

    offset_bit = checkP2(pgs);
    m = (int)log2(ms);
    pg_num_bit = checkP2(nof);

    printf("Page size: %d\n", pgs);
    printf("Memory size: %d\n", ms);
    printf("Number of frames required: %d\n", nof);
    printf("Page number bits: %d\n", pg_num_bit);
    printf("Offset bits: %d\n", offset_bit);
    printf("Number of address spaces: %d\n", m);

    printf("Page Table_____\n");
    for (int i = 0; i < 5; i++) {
        printf("%d -> %d\n", i, pmt[i]);
    }

    for (int i = 0; i < 7; i++) {
        int page_num = la[i] / pgs;
        int offset = la[i] % pgs;

        if (page_num >= 5) {
            printf("%d is an invalid page number\n", page_num);
            continue;
        }

        int frame_num = pmt[page_num];
        int physical_address = (frame_num * pgs) + offset;

        if (physical_address >= ms) {
            printf("%d is an invalid physical address\n", physical_address);
        }
        else {
            printf("Corresponding physical address of logical address %d: %d\n", la[i], physical_address);
        }
    }

    return 0;
}

int checkP2(int x) {
    int count = 0;
    while (x != 1) {
        if (x % 2 != 0) {
            return -1;
        }
        x /= 2;
        count++;
    }
    return count;
}

int* dTob(int n, int l) {
    static int arr[32];
    int i;
    for (i = 0; n > 0; i++) {
        arr[i] = n % 2;
        n /= 2;
    }
    return arr;
}

int bTod(int a[], int l) {
    int value = 0, i;
    for (i = 0; i < l; i++) {
        value += a[l - (i + 1)] * pow(2, i);
    }
    return value;
}