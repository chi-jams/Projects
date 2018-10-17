
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define UH 102
#define STRIDE 8
int main() {
    
    srand(time(NULL)); 
    std::vector<int> things(UH, 0);
    std::vector<int> other(UH, 0);
    for (int i = 0; i < things.size(); i++) {
        things[i] = rand() % 10;
        other[i] = rand() % 10;
    }

    int sum = 0;
    for (int i = 0; i < things.size(); i++) {
        sum += things[i] + other[i];
        std::cout << "sum " << sum << std::endl;
    }

    int p_sum = 0;
    int k = 0;
    int p_sums[4] = {0};
    for (k = 0; k < things.size() - STRIDE; k+= STRIDE) {
        std::cout << k << std::endl;
        p_sums[0] += things[k] + other[k]; 
        p_sums[1] += things[k + 1] + other[k + 1]; 
        p_sums[2] += things[k + 2] + other[k + 2]; 
        p_sums[3] += things[k + 3] + other[k + 3]; 
        p_sums[0] += things[k + 4] + other[k + 4]; 
        p_sums[1] += things[k + 5] + other[k + 5]; 
        p_sums[2] += things[k + 6] + other[k + 6]; 
        p_sums[3] += things[k + 7] + other[k + 7]; 

        p_sums[0] += p_sums[2];
        p_sums[1] += p_sums[3];
        
        p_sum += p_sums[0] + p_sums[1];
        
        memset(p_sums, 0, sizeof(p_sums));
        std::cout << "p_sum " << p_sum << std::endl;
    }

    std::cout << "Stopped at " << k << std::endl;
    for (; k < things.size(); k++) {
        std::cout << k << std::endl;
        p_sum += things[k] + other[k];
    }
    std::cout << "Ohai " << sum << " vs. " << p_sum << std::endl;
    return 0;
}
