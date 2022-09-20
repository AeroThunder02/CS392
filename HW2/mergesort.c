/*
Name: mergesort.c
Author: Maciej Kowalczyk
Date: 2/16/22
Pledge: I pledge my Honor that I have abided by the Stevens Honor System
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mergesort.h"
/*
Helper functions used in mergesort implementation.
*/

static void merge(void *array, size_t len, size_t elem_sz, int(*comp)(const void*, const void*), int l, int m, int h);
static void mergeActual(void *array, size_t len, size_t elem_sz, int (*comp)(const void*, const void*), int l, int h);
/* 
Function that takes two int void pointers and compares them.
It returns an integer depending on their order:
-  1 if first int is greater
- -1 if second int is greater
-  0 if both doubles are equal
*/


int int_cmp(const void *a, const void *b){
	if(*(int *) a > *(int *) b){
		return 1;
        }
	else if(*(int *) a < *(int *) b){
		return -1;
	}
	return 0;
}

/*
Function that takes two double void pointers and compares them.
It returns an integer depending on their order
-  1 if first double is greater
- -1 if second double is greater
-  0 if both doubles are equal
*/

int dbl_cmp(const void *a, const void *b){
	if(*(double *) a > *(double *) b){
		return 1;
	}
	else if(*(double *) a < *(double *) b){
		return -1;
	}
	return 0;
}

/*
Mergesort implementation credit: geeksforgeeks.org/merge-sort
Modified to work with void pointers according to HW2 specs
*/
void merge(void* array, size_t len, size_t elem_sz, int(*comp)(const void*, const void*), int l, int m, int h){
	int l2 = m+1;

	//Int case
	if(elem_sz == sizeof(int)){
		int* arr = (int*) array;
		if (comp(arr+m, arr+l2) <= 0){
			return;
		}

		while(l <= m && l2 <= h){
			if (comp(arr+l, arr+l2) <= 0){
				l++;
			}
			else{
				int val = *(arr+l2);
				int i = l2;
				while (i != l){
					*(arr+i) = *(arr+(i-1));
					i--;
				}
				*(arr+l) = val;
				l++;
				l2++;
				m++;
			}
		}
	}

	//Double case
	else if(elem_sz == sizeof(double)){
		double* arr = (double*)array;
		if (comp(arr+m, arr+l2) <= 0){
			return;
		}

		while(l <= m && l2 <= h){
			if (comp(arr+l, arr+l2) <= 0){
				l++;
			}
			else{
				double val = *(arr+l2);
				int i = l2;
				while (i != l){
					*(arr+i) = *(arr+(i-1));
					i--;
				}
				*(arr+l) = val;
				l++;
				l2++;
				m++;
			}
		}
	}
	//Other cases(outside scope of project)
	else{
		printf("debug");
		return;
	}
}

/*
Implementation of mergesort. Also acquired from GeeksforGeeks.
*/
void mergeActual(void* array, size_t len, size_t elem_sz,  int (*comp)(const void*, const void*), int l, int h){
	if(l<h){
		int m = l + ((h-l)/2);
		mergeActual(array, len, elem_sz, comp, l, m);
		mergeActual(array, len, elem_sz, comp, (m+1), h);
		merge(array, len, elem_sz, comp, l, m, h);
	}
}

void mergesort(void* array, size_t len, size_t elem_sz, int (*comp)(const void*, const void*)){
	mergeActual(array, len, elem_sz, comp, 0, len-1);
}
