#include <iostream>
#include "DataContainer.h"

#define DATAROW_LENGTH 4
typedef DataContainer< DATAROW_LENGTH > DataRow; 

void printAll(DataRow d1, DataRow d2, DataRow d3) {
    std::cout << std::endl;
    std::cout << "d1: "; d1.Print();
    std::cout << "d2: "; d2.Print();
    std::cout << "d3: "; d3.Print();
    std::cout << std::endl;
}
int main() { 
    DataRow d1, d2, d3; 
    d1.fill(10); d2.fill(20);
 
    d3 = d1 + d2; // Elementwise addition
    std::cout << "10+20 test: "; printAll(d1, d2, d3);
    d3 = d1 - d2; // Elementwise subtraction 
    std::cout << "10-20 test: "; printAll(d1, d2, d3);
    d3 = d1/5; // Divide all elements by a constant 
    std::cout << "10/5 test: "; printAll(d1, d2, d3);
    d3 += d1; // Compound assignment
    std::cout << "2+=10 test: "; printAll(d1, d2, d3);
    d3 -= d2; 
    std::cout << "12-=20 test: "; printAll(d1, d2, d3);
    /* d3 = d1.Pow(2); // Raise all elements to a constant power(d1 unchanged) */
    /* std::cout << "10^2 test: "; d3.Print(); */
    /* d3 = d2.Sqrt(); // Square root of element (d2 unchanged) */
    /* std::cout << "sqrt(20) test: "; d3.Print(); */
    return 0; 
}
