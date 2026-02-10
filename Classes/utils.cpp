#include "utils.h"
#include <iostream>
#include <iomanip>
string to_string_with_precision(const float a_value, const int percision )
{
    stringstream stream;
    stream << fixed << setprecision(percision) << a_value;
    return stream.str();
}
