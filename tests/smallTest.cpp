#include <iostream>

// Define a template class with a static member variable
template <double Value>
struct DoubleValue {
    static constexpr double value = Value;
};

int main() {
    // Use the DoubleValue template with a specific double value
    using MyDouble = DoubleValue<3.14>;

    // Access the static member variable
    std::cout << MyDouble::value << std::endl; // Output: 3.14

    return 0;
}
