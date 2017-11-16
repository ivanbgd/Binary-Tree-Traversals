#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int read_r1(int *n, int **key, int **left, int **right) {
    int i;
	int *keyLocal;
	int *leftLocal, *rightLocal;
    scanf("%d", n);                                           // n is same as &*n or *&n here.

	keyLocal = (int *)calloc(*n, sizeof(int));
	if (keyLocal == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}
	*key = keyLocal;

	leftLocal = (int *)calloc(*n, sizeof(int));
	if (leftLocal == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}
	*left = leftLocal;

	rightLocal = (int *)calloc(*n, sizeof(int));
	if (rightLocal == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}
	*right = rightLocal;

	for (i = 0; i < *n; i++) {
		scanf("%d%d%d", &keyLocal[i], &leftLocal[i], &rightLocal[i]);     // &keyLocal[i] is same as &(*key)[i] here.
	}
	return 0;
}

void inOrderRec_r1(int n, int *key, int *left, int *right, int current, int *result) {
    static int counter = 0;
    if (left[current] != -1)
        inOrderRec_r1(n, key, left, right, left[current], result);
    result[counter++] = key[current];
    if (right[current] != -1)
        inOrderRec_r1(n, key, left, right, right[current], result);
}

int * inOrder_r1(int n, int *key, int *left, int *right) {
    int *result = (int *)calloc(n, sizeof(int));
    inOrderRec_r1(n, key, left, right, 0, result);              // 0 is root
    return result;
}

void preOrderRec_r1(int n, int *key, int *left, int *right, int current, int *result) {
    static int counter = 0;
    result[counter++] = key[current];
    if (left[current] != -1)
        preOrderRec_r1(n, key, left, right, left[current], result);
    if (right[current] != -1)
        preOrderRec_r1(n, key, left, right, right[current], result);
}

int * preOrder_r1(int n, int * key, int * left, int * right) {
    int *result = (int *)calloc(n, sizeof(int));
    preOrderRec_r1(n, key, left, right, 0, result);             // 0 is root
    return result;
}

void postOrderRec_r1(int n, int *key, int *left, int *right, int current, int *result) {
    static int counter = 0;
    if (left[current] != -1)
        postOrderRec_r1(n, key, left, right, left[current], result);
    if (right[current] != -1)
        postOrderRec_r1(n, key, left, right, right[current], result);
    result[counter++] = key[current];
}

int * postOrder_r1(int n, int * key, int * left, int * right) {
    int *result = (int *)calloc(n, sizeof(int));
    postOrderRec_r1(n, key, left, right, 0, result);            // 0 is root
    return result;
}

void print_r1(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_r1() {
	int n, *key, *left, *right, *result;

	read_r1(&n, &key, &left, &right);
    result = inOrder_r1(n, key, left, right);
	print_r1(n, result);
    result = preOrder_r1(n, key, left, right);
	print_r1(n, result);
    result = postOrder_r1(n, key, left, right);
	print_r1(n, result);

    free(result);
    free(key);
	free(left);
	free(right);

	//scanf("%d", &n);
	return 0;
}