/*
Returning or passing a struct means copying all the struct's elements, and therefore it's better to return/pass a pointer to the struct instead.
That's what we do here - working with pointers.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct Arrays {                                         // type name, Arrays, is unneccessary
    int n;
    int *key, *left, *right;
} arrays;

void read_2a(arrays *arrayPtr) {
    scanf("%d", &arrayPtr->n);

    arrayPtr->key = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->key == NULL)
		fprintf(stderr, "calloc failed\n");

	arrayPtr->left = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->left == NULL)
		fprintf(stderr, "calloc failed\n");

	arrayPtr->right = (int *)calloc(arrayPtr->n, sizeof(int));
	if (arrayPtr->right == NULL)
		fprintf(stderr, "calloc failed\n");

    for (int i = 0; i < arrayPtr->n; i++) {
        scanf("%d%d%d", &arrayPtr->key[i], &arrayPtr->left[i], &arrayPtr->right[i]);
    }
}

int * inOrder_2a(arrays *arrayPtr) {
	int * result;
	result = (int *)calloc(arrayPtr->n, sizeof(int));
	int resultSize = 0;
	int * stack;												// stack contains indices of vertices
	stack = (int *)calloc(arrayPtr->n, sizeof(int));
	int size = 0;												// current stack size
	int current = 0;											// an index - 0 is root
	while (1) {
        while (current > -1) {
            stack[size++] = current;
            current = arrayPtr->left[current];
        }
        if (size) {
            current = stack[--size];
            result[resultSize++] = arrayPtr->key[current];      // visit()
            current = arrayPtr->right[current];
        }
        else
            return result;
	}
}

int * preOrder_2a(arrays *arrayPtr) {
    int * result;
    result = (int *)calloc(arrayPtr->n, sizeof(int));
    int resultSize = 0;
    int * stack;												// stack contains indices of vertices
    stack = calloc(arrayPtr->n, sizeof(int));
    int size = 0;												// current stack size
    stack[size++] = 0;                                          // stack contains indices of vertices - 0 is root
    int current;
    while (size) {
        current = stack[--size];                                // an index
        result[resultSize++] = arrayPtr->key[current];          // visit()
        if (arrayPtr->right[current] != -1) {
            stack[size++] = arrayPtr->right[current];
        }
        if (arrayPtr->left[current] != -1) {
            stack[size++] = arrayPtr->left[current];
        }
    }
    return result;
}

int * postOrder_2a(arrays *arrayPtr) {
    int * result = (int *)calloc(arrayPtr->n, sizeof(int));
    int resultSize = 0;
    int * stack = (int *)calloc(arrayPtr->n, sizeof(int));      // stack contains indices of vertices
    int size = 0;												// current stack size
    char * boolStack = (char *)calloc(arrayPtr->n, sizeof(char)); // For each element on the node stack, a corresponding value is stored on the bool stack. If this value is true, then we need to pop and visit the node on next encounter.
    int boolSize = 0;
    char alreadyEncountered;                                    // boolean
    int current = 0;                                            // an index - 0 is root
    while (current > -1) {
        stack[size++] = current;
        boolStack[boolSize++] = 0;                              // false
        current = arrayPtr->left[current];
    }
    while (size) {
        current = stack[size - 1];
        alreadyEncountered = boolStack[boolSize - 1];
        if (alreadyEncountered) {
            result[resultSize++] = arrayPtr->key[current];      // visit()
            size--;
            boolSize--;
        }
        else {
            boolSize--;
            boolStack[boolSize++] = 1;                          // true
            current = arrayPtr->right[current];
            while (current > -1) {
                stack[size++] = current;
                boolStack[boolSize++] = 0;                      // false
                current = arrayPtr->left[current];
            }
        }
    }
    return result;
}

void print_2a(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_2a() {
    arrays array;                                               // we create an instance of arrays
    arrays *arrayPtr = &array;                                  // a pointer to it - arrayPtr contains the address of the arrays instance array
    int *result;

    read_2a(arrayPtr);
    result = inOrder_2a(arrayPtr);
	print_2a((*arrayPtr).n, result);
    result = preOrder_2a(arrayPtr);
	print_2a(arrayPtr->n, result);
    result = postOrder_2a(arrayPtr);
	print_2a(arrayPtr->n, result);

    free(result);
    free(arrayPtr->key);
	free(arrayPtr->left);
	free(arrayPtr->right);

	//scanf("%d", &(*arrayPtr).n);                                // same as scanf("%d", &array.n); or scanf("%d", &arrayPtr->n);
	return 0;
}