// Fábio Pascoal - 2024102901
// Gessica Silva - 2022102174
// Nathan Garcia - 2022102179

#include <stdlib.h>
#include "item.h"

const int CUTOFF = 20;

void insert_sort(Item *a, int lo, int hi) {
    for (int i = lo + 1; i <= hi; i++) {
        Item temp = a[i];
        int j = i;
        while (j > lo && less(temp, a[j - 1])) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }
}

int median_of_3(Item *a, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (less(a[mid], a[lo])) exch(a[mid], a[lo]); // Ordena lo e mid
    if (less(a[hi], a[lo])) exch(a[hi], a[lo]);   // Ordena lo e hi
    if (less(a[hi], a[mid])) exch(a[hi], a[mid]); // Ordena mid e hi
    return mid;
}

int partition(Item *a, int lo, int hi) {
    int i = lo, j = hi+1;
    Item v = a[lo];
    while(1) {
        while (less(a[++i], v)) // Find item on left to swap.
            if (i == hi) break;
        while (less(v, a[--j])) // Find item on right to swap.
            if (j == lo) break;
        if (i >= j) break; // Check if pointers cross.
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]); // Swap with partitioning item.
    return j; // Return index of item known to be in place.
}

void quick_sort(Item *a, int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insert_sort(a, lo, hi);
        return;
    }
    int median = median_of_3(a, lo, hi);
    exch(a[lo], a[median]);
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j-1);
    quick_sort(a, j+1, hi);
}

void sort(Item *a, int lo, int hi) {
    quick_sort(a, lo, hi);
}