#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int rand_range(int min, int max);
int* make_pts(int N);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        exit(-1);
    }

    long int N = strtol(argv[1], NULL, 10);
    if (N <= 0) {
        printf("Please enter a positive int for N\n");
        exit(-1);
    }
    else if (N == LONG_MAX || N == LONG_MIN) {
        printf("The provided N is too %s.\n", N == LONG_MAX ? "large" : "small");
        exit(-1);
    }

    printf("N: %d\n", N);

    int* pts = make_pts(N);

    for (int i = 0; i < 2 * N; i+=2)
        printf("%d: (%d, %d)\n", i / 2, pts[i], pts[i + 1]);

    int* perms = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) perms[i] = i;

    free(pts);
    free(perms);
    return 0;
}

int rand_range(int min, int max) {
    double u = rand() / (double)RAND_MAX;
    return (max - min + 1) * u + min;
}

int* make_pts(int N) {
    int* pts = (int*) malloc(sizeof(int) * N * 2);
    srand(time(NULL));
    for (int i = 0; i < 2 * N; i+=2) {
        pts[i] = rand_range(0, 1000);
        pts[i + 1] = rand_range(0, 1000);
    }

    return pts;
}
