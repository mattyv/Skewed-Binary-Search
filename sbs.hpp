#ifndef sbs_h
#define sbs_h

#include <algorithm>

namespace sbs
{

enum class skewness { in_bounds, out_of_range };

//implementation of Andrei Alexandrescu's skewed binary search
template< class ForwardIt, class T, class Compare>
static ForwardIt out_of_range_lower_bound( ForwardIt first, ForwardIt last,
                                          const T& value, Compare comp )
{
    if (first == last) return last;
    auto middle = first + (last - first) / 2;
    if(comp(*middle, value))
    {
        //stay in upper half
        for(first = middle + 1; first < last; first = middle + 1 )
        {
            //skew middle to the right
            middle = first + 3 * (last - first) / 4;
            if(!comp(*middle, value))
            {
                last = middle;
                break;
            }
        }
    }
    else
    {
        //stay in lower half
        for(last = middle; first < last; last = middle )
        {
            //skew middle to the left
            middle = first + (last - first) / 4;
            if(comp(*middle, value))
            {
                first = middle + 1;
                break;
            }
        }
    }
    return std::lower_bound(first, last, value, comp);
}
template< class ForwardIt, class T, class Compare >
static ForwardIt skewed_lower_bound( ForwardIt first, ForwardIt last,
                                    const T& value, Compare comp , skewness skew = skewness::in_bounds)
{
    if (skew == skewness::in_bounds) {
        return std::lower_bound(first, last, value, comp);
    } else {
        return out_of_range_lower_bound(first, last, value, comp);
    }
}

template< class ForwardIt, class T, class Compare >
static ForwardIt skewed_lower_bound( ForwardIt first, ForwardIt last,
                                         const T& value, Compare comp ,
                                         const std::pair<size_t, size_t>& ratio, //first is the numerator, second is the denominator
                                         skewness skew = skewness::in_bounds)
{
     if(first == last) return last;
     const auto skewed_middle = first + ratio.first * (last - first) / ratio.second;
     //const auto middle = first + (last - first) / 2;
     //std::cout << "first: " << *first << " middle: " << *middle << " size: " << (last - first) << " skewed_middle: " << *skewed_middle << std::endl;
     if(comp(*skewed_middle, value))
         return skewed_lower_bound(skewed_middle, last, value, comp, skew);
     else
         return skewed_lower_bound(first, skewed_middle, value, comp, skew);
     
 }
 
template< class ForwardIt, class T, class Compare >
static ForwardIt skewed_find( ForwardIt first, ForwardIt last,
                             const T& value, Compare comp, skewness skew = skewness::in_bounds)
{
    auto it = skewed_lower_bound(first, last, value, comp, skew);
    if(it != last && !comp(value, *it))
    {
        return it;
    }
    return last;
}

template< class ForwardIt, class T, class Compare >
static ForwardIt skewed_find(ForwardIt first, ForwardIt last,
                                const T& value, Compare comp ,
                                const std::pair<size_t, size_t>& ratio, //first is the numerator, second is the denominator
                                skewness skew = skewness::in_bounds)
{
     auto it = skewed_lower_bound(first, last, value, comp, ratio, skew);
     if(it != last && !comp(value, *it))
     {
         return it;
     }
     return last;
 }
 
}

#endif /* sbs_h */
