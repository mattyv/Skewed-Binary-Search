//
//  Tests.hpp
//  Skewed Binary Search
//
//  Created by Matthew Varendorff on 25/5/2024.
//

#ifndef Tests_h
#define Tests_h

#include "sbs.hpp"
#include <vector>
#include <numeric>

template<typename T>
static void test(T a, T b, const char* message, int line)
{
    if(a != b)
    {
        std::cout << message << " " << a << " != " << b << " @ line: " << line << std::endl;
        exit(1);
    }
}

static void test(bool condition, const char* message, int line)
{
    if(!condition)
    {
        std::cout << message << " @ line: " << line << std::endl;
        exit(1);
    }
}

static void test_failure(bool condition, const char* message, int line)
{
   test(!condition, message, line);
}

static void run_tests()
{
    //fill vector with numbers from 10^3 - 10^6-1 numbers
    std::vector<int> vec(std::pow(10, 6) - std::pow(10, 3));
    std::iota(vec.begin(), vec.end(), std::pow(10, 3));
    
    //test skewed_lower_bound with in_bounds skewness
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>()) == vec.begin(), "Failed test 1", __LINE__);
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 6), std::less<int>()) == vec.end(), "Failed test 2", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 2), std::less<int>()) == vec.begin(), "Failed test 3", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 7), std::less<int>()) == vec.begin(), "Failed test 4", __LINE__);
    
    //test skewed_lower_bound with out_of_range skewness
    test(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>(), sbs::skewness::out_of_range) == vec.begin(), "Failed test 3", __LINE__);
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 6), std::less<int>(), sbs::skewness::out_of_range) == vec.end(), "Failed test 4", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 2), std::less<int>(), sbs::skewness::out_of_range) == vec.begin(), "Failed test 5", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 7), std::less<int>(), sbs::skewness::out_of_range) == vec.begin(), "Failed test 6", __LINE__);
    
    //test skewed lower bound with ratio
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>(), {1,4}) == vec.begin(), "Failed test 7", __LINE__);
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 6), std::less<int>(), {3,4}) == vec.end(), "Failed test 8", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 2), std::less<int>(), {1,4}) == vec.begin(), "Failed test 9", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 7), std::less<int>(), {3,4}) == vec.begin(), "Failed test 10", __LINE__);
    
    //test skewed lower bound with ratio and out of range
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>(), {1,4}, sbs::skewness::out_of_range) == vec.begin(), "Failed test 11", __LINE__);
    test(sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 6), std::less<int>(), {3,4}, sbs::skewness::out_of_range) == vec.end(), "Failed test 12", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 2), std::less<int>(), {1,4}, sbs::skewness::out_of_range) == vec.begin(), "Failed test 13", __LINE__);
    test_failure(sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 7), std::less<int>(), {3,4}, sbs::skewness::out_of_range) == vec.begin(), "Failed test 14", __LINE__);
    
}
#endif /* Tests_h */
