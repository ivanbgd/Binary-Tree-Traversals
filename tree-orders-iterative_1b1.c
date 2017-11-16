// On average, this version will consume more memory then a version with dynamic arrays. We allocate a fixed value of 100000 elements here for any input.

#define _CRT_SECURE_NO_WARNINGS
#define NMAX 100000                                             // I was getting stack overflow error for 100000 when local function variables were auto; but it works when they are static.

#include <stdio.h>


int read_1b1(int *n, int *key, int *left, int *right) {
    scanf("%d", n);
	for (int i = 0; i < *n; i++) {
		scanf("%d%d%d", &key[i], &left[i], &right[i]);
	}
	return 0;
}

int * inOrder_1b1(int n, int *key, int *left, int *right) {
	static int result[NMAX], stack[NMAX];                       // stack contains indices of vertices
	int resultSize = 0;
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

int * preOrder_1b1(int n, int * key, int * left, int * right) {
    static int result[NMAX], stack[NMAX];                       // stack contains indices of vertices
    int resultSize = 0;
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

int * postOrder_1b1(int n, int * key, int * left, int * right) {
	static int result[NMAX], stack[NMAX];                       // stack contains indices of vertices
    static char boolStack[NMAX];                                // For each element on the node stack, a corresponding value is stored on the bool stack. If this value is true, then we need to pop and visit the node on next encounter.
    int resultSize = 0;
    int size = 0;												// current stack size
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

void print_1b1(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_1b1() {
    static int n, key[NMAX], left[NMAX], right[NMAX], *result;

	read_1b1(&n, key, left, right);
    result = inOrder_1b1(n, key, left, right);
	print_1b1(n, result);
    result = preOrder_1b1(n, key, left, right);
	print_1b1(n, result);
    result = postOrder_1b1(n, key, left, right);
	print_1b1(n, result);

	scanf("%d", &n);
	return 0;
}