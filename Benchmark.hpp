//
//  Benchmark.hpp
//  Skewed Binary Search
//
//  Created by Matthew Varendorff on 25/5/2024.
//

#ifndef Benchmark_h
#define Benchmark_h

static void benchmark()
{
    //fill vector with numbers from 10^3 - 10^6-1 numbers
    std::vector<int> vec(std::pow(10, 6) - std::pow(10, 3));
    std::iota(vec.begin(), vec.end(), std::pow(10, 3));
    
    //benchmark skewed_lower_bound with in_bounds skewness
    auto start = std::chrono::high_resolution_clock::now();
    sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark 1: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    sbs::skewed_lower_bound(vec.begin(), vec.end(), std::pow(10, 6), std::less<int>());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark 2: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 2), std::less<int>());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark 3: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 7), std::less<int>());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark 4: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    
    //benchmark skewed_lower_bound with out_of_range skewness
    start = std::chrono::high_resolution_clock::now();
    sbs::skewed_find(vec.begin(), vec.end(), std::pow(10, 3), std::less<int>(), sbs::skewness::out_of_range);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark 5: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
}

#endif /* Benchmark_h */
