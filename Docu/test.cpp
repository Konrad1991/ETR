#include <iostream>
#include <thread>

template<int N>
class MyClass {
public:
    static constexpr int constantValue = N;
};

void threadFunction() {
    std::cout << "Thread ID: " << std::this_thread::get_id() 
              << " - Constant Value: " << MyClass<2>::constantValue << std::endl;
}

int main() {
    
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    return 0;
}
