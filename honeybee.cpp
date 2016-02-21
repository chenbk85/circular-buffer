/* Author: Adam Werries, Email: awerries@cmu.edu
 *
 * Informal test program for DataContainer and StatisticsBuffer classes.
 */

// Debugging output
#include <iostream>
#include <iomanip>
#include <limits>
// Used by code to read in test data from CSV
#include <sstream>
#include <string>
#include <fstream>
// Custom classes
#include "DataContainer.h"
#include "StatisticsBuffer.h"

#define DATAROW_WIDTH 4
#define BUFFER_LENGTH 50
#define CHECK_INTERVAL 15
typedef DataContainer< DATAROW_WIDTH > DataRow; 

void printTest(std::string testname, DataRow d1, DataRow d2, DataRow d3) {
    std::cout << testname
              << "d1: " << d1 << ", "
              << "d2: " << d2 << ", "
              << "d3: " << d3 << std::endl;
}

template <size_t T_length, size_t T_width>
void printStatBufferInfo(StatisticsBuffer<T_length, T_width> statBuffer) {
    std::cout << "length " << statBuffer.currentLength() << ", ";
    std::cout << "Mean: " << statBuffer.getMean() << ", ";
    std::cout << "StdDev: " << statBuffer.getStdDev() << ", ";
    std::cout << "First row: " << statBuffer.getRow(0) << "; ";
    std::cout << "Last row: " << statBuffer.getRow(statBuffer.currentLength() - 1) << "; ";
    std::cout << "Latest row: " << statBuffer.getLatestRow() << std::endl;
}

void DataContainerTest1() {
    std::cout << "##### DataContainer Test1: Class functionality #####" << std::endl;

    // Test Assignment 1
    DataRow d1, d2, d3; 
    d1.fill(10); d2.fill(20);
 
    d3 = d1 + d2; // Elementwise addition
    printTest("d3=d1+d2 test: ", d1, d2, d3);
    d3 = d1 - d2; // Elementwise subtraction 
    printTest("d3=d1-d2test: ", d1, d2, d3);
    d3 = d1/5; // Divide all elements by a constant 
    printTest("d3=d1/5 test: ", d1, d2, d3);
    d3 += d1; // Compound assignment
    printTest("d3+=d1 test: ", d1, d2, d3);
    d3 -= d2; 
    printTest("d3-=d2test: ", d1, d2, d3);
    d3 = d1.Pow(2); // Raise all elements to a constant power(d1 unchanged)
    printTest("d3=d1^2 test: ", d1, d2, d3);
    d3 = d2.Sqrt(); // Square root of element (d2 unchanged)
    printTest("d3=sqrt(d2)test: ", d1, d2, d3);

    std::cout << std::endl << std::endl;
}

void StatisticsBufferTest1() {
    std::cout << "##### StatisticsBuffer Test1: Class functionality #####" << std::endl;

    StatisticsBuffer<BUFFER_LENGTH, DATAROW_WIDTH> statBuffer;

    // Uncomment to crash! (means the assert() is working for empty statBuffers)
    //statBuffer.getLatestRow();
    //statBuffer.getRow(0);
    std::cout << "Max length should be " << BUFFER_LENGTH << " and is " << statBuffer.maxLength() << std::endl;
    std::cout << "Current length should be 0 and is " << statBuffer.currentLength() << std::endl;
    std::cout << "isEmpty(): " << statBuffer.isEmpty() << std::endl;
    std::cout << "isFull(): " << statBuffer.isFull() << std::endl;
    
    // Simple test to show circular property of buffer and test functions
    std::cout << "After circular buffer fills, std-dev for THIS incrementing 'dataset' will remain constant." << std::endl;
    for (unsigned int i = 0; i < BUFFER_LENGTH*4  + 1; i++) {
        DataRow temp;
        temp.fill(i);
        temp[1] *= 2;
        temp[2] *= 3;
        temp[3] *= 4;
        statBuffer.addRow(temp);
        if (i != 0  && !(i % CHECK_INTERVAL)) {
            std::cout << "iteration " << i << ", ";
            printStatBufferInfo(statBuffer);
        }
    }
    std::cout << std::endl;
    std::cout << "isEmpty(): " << statBuffer.isEmpty() << std::endl;
    std::cout << "isFull(): " << statBuffer.isFull() << std::endl;

    std::cout << "Current length before removing one row: " << statBuffer.currentLength() << std::endl;
    statBuffer.removeRow();
    printStatBufferInfo(statBuffer);
    
    std::cout << "Removing rows 10 at a time.";
    while (!statBuffer.isEmpty()) {
        printStatBufferInfo(statBuffer);
        statBuffer.removeRows(10);
    }
    std::cout << "isEmpty(): " << statBuffer.isEmpty() << std::endl;
    std::cout << "isFull(): " << statBuffer.isFull() << std::endl;
    std::cout << std::endl << std::endl;
}

// Check accuracy of std-dev after 1000 data points sampled from Gaussian (mean 0.4, std-dev 0.5)
void StatisticsBufferTest2() {
    std::cout << "##### StatisticsBuffer Test2: Incremental computation accuracy #####" << std::endl;

    const size_t numDataPoints = 1000;
    std::array<double, numDataPoints> testdata;
    unsigned int arrayIndex = 0;
    std::ifstream infile("test_data.txt");
    std::string line = "";
    std::string::size_type sz;
    while (std::getline(infile, line)) {
        // convert to double and save
        testdata[arrayIndex] = std::stod(line, &sz);
        arrayIndex++;
    }

    // Compute accurate mean and std-dev
    double mean = 0;
    for (auto r: testdata) {
        mean += r;
    }
    mean /= numDataPoints;

    double std_sum = 0;
    double diff = 0;
    for (auto r: testdata) {
        diff = mean - r; 
        std_sum += diff*diff;
    }
    double stdDev = std::sqrt(std_sum/(numDataPoints-1));

    // Add all to StatisticsBuffer, output final incremental mean/stddev
    StatisticsBuffer<numDataPoints, 1> statBuffer;
    for (auto r: testdata) {
        DataContainer<1> temp;
        temp[0] = r;
        statBuffer += temp;
    }
    int precision = std::numeric_limits<double>::max_digits10;
    std::cout << "Max length should be " << numDataPoints
              << " and is " << statBuffer.maxLength() << std::endl;
    std::cout << "Current length should be " << numDataPoints 
              << " and is " << statBuffer.currentLength() << std::endl;

    std::cout << std::setprecision(precision)
              << "Mean should be " << mean
              << " and is: " << statBuffer.getMean()
              << ", with a difference of: " << mean - statBuffer.getMean()[0] << std::endl
              << "StdDev should be " << stdDev
              << " and is: " << statBuffer.getStdDev()
              << ", with a difference of: " << stdDev - statBuffer.getStdDev()[0] << std::endl
              << "First row: " << statBuffer.getRow(0) << "; "
              << "Last row: " << statBuffer.getRow(statBuffer.currentLength() - 1) << "; "
              << "Latest row: " << statBuffer.getLatestRow() << std::endl;
    std::cout << std::endl << std::endl;
}

int main() { 
    DataContainerTest1();
    StatisticsBufferTest1();
    StatisticsBufferTest2();
    return 0; 
}

