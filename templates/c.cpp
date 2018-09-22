#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        exit(-1);
    }
    
    printf("Ohai %s\n", argv[1]);
    return 0;
}
