#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int read_1a2(int *n, int **key, int **left, int **right) {
    int i;
	int *keyLocal;
	int *leftLocal, *rightLocal;
    scanf("%d", n);                                             // n is same as &*n or *&n here.

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

int * inOrder_1a2(int n, int *key, int *left, int *right) {
	int * result;
	result = (int *)calloc(n, sizeof(int));
	int resultSize = 0;
	int * stack;												// stack contains indices of vertices
	stack = (int *)calloc(n, sizeof(int));
	int size = 0;												// current stack size
	int current = 0;											// an index - 0 is root
	while (1) {
        while (current > -1) {
            stack[size++] = current;
            current = left[current];
        }
        if (size) {
            current = stack[--size];
            result[resultSize++] = key[current];                // visit()
            current = right[current];
        }
        else
            return result;
	}
}

int * preOrder_1a2(int n, int * key, int * left, int * right) {
    int * result;
    result = (int *)calloc(n, sizeof(int));
    int resultSize = 0;
    int * stack;												// stack contains indices of vertices
    stack = calloc(n, sizeof(int));
    int size = 0;												// current stack size
    stack[size++] = 0;                                          // stack contains indices of vertices - 0 is root
    int current;
    while (size) {
        current = stack[--size];                                // an index
        result[resultSize++] = key[current];                    // visit()
        if (right[current] != -1) {
            stack[size++] = right[current];
        }
        if (left[current] != -1) {
            stack[size++] = left[current];
        }
    }
    return result;
}

int * postOrder_1a2(int n, int * key, int * left, int * right) {
    int * result = (int *)calloc(n, sizeof(int));
    int resultSize = 0;
    int * stack = (int *)calloc(n, sizeof(int));                // stack contains indices of vertices
    int size = 0;												// current stack size
    char * boolStack = (char *)calloc(n, sizeof(char));         // For each element on the node stack, a corresponding value is stored on the bool stack. If this value is true, then we need to pop and visit the node on next encounter.
    int boolSize = 0;
    char alreadyEncountered;                                    // boolean
    int current = 0;                                            // an index - 0 is root
    while (current > -1) {
        stack[size++] = current;
        boolStack[boolSize++] = 0;                              // false
        current = left[current];
    }
    while (size) {
        current = stack[size - 1];
        alreadyEncountered = boolStack[boolSize - 1];
        if (alreadyEncountered) {
            result[resultSize++] = key[current];                // visit()
            size--;
            boolSize--;
        }
        else {
            boolSize--;
            boolStack[boolSize++] = 1;                          // true
            current = right[current];
            while (current > -1) {
                stack[size++] = current;
                boolStack[boolSize++] = 0;                      // false
                current = left[current];
            }
        }
    }
    return result;
}

void print_1a2(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_1a2() {
	int n, *key, *left, *right, *result;

	read_1a2(&n, &key, &left, &right);
    result = inOrder_1a2(n, key, left, right);
	print_1a2(n, result);
    result = preOrder_1a2(n, key, left, right);
	print_1a2(n, result);
    result = postOrder_1a2(n, key, left, right);
	print_1a2(n, result);

    free(result);
    free(key);
	free(left);
	free(right);

	scanf("%d", &n);
	return 0;
}