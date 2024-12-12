//
// Created by dideldumm on 15.11.24.
//

#include <algorithm>
#include <cstddef>
#include <utility>

template <class Iterator, class PolygonTraits>
void make_simple_polygon(Iterator points_begin, Iterator points_end,
                         const PolygonTraits& polygon_traits)
{
    std::pair<std::ptrdiff_t,std::ptrdiff_t> swap_interval;

#if defined(CGAL_POLY_GENERATOR_DEBUG)
    Iterator it;
    std::cout << "In make_simple_polygon the points are: " << std::endl;
    int size = 0;
    for (it = points_begin; it != points_end; it++, size++)
        std::cout << *it << " ";
    std::cout << std::endl;
#endif


    do {
        swap_interval = check_simple_polygon(points_begin,
                                             points_end, polygon_traits);
#if defined(CGAL_POLY_GENERATOR_DEBUG)
        std::cout << "To swap: " << swap_interval.first << " "
                                 << swap_interval.second << std::endl;
        CGAL_assertion(swap_interval.first >= -1 &&
                               swap_interval.second >= -1 &&
                               swap_interval.first < size &&
                               swap_interval.second < size);
#endif
        // will break out when a negative nonsense value is selected
        // or with -1 is given indicating that the polygon was simple.
        // For positive nonsense values, one needs to know the how
        // many points there are...
        if (swap_interval.first <= -1 || swap_interval.second <= -1)
            break;
        // swap with vertex_data.conflict1, vertex_data.conflict2;
        Iterator b = points_begin;
        std::ranges::advance(b, swap_interval.first+1);
        Iterator e = b;
        std::advance(e, swap_interval.second-swap_interval.first);
        std::reverse(b, e);
    } while (true);
}
