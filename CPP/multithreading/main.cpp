
#include <iostream>
#include <thread>
#include <vector>

void thread_action( int num_items, int thread_num ) {

    int cake = 1;
    for( int i = 0; i < num_items; i++ ) {
        cake *= 2;
    }
    std::cout << "Thread: " << thread_num << " Val: " << cake << std::endl;
}

void test_thread() {
    std::cout << "Hello multithreading!" << std::endl;
}

int main() {

    unsigned int num_threads = std::thread::hardware_concurrency();

    std::cout << "Number of threads: " << num_threads << std::endl;

    std::vector<std::thread> processes;

    for( unsigned int i = 0; i < num_threads; i++ ) {
        processes.push_back( std::thread( thread_action, 10000000, (int)i ) );
    }

    // Wait for all processes to finish before we continue
    for( unsigned int i = 0; i < num_threads; i++ ) {
        processes[i].join();
    }

    std::cout << "Done!" << std::endl;


    return 0;
}