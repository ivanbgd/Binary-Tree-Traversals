#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct Arrays {                                         // type name, Arrays, is unneccessary
    int n;
    int *key, *left, *right;
} arrays;

arrays read_2b(void) {
    arrays arrays;                                              // we create an instance of arrays - this instance will be destroyed when the function returns, because it is local,
                                                                // but it will be copied into another instance, that this function returns, and that is declared and defined in
                                                                // function main(), that calls this function
    printf("2 %p\n", &arrays);                                  // we can see that the address of this instance is different from the one in main()

    scanf("%d", &arrays.n);

    arrays.key = (int *)calloc(arrays.n, sizeof(int));
	if (arrays.key == NULL)
		fprintf(stderr, "calloc failed\n");

	arrays.left = (int *)calloc(arrays.n, sizeof(int));
	if (arrays.left == NULL)
		fprintf(stderr, "calloc failed\n");

	arrays.right = (int *)calloc(arrays.n, sizeof(int));
	if (arrays.right == NULL)
		fprintf(stderr, "calloc failed\n");

    for (int i = 0; i < arrays.n; i++) {
        scanf("%d%d%d", &arrays.key[i], &arrays.left[i], &arrays.right[i]);
    }

    return arrays;
}

int * inOrder_2b(arrays arrays) {
	int * result;
	result = (int *)calloc(arrays.n, sizeof(int));
	int resultSize = 0;
	int * stack;												// stack contains indices of vertices
	stack = (int *)calloc(arrays.n, sizeof(int));
	int size = 0;												// current stack size
	int current = 0;											// an index - 0 is root
	while (1) {
        while (current > -1) {
            stack[size++] = current;
            current = arrays.left[current];
        }
        if (size) {
            current = stack[--size];
            result[resultSize++] = arrays.key[current];         // visit()
            current = arrays.right[current];
        }
        else
            return result;
	}
}

int * preOrder_2b(arrays arrays) {
    int * result;
    result = (int *)calloc(arrays.n, sizeof(int));
    int resultSize = 0;
    int * stack;												// stack contains indices of vertices
    stack = calloc(arrays.n, sizeof(int));
    int size = 0;												// current stack size
    stack[size++] = 0;                                          // stack contains indices of vertices - 0 is root
    int current;
    while (size) {
        current = stack[--size];                                // an index
        result[resultSize++] = arrays.key[current];             // visit()
        if (arrays.right[current] != -1) {
            stack[size++] = arrays.right[current];
        }
        if (arrays.left[current] != -1) {
            stack[size++] = arrays.left[current];
        }
    }
    return result;
}

int * postOrder_2b(arrays arrays) {
    int * result = (int *)calloc(arrays.n, sizeof(int));
    int resultSize = 0;
    int * stack = (int *)calloc(arrays.n, sizeof(int));         // stack contains indices of vertices
    int size = 0;												// current stack size
    char * boolStack = (char *)calloc(arrays.n, sizeof(char));  // For each element on the node stack, a corresponding value is stored on the bool stack. If this value is true, then we need to pop and visit the node on next encounter.
    int boolSize = 0;
    char alreadyEncountered;                                    // boolean
    int current = 0;                                            // an index - 0 is root
    while (current > -1) {
        stack[size++] = current;
        boolStack[boolSize++] = 0;                              // false
        current = arrays.left[current];
    }
    while (size) {
        current = stack[size - 1];
        alreadyEncountered = boolStack[boolSize - 1];
        if (alreadyEncountered) {
            result[resultSize++] = arrays.key[current];         // visit()
            size--;
            boolSize--;
        }
        else {
            boolSize--;
            boolStack[boolSize++] = 1;                          // true
            current = arrays.right[current];
            while (current > -1) {
                stack[size++] = current;
                boolStack[boolSize++] = 0;                      // false
                current = arrays.left[current];
            }
        }
    }
    return result;
}

void print_2b(int n, int * array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
}



int main_2b() {
    arrays arrays;
    int *result;
    printf("1 %p\n", &arrays);

    arrays = read_2b();
    printf("3 %p\n", &arrays);

    result = inOrder_2b(arrays);
	print_2b(arrays.n, result);
    result = preOrder_2b(arrays);
	print_2b(arrays.n, result);
    result = postOrder_2b(arrays);
	print_2b(arrays.n, result);

    free(result);
    free(arrays.key);
	free(arrays.left);
	free(arrays.right);

	scanf("%d", &arrays.n);
	return 0;
}