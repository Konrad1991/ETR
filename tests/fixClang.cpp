#define STANDALONE_ETR
// ##include "../include/etr.hpp"
#include "../include/etr_bits/Core.hpp"
#include "../include/etr_bits/BinaryCalculations.hpp"

#include "../include/etr_bits/Allocation.hpp"
#include "../include/etr_bits/SEXPConversions.hpp"
#include "../include/etr_bits/Printing.hpp"
#include "../include/etr_bits/Coca.hpp"
#include "../include/etr_bits/Helper.hpp"
#include "../include/etr_bits/Interpolation.hpp"
#include "../include/etr_bits/Subsetting.hpp"
#include "../include/etr_bits/UnaryCalculations.hpp"

#include "../include/etr_bits/BufferVector.hpp"
#include "../include/etr_bits/Derivatives/Derivs.hpp"

using namespace etr;

int main() {
	Vec<double> v = coca(1, 2, 3);
	print(v);
	v = coca(2, 7, 9) + coca(4.5, 6, 7);

	Vec<double> a, b;
    etr::AllVars<2, 0, 0> av(1, 0);
    av.initBuffer(&a, &b);
    Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
    Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

    a = etr::coca(1, 2, 3);
    b = etr::coca(4, 5, 6);

}
