#include "subdivision.hpp"
#include "simulated_annealing.hpp"

using namespace std;


/// @brief
/// @param points 
/// @param L 
/// @param min_max 
/// @param threshold 
/// @return 
Polygon_2D subdivision(vector<Point_2> points, int L, string min_max, double threshold){
    int m = 10;
    
    // Sort the points
    sort(points.begin(), points.end(), check_the_x);
    // Gia arxi
    // xorizo se temaxia
    // opou prepei to aristero x na xei aristera&deksia ena x pio xamilo toulaxtstion
    // an m dn to ikanopoiei m, m+1, m+...
    //apothikeuo to struct mou me akmes

    // for
    Polygon_2D polygon;

    return polygon;
}
