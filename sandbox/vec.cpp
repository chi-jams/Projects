#include <cstdio>
#include <cstdlib>

typedef int v4si __attribute__ ((vector_size (16)));
typedef double v4sd __attribute__ ((vector_size (64)));

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        exit(-1);
    }
    
    v4si a = {1, 2, 3, 4};
    v4si b = {4, 3, 2, 1};
    v4si c;
    
    c = a + b;
    printf("%d, %d\n", c[0], c[3]);

    v4sd f = {1, 2, 3, 4};
    v4sd g = {4, 3, 2};
    v4sd h;

    h = f + g;
    printf("%f %f\n", h[0], h[3]);
    printf("size of double: %d\n", sizeof(double));
    printf("Ohai %s\n", argv[1]);
    return 0;
}
