#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define NLNCHR '\n'
#define BSTRLN 20
#define ZERO  "zero"
#define ONE   "one"
#define TWO   "two"
#define THREE "three"
#define FOUR  "four"
#define FIVE  "five"
#define SIX   "six"
#define SEVEN "seven"
#define EIGHT "eight"
#define NINE  "nine"


int is_digit(int c);
int to_digit(int c);
int parse_num(char *str, int *is0);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);
void print_int_arr(int *arr, int n);


int main(int argc, char *argv[]) {
    int sum = 0, brk = 0;
    
    while (1) {
        int maxStrLen = BSTRLN, len = 0;
        char *str = (char*)calloc(maxStrLen, sizeof(char));
        assert(str);
        char c;
        int lastNL = 0;
        while ((c = getchar()) != ',') {
            if (c == '\n') {
                if (lastNL) {
                    brk = 1;
                    break;
                }
                lastNL = 1;
                continue;
            }
            lastNL = 0;
            str[len] = c;
            len++;
            if (len + 1 >= maxStrLen) {
                maxStrLen *= 2;
                str = (char*)realloc(str, maxStrLen * sizeof(char));
                assert(str);
            }
        }

        

        str[len] = '\0';
        // printf("%s\n", str);

        int curVal = 0;
        for (int i = 0; i < len; i++) {
            curVal = ((curVal + str[i]) * 17) % 256;
        }
        // printf("%d\n", curVal);
        sum += curVal;

        free(str);
        if (brk) {
            break;
        }


    }
    
    printf("Sum: %d", sum);
    return 0;
}

// Returns 1 if a character is a digit
int is_digit(int c) {
    return ((c = c - '0') >= 0) && (c < 10);
}

// Returns a integer digit given a character digit
int to_digit(int c) {
    return c - '0';
}

// Turns string of numbers into an integer, 
// stopping at the first non digit it encounters
// Now accepts negative numbers
int parse_num(char *str, int *is0) {
    int isNegative = -1;
    int i = 0, ret = 0;
    if (str[0] == '-') {
        isNegative = 1;
        i++;
    }

    if (str[0] == '0') {
        *is0 = 1;
    }
    
    while (is_digit(str[i])) {
        ret *= 10;
        ret += (isNegative * -1) * to_digit(str[i]);
        i++;
    }

    return ret;
}

// Reads one input line, including the newline character
char *read_line(void) {
    int n = 0, linelen = BSTRLN;
    char ch = getchar(), *line;
    line = (char*)malloc(linelen * sizeof(char));
    assert(line);

    if (ch == EOF) {
        line[0] = '\n'; line[1] = '\0';
        return line;
    }

    while (1) {
        /* Make character array longer */
        if (n + 1 >= linelen) {
            linelen *= 2;
            line = realloc(line, linelen * sizeof(char));
            assert(line);
        }
        line[n++] = ch;
        /* Break at a newline or EOF character */
        if (ch == NLNCHR || ch == EOF) {
            break;
        }

        ch = getchar();
    }
    line[n] = '\0';
    return line;
}


// Returns 1 if the array contains the element specified, up to n
int contains(int *arr, int elem, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elem) {
            return 1;
        }
    }
    return 0;
}

// Returns the sum of the list, within integer overflow bounds
int sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// Prints an integer array
void print_int_arr(int *arr, int n) {
    printf("[");
        for (int i = 0; i < n; i++) {
            printf("%d, ", arr[i]);
        }
    printf("]\n");
}
