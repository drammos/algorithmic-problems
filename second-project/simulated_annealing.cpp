#include "simulated_annealing.hpp"

using namespace std;

// Simulated Anneaning algorithm
/// @brief 
/// @param polygon 
/// @param L 
/// @param min_max 
/// @param threshold 
/// @param annealing 
/// @return 
Polygon_2D simulated_annealing(Polygon_2D polygon, int L, string min_max, double threshold, string annealing){
    Polygon_2D new_polygon = polygon;


    double temperature = 1;
    Points internal_points = polygon.vertices();
    int vertices_size = internal_points.size();
    Points result;

    // Create the convex hull
    CGAL::convex_hull_2(internal_points.begin(), internal_points.end(), std::back_inserter(result));
    Polygon_2D polygon_convex_hull;

    for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
        polygon_convex_hull.push_back(*iter);
    }

    // Area for convex hull 
    // The convex hull is same for all program
    double area_convex_hull = polygon_convex_hull.area();

    // Start energy for polygon
    double start_energy = energy(vertices_size, polygon.area(), area_convex_hull, min_max);


    while(temperature > 0){
        double new_energy;
        if(annealing.compare("local") == 0){
            new_energy = local_algorithm(new_polygon, area_convex_hull, vertices_size, min_max);
        }   
        else if(annealing.compare("global") == 0){
            cout << "hh" << endl;
        }
        else{
            cout << "hh" << endl;
        }
        temperature = temperature - (1/L);
    }

    return new_polygon;
}

// Local for simulated Annealing
/// @brief 
/// @param polygon 
/// @param area_convex_hull 
/// @param vertices_size 
/// @param min_max 
/// @return 
double local_algorithm( Polygon_2D polygon, double area_convex_hull, int vertices_size, string min_max){

    srand(time(NULL));
    int my_rand = rand();

    // Points vertices = polygon.
    int num_vertice = my_rand%vertices_size;


    VertexIterator vert_iter_point = polygon.vertices_begin() + num_vertice;
    VertexIterator vert_iter_point_before;
    VertexIterator vert_iter_point_next1;
    VertexIterator vert_iter_point_next2;

    // The first
    if( num_vertice == 0){
        vert_iter_point_before = polygon.vertices_end() - 1;
        vert_iter_point_next1 = polygon.vertices_begin() + 1;
        vert_iter_point_next2 = polygon.vertices_begin() + 2;   
    }
    // The last
    else if( num_vertice == vertices_size - 1 ){
        vert_iter_point_before = polygon.vertices_end() - 2;
        vert_iter_point_next1 = polygon.vertices_begin();
        vert_iter_point_next2 = polygon.vertices_begin() + 1; 
    }

    /// .... \./
    // The last -1
    else if(num_vertice == vertices_size - 2){
        vert_iter_point_before = polygon.vertices_end() - 3;
        vert_iter_point_next1 = polygon.vertices_end() - 1;
        vert_iter_point_next2 = polygon.vertices_begin();
    }
    // Any other
    else{
        vert_iter_point_before = vert_iter_point - 1;
        vert_iter_point_next1 = vert_iter_point + 1;
        vert_iter_point_next2 = vert_iter_point + 2;
    }
    Point_2 previous_point(vert_iter_point_before->x(), vert_iter_point_before->y());
    Point_2 point(vert_iter_point->x(), vert_iter_point->y());
    Point_2 next_point(vert_iter_point_next1->x(), vert_iter_point_next1->y());
    Point_2 next_2_point(vert_iter_point_next2->x(), vert_iter_point_next2->y());

    
    Fuzzy_iso_box box = create_box(previous_point, point, next_point, next_2_point);

    // tora prepei na checkareis an to neo polygon me tis nees akmes
    // dimiourgei ERROR for new edges
    // meta gurnas tin energeia autou tou polygonoun an ola kala
    

    vector<Point_2> points;
    Tree tree;
    tree.search( back_inserter(points), box);

    // Create new edges
    // edge previous_point with next_point e1
    // edge point with next_2_point e2


    // Segment_2 first_edge(prev);
    // Segment_2 second_edge();
    return 1.1;
}

// Create the box with min and max points from x and y
/// @brief
/// @param previous_point 
/// @param point 
/// @param next_point 
/// @param next_2_point 
/// @return 
Fuzzy_iso_box create_box(Point_2 previous_point, Point_2 point, Point_2 next_point, Point_2 next_2_point){

    // Create a vector from points and fine the point
    // With smallext x and Y and point with biggest x and y

    vector <Point_2> points;
    points = {
        previous_point,
        point,
        next_point,
        next_2_point
    };
    // FOR THE Y
    sort(points.begin(), points.end(), check_the_y);
    int small_y(points.begin()->hy());
    int big_y((points.end() - 1)->hy());

    // FOR THE X
    sort(points.begin(), points.end(), check_the_x);
    int small_x(points.begin()->hx());
    int big_x((points.end() - 1)->hx());

    // Create the smallest point and the biggest boint
    Point_2 smallest(small_x, small_y);
    Point_2 biggest(big_x, big_y);


    Fuzzy_iso_box box(smallest, biggest);
    return box;
}

// Check for x
/// @brief 
/// @param it1 
/// @param it2 
/// @return 
bool check_the_x(Points::iterator it1, Points::iterator it2){
    return it1->hx() < it2->hx();
}

// Check for y
/// @brief 
/// @param it1 
/// @param it2 
/// @return 
bool check_the_y(Points::iterator it1, Points::iterator it2){
    return it1->hy() < it2->hy();
}

// Energy for min or max
/// @brief
/// @param vertices_size 
/// @param area_polygon 
/// @param area_convex_hull 
/// @param min_max 
/// @return 
double energy(int vertices_size, double area_polygon, double area_convex_hull, string min_max){
    if(min_max.compare("-min") == 0){
        return vertices_size*(area_polygon/area_convex_hull);
    }
    else{
        return vertices_size*(1 - (area_polygon/area_convex_hull));
    }
}