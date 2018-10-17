#include <cstdio>
#include <cstdlib>
#include <utility>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        exit(-1);
    }
    
    printf("Ohai %s\n", argv[1]);
    
    printf("This %d and this %f\n", std::pair<int,double>(1,2.0).first
                                  , std::pair<int,double>(5,42.0).second);
    return 0;
}
