#ifndef UTILS_HH
#define UTILS_HH 1
#include <iostream>
#include <vector>
template<typename T>
std::ostream& operator<<(std::ostream& stream,
                         const std::vector<T>& v)
{   
    for(auto& e: v){
        stream << e;
    }
    return stream;
}
#endif // UTILS_HH
