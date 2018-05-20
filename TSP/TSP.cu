#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#include <algorithm>

int rand_range(int min, int max);
int* make_pts(int N);
int* gen_perm(int n, int k);

double get_dist(const int* pts, int i, int j);

void serial_tsp(int* pts, double& min_dist, int& min_perm, int N, int Nf);

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
    unsigned long long int Nf = 1;
    for (int i=N;i>0;i--) Nf*=i;

    int* pts = make_pts(N);

    for (int i = 0; i < 2 * N; i+=2)
        printf("%d: (%d, %d)\n", i / 2, pts[i], pts[i + 1]);

    double min_dist;
    int min_perm;
    serial_tsp(pts, min_dist, min_perm, N, Nf);
    printf("Min distance: %f\n", min_dist);
    printf("Path:\n");
    int* perm = gen_perm(N, min_perm);
    for (int i = 0; i < N; i++) {
        int p_i = perm[i];
        printf("%d: (%d, %d)\n", p_i, pts[2*p_i], pts[2*p_i + 1]);
    }

    free(pts);
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

int* gen_perm(int n, int perm) {
    int i, ind, m=perm;
    int* p = (int*) malloc(sizeof(int) * n);
    int* e = (int*) malloc(sizeof(int) * n);

    for (i=0;i<n;i++)e[i]=i;
    for (i=0;i<n;i++) {
        ind = m % (n - i);
        m = m / (n - i);
        p[i] = e[ind];
        e[ind] = e[n - i - 1];
    }

    free(e);

    return p;
}

double get_dist(const int* pts, int i, int j) {
    int x1 = pts[2*i],
        y1 = pts[2*i + 1],
        x2 = pts[2*j],
        y2 = pts[2*j + 1];

    int dx = x1 - x2,
        dy = y1 - y2;
    dx *= dx;
    dy *= dy;
    
    return sqrt(dx + dy);
}

void serial_tsp(int* pts, double& min_dist, int& min_perm, int N, int Nf) {
    min_dist = -1;
    int* perm;

    for (int i = 0; i < Nf; i++) {
        perm = gen_perm(N, i); 

        double dist = 0;
        for (int j = 0; j < N; j++) {
            dist += get_dist(pts, perm[j], perm[(j+1) % N]);
        }

        if (dist < min_dist || min_dist < 0) {
            min_dist = dist;
            min_perm = i;
        }
        
        free(perm);
    }
}
