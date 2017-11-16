#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct Arrays {                                         // type name, Arrays, is unneccessary
    int n;
    int *key, *left, *right;
} arrays;

int read_r2(arrays *arrayPtr) {
    scanf("%d", &arrayPtr->n);

	arrayPtr->key = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->key == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}

	arrayPtr->left = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->left == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}

	arrayPtr->right = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->right == NULL) {
		fprintf(stderr, "calloc failed\n");
		return(-1);
	}

	for (int i = 0; i < arrayPtr->n; i++) {
		scanf("%d%d%d", &arrayPtr->key[i], &arrayPtr->left[i], &arrayPtr->right[i]);
	}
	return 0;
}

void inOrderRec_r2(int n, int *key, int *left, int *right, int current, int *result) {
    static int counter = 0;
    if (left[current] != -1)
        inOrderRec_r2(n, key, left, right, left[current], result);
    result[counter++] = key[current];
    if (right[current] != -1)
        inOrderRec_r2(n, key, left, right, right[current], result);
}

int * inOrder_r2(arrays *arrayPtr) {
    int *result = (int *)calloc(arrayPtr->n, sizeof(int));
    inOrderRec_r2(arrayPtr->n, arrayPtr->key, arrayPtr->left, arrayPtr->right, 0, result);              // 0 is root
    return result;
}

void preOrderRec_r2(arrays *arrayPtr, int current, int *result) {       // we can also pass a pointer to the struct instead of all its elements individually
    static int counter = 0;
    result[counter++] = arrayPtr->key[current];
    if (arrayPtr->left[current] != -1)
        preOrderRec_r2(arrayPtr, arrayPtr->left[current], result);
    if (arrayPtr->right[current] != -1)
        preOrderRec_r2(arrayPtr, arrayPtr->right[current], result);
}

int * preOrder_r2(arrays *arrayPtr) {
    int *result = (int *)calloc(arrayPtr->n, sizeof(int));
    preOrderRec_r2(arrayPtr, 0, result);                        // 0 is root
    return result;
}

void postOrderRec_r2(arrays *arrayPtr, int current, int *result) {
    static int counter = 0;
    if (arrayPtr->left[current] != -1)
        postOrderRec_r2(arrayPtr, arrayPtr->left[current], result);
    if (arrayPtr->right[current] != -1)
        postOrderRec_r2(arrayPtr, arrayPtr->right[current], result);
    result[counter++] = arrayPtr->key[current];
}

int * postOrder_r2(arrays *arrayPtr) {
    int *result = (int *)calloc(arrayPtr->n, sizeof(int));
    postOrderRec_r2(arrayPtr, 0, result);                       // 0 is root
    return result;
}

void print_r2(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_r2() {
    arrays array;                                               // we create an instance of arrays
    arrays *arrayPtr = &array;                                  // a pointer to it - arrayPtr contains the address of the arrays instance array
	int *result;

	read_r2(arrayPtr);
    result = inOrder_r2(arrayPtr);
	print_r2(arrayPtr->n, result);
    result = preOrder_r2(arrayPtr);
	print_r2(arrayPtr->n, result);
    result = postOrder_r2(arrayPtr);
	print_r2(arrayPtr->n, result);

    free(result);
    free(arrayPtr->key);
	free(arrayPtr->left);
	free(arrayPtr->right);

	//scanf("%d", &arrayPtr->n);
	return 0;
}