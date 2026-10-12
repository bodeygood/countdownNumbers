#include <stdlib.h>
#include <stdio.h>

/**
 * Uses operations in array order to try to reach target.
 * @param op operations (0 = +, 1 = -, 2 = *, 3 = /)
 * @param currNums pointer to a modifiable array of the six numbers
 * @param n indexes of numbers to be used for each operation
 * @param target target number to reach
 * @returns how many operations to reach target, or -1 if not reached
 */
int reachTarget(int (*op)[], int (*currNums)[], int n[][2], int target) {
    int res[5];
    for (int i = 0; i < 5; i++) {
        int *n1 = &(*currNums)[n[i][0]];
        int *n2 = &(*currNums)[n[i][1]];
        while (*n1 <= 0) {
            n1 = &res[-*n1];
        }
        while (*n2 <= 0) {
            n2 = &res[-*n2];
        }
        if ((*op)[i] == 0) {
            res[i] = *n1 + *n2;
            *n1 = -i;
            *n2 = -i;
        }
        else if ((*op)[i] == 1) {
            if (*n1 - *n2 <= 0) {
                return -1;
            }
            res[i] = *n1 - *n2;
            *n1 = -i;
            *n2 = -i;
        }
        else if ((*op)[i] == 2) {
            res[i] = *n1 * *n2;
            *n1 = -i;
            *n2 = -i;
        }
        else {
            if (*n1 % *n2 != 0) {
                return -1;
            }
            res[i] = *n1 / *n2;
            *n1 = -i;
            *n2 = -i;
        }
        if (res[i] == target) {
            return i;
        }
    }
    return -1;
}

/**
 * Prints the calculations to find the target once a solution has been found.
 * @param op operations (0 = +, 1 = -, 2 = *, 3 = /)
 * @param currNums pointer to a modifiable array of the six numbers
 * @param n indexes of numbers to be used for each operation
 * @param target target number to reach
 */
void printResult(int (*op)[], int (*currNums)[], int n[][2], int target) {
    int res[5];
    for (int i = 0; i < 5; i++) {
        int *n1 = &(*currNums)[n[i][0]];
        int *n2 = &(*currNums)[n[i][1]];
        while (*n1 <= 0) {
            n1 = &res[-*n1];
        }
        while (*n2 <= 0) {
            n2 = &res[-*n2];
        }
        if ((*op)[i] == 0) {
            res[i] = *n1 + *n2;
            printf("%d + %d = %d\n", *n1, *n2, res[i]);
            *n1 = -i;
            *n2 = -i;
        }
        else if ((*op)[i] == 1) {
            if (*n1 - *n2 <= 0) {
                return;
            }
            res[i] = *n1 - *n2;
            printf("%d - %d = %d\n", *n1, *n2, res[i]);
            *n1 = -i;
            *n2 = -i;
        }
        else if ((*op)[i] == 2) {
            res[i] = *n1 * *n2;
            printf("%d * %d = %d\n", *n1, *n2, res[i]);
            *n1 = -i;
            *n2 = -i;
        }
        else {
            if (*n1 % *n2 != 0) {
                return;
            }
            res[i] = *n1 / *n2;
            printf("%d / %d = %d\n", *n1, *n2, res[i]);
            *n1 = -i;
            *n2 = -i;
        }
        if (res[i] == target) {
            return;
        }
    }
}

/**
 * Asks for input of six numbers and a target number,
 * then tries to find a way using elementary operations
 * to combine these numbers into the target number.
 */
int main(int argc, char *argv[]) {
    int nums[6];
    printf("Numbers: ");
    scanf("%d %d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4], &nums[5]);
    printf("Numbers chosen are %d %d %d %d %d %d\n", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]);

    int target;
    printf("Target: ");
    scanf("%d", &target);
    printf("Target is %d\n", target);

    int op[5]; // Array of operations
    int n[5][2]; // Array of numbers to use in each operation
    int currNums[6]; // Modifiable array of numbers to use
    int counts[6] = {0}; // Counts how many times each number has been chosen in the operations
    for (op[0] = 0; op[0] < 4; op[0]++) {
        for (op[1] = 0; op[1] < 4; op[1]++) {
            for (op[2] = 0; op[2] < 4; op[2]++) {
                for (op[3] = 0; op[3] < 4; op[3]++) {
                    for (op[4] = 0; op[4] < 4; op[4]++) {
                        for (n[0][0] = 0; n[0][0] < 6; n[0][0]++) {
                            counts[n[0][0]]++;
                            for (n[0][1] = op[0] % 2 == 1 ? 0 : n[0][0] + 1; n[0][1] < 6; n[0][1]++) { // Order matters for -, / but not for +, *
                                if (counts[n[0][1]] == 2 || n[0][0] == n[0][1] || (counts[n[0][0]] == 2 && counts[n[0][1]] == 1)) { // Each number should only be chosen once, don't choose the same number for the same operation, and one of the numbers of the operation must be chosen for the first time
                                    continue;
                                }
                                counts[n[0][1]]++;
                                for (n[1][0] = 0; n[1][0] < 6; n[1][0]++) {
                                    if (counts[n[1][0]] == 2) {
                                        continue;
                                    }
                                    counts[n[1][0]]++;
                                    for (n[1][1] = op[1] % 2 == 1 ? 0 : n[1][0] + 1; n[1][1] < 6; n[1][1]++) {
                                        if (counts[n[1][1]] == 2 || n[1][0] == n[1][1] || (counts[n[1][0]] == 2 && counts[n[1][1]] == 1)) {
                                            continue;
                                        }
                                        counts[n[1][1]]++;
                                        for (n[2][0] = 0; n[2][0] < 6; n[2][0]++) {
                                            if (counts[n[2][0]] == 2) {
                                                continue;
                                            }
                                            counts[n[2][0]]++;
                                            for (n[2][1] = op[2] % 2 == 1 ? 0 : n[2][0] + 1; n[2][1] < 6; n[2][1]++) {
                                                if (counts[n[2][1]] == 2 || n[2][0] == n[2][1] || (counts[n[2][0]] == 2 && counts[n[2][1]] == 1)) {
                                                    continue;
                                                }
                                                counts[n[2][1]]++;
                                                for (n[3][0] = 0; n[3][0] < 6; n[3][0]++) {
                                                    if (counts[n[3][0]] == 2) {
                                                        continue;
                                                    }
                                                    counts[n[3][0]]++;
                                                    for (n[3][1] = op[3] % 2 == 1 ? 0 : n[3][0] + 1; n[3][1] < 6; n[3][1]++) {
                                                        if (counts[n[3][1]] == 2 || n[3][0] == n[3][1] || (counts[n[3][0]] == 2 && counts[n[3][1]] == 1)) {
                                                            continue;
                                                        }
                                                        counts[n[3][1]]++;
                                                        for (n[4][0] = 0; n[4][0] < 6; n[4][0]++) {
                                                            if (counts[n[4][0]] == 2) {
                                                                continue;
                                                            }
                                                            counts[n[4][0]]++;
                                                            for (n[4][1] = op[4] % 2 == 1 ? 0 : n[4][0] + 1; n[4][1] < 6; n[4][1]++) {
                                                                if (counts[n[4][1]] == 2 || n[4][0] == n[4][1] || (counts[n[4][0]] == 2 && counts[n[4][1]] == 1)) {
                                                                    continue;
                                                                }
                                                                counts[n[4][1]]++;
                                                                for (int i = 0; i < 6; i++) { // Reset current numbers
                                                                    currNums[i] = nums[i];
                                                                }
                                                                if (reachTarget(&op, &currNums, n, target) != -1) {
                                                                    printf("Solution found:\n");
                                                                    printResult(&op, &nums, n, target);
                                                                    return 0;
                                                                }
                                                                counts[n[4][1]]--;
                                                            }
                                                            counts[n[4][0]]--;
                                                        }
                                                        counts[n[3][1]]--;
                                                    }
                                                    counts[n[3][0]]--;
                                                }
                                                counts[n[2][1]]--;
                                            }
                                            counts[n[2][0]]--;
                                        }
                                        counts[n[1][1]]--;
                                    }
                                    counts[n[1][0]]--;
                                }
                                counts[n[0][1]]--;
                            }
                            counts[n[0][0]]--;
                        }
                    }
                }
            }
        }
    }

    printf("Solution not found.\n");
    return 0;
}