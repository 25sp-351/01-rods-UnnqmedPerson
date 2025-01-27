#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIECES 100

typedef struct {
    int length;
    int value;
} Piece;

void solveRodCutting(int rodLength, Piece *pieces, int pieceCount) {
    int dp[rodLength + 1];
    int choice[rodLength + 1];

    // Initialize DP array
    for (int ii = 0; ii <= rodLength; ii++) {
        dp[ii] = 0;
        choice[ii] = -1;
    }

    // Fill DP array
    for (int ii = 1; ii <= rodLength; ii++) {
        for (int jj = 0; jj < pieceCount; jj++) {
            if (pieces[jj].length <= ii) {
                int candidate = dp[ii - pieces[jj].length] + pieces[jj].value;
                if (candidate > dp[ii]) {
                    dp[ii] = candidate;
                    choice[ii] = jj;
                }
            }
        }
    }

    // Output the cutting list
    int remainingLength = rodLength;
    int totalValue = 0;
    while (remainingLength > 0 && choice[remainingLength] != -1) {
        int idx = choice[remainingLength];
        int count = 0;

        // Count the number of times the piece is used
        while (remainingLength >= pieces[idx].length && choice[remainingLength] == idx) {
            remainingLength -= pieces[idx].length;
            totalValue += pieces[idx].value;
            count++;
        }

        printf("%d @ %d = %d\n", count, pieces[idx].length, count * pieces[idx].value);
    }

    // Output the remainder and total value
    printf("Remainder: %d\n", remainingLength);
    printf("Value: %d\n", totalValue);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rod length>\n", argv[0]);
        return 1;
    }

    int rodLength = atoi(argv[1]);
    if (rodLength <= 0) {
        fprintf(stderr, "Invalid rod length: %d\n", rodLength);
        return 1;
    }

    Piece pieces[MAX_PIECES];
    int pieceCount = 0;

    char line[256];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (pieceCount >= MAX_PIECES) {
            fprintf(stderr, "Too many pieces specified. Maximum allowed is %d.\n", MAX_PIECES);
            return 1;
        }

        int length, value;
        if (sscanf_s(line, "%d, %d", &length, &value) != 2) {
            fprintf(stderr, "Invalid input format: %s", line);
            return 1;
        }

        if (length > 0 && value > 0) {
            pieces[pieceCount].length = length;
            pieces[pieceCount].value = value;
            pieceCount++;
        }
    }

    if (pieceCount == 0) {
        fprintf(stderr, "No valid pieces provided.\n");
        return 1;
    }

    solveRodCutting(rodLength, pieces, pieceCount);

    return 0;
}
