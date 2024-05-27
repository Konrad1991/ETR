#include <stdexcept>
#include <type_traits>
#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

void test_basestore() {
  // NOTE: test nothing allocated
  {
    std::string s = "BaseStoreTestsNotAllocated: ";
    BaseStore<double> bs;
    try {
      bs[0];
    } catch (std::runtime_error &e) {
      std::string expected = "No memory was allocated";
      ass(e.what() == expected, s + "nothing allocated");
    }
    ass(bs.size() == 0, s + "size");
    ass(bs.capacity == 0, s + "capacity");
    ass(bs.im() == false, s + "im");
    ass(bs.nc() == 0, s + "nc");
    ass(bs.nr() == 0, s + "nr");
    ass(bs.allocated == false, s + "allocated");
  }
}

int main(int argc, char *argv[]) {
  test_basestore();
  return 0;
}
