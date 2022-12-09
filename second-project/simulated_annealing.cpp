#include "simulated_annealing.hpp"

using namespace std;


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


// Check the polygon with box
bool check_the_polygon(Polygon_2D polygon, vector<Point_2> box_points){
    bool flag_1 = true;
    for(int i = 0; i < box_points.size(); i++) {
        Point_2 box_point = box_points.at(i);
        Segment_2 edge1;
        Segment_2 edge2;
        Point_2 same_point;
        
        // Find the edge for box_point
        for( 
            VertexIterator iter = polygon.vertices_begin();
            iter != polygon.vertices_end();
            iter++
        ) {
            Point_2 point(iter->x(), iter->y());
            if(point == box_point){
                if(iter == polygon.vertices_begin()){
                    VertexIterator iter_prev = polygon.end() - 1;
                    VertexIterator iter_next = polygon.begin() + 1;
                    Point_2 previous_point(iter_prev->x(), iter_prev->y());
                    Point_2 next_point(iter_next->x(), iter_next->y());

                    edge1 =  Segment_2(previous_point, point);
                    edge2 = Segment_2(point, next_point);
                    same_point = point;
                }
                else if( iter == polygon.vertices_end() - 1){
                    VertexIterator iter_prev = polygon.end() - 2;
                    VertexIterator iter_next = polygon.begin();
                    Point_2 previous_point(iter_prev->x(), iter_prev->y());
                    Point_2 next_point(iter_next->x(), iter_next->y());

                    edge1 =  Segment_2(previous_point, point);
                    edge2 = Segment_2(point, next_point);
                    same_point = point;
                }
                else{
                    VertexIterator iter_prev = iter - 1;
                    VertexIterator iter_next = iter + 1;
                    Point_2 previous_point(iter_prev->x(), iter_prev->y());
                    Point_2 next_point(iter_next->x(), iter_next->y());

                    edge1 =  Segment_2(previous_point, point);
                    edge2 = Segment_2(point, next_point);
                    same_point = point;
                }


            }
        }

        // I have the edge1 and edge2 for box_point
        // Check the edges for new_polygon

        // Check for the edges and internalpoints
        // Because the polygon must be simple every time
        for(const Segment_2& e :polygon.edges()){

            Point_2 first_point = e.point(0);
            Point_2 second_point = e.point(1);

            Point_2 p_1;
            if( edge1.point(0) != same_point){
                p_1 = edge1.point(0);
            }
            else{
                p_1 = edge1.point(1);
            }
            Point_2 p_2;
            if( edge2.point(0) != same_point){
                p_2 = edge2.point(0);
            }
            else{
                p_2 = edge2.point(1);
            }

            // For the same points in differents eges
            if( first_point != p_1 && second_point != p_1 && first_point != same_point && second_point != same_point){
                if(CGAL::do_intersect(edge1, e) == true){
                    return false;
                }
            }
    
            // For the same points in differents eges
            if( first_point != p_2 && second_point != p_2 && first_point != same_point && second_point != same_point){
                if(CGAL::do_intersect(edge2, e) == true){
                    return false;
                }
            }
        }

    }
    return true;
}

// Local for simulated Annealing
/// @brief 
/// @param polygon 
/// @param vertices_size 
/// @param points 
/// @return 
Polygon_2D local_algorithm(Polygon_2D polygon, int vertices_size, vector<Point_2> points){

    srand(time(NULL));
    bool result;
    Polygon_2D new_polygon;

    do{
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

        // Check for new edge
        Segment_2 seg1(previous_point, next_point);
        Segment_2 seg2(point, next_2_point);
        if(CGAL::do_intersect(seg1, seg2) == true){
            result = false;
            continue;
        }
        
        Fuzzy_iso_box box = create_box(previous_point, point, next_point, next_2_point);

        

        vector<Point_2> points_in_box;

        // Create tree and find the points in box
        Tree tree;
        tree.insert(points.begin(), points.end());
        tree.search( back_inserter(points_in_box), box);


        // Delete point where find from rand()
        // And the polygon create automatic new edge with previous & next 
        new_polygon = polygon;
        new_polygon.erase(vert_iter_point);

        // Add again the point before the next_2_point
        new_polygon.insert(vert_iter_point_next2, point);

        result = check_the_polygon(new_polygon, points_in_box);
    } while(result == false);

    return new_polygon;
}

/// Gloabl step algorithm
/// @brief 
/// @param pol 
/// @param min_max 
/// @return 
Polygon_2D global_step(Polygon_2D pol, string min_max){
    srand(time(NULL));
    vector<Point_2> vertices;
    for(const Point_2& v  : pol.vertices())
        vertices.push_back(v);

    bool valid = false;
    Polygon_2D new_pol;
    while(valid == false){
        new_pol = pol;

        int size = vertices.size();
        int first = rand() % size;
        int second = rand() % size;

        while(second == first || second == first-1 || (second == 0 && first == size-1)){
            first = rand() % size;
            second = rand() % size;
        }

        for(VertexIterator vit = new_pol.vertices_begin(); vit != new_pol.vertices_end(); vit++){
            if(vit->x() == vertices.at(first).x() && vit->y() == vertices.at(first).y()){
                new_pol.erase(vit);
                break;
            }
        }

        for(VertexIterator vit = new_pol.vertices_begin(); vit != new_pol.vertices_end(); vit++){
            if(vit->x() == vertices.at(second).x() && vit->y() == vertices.at(second).y()){
                Point_2 point = vertices.at(first);
                new_pol.insert(vit, point);
                break;
            }
        }

        if(new_pol.is_simple()){
            valid = true;
        }
    }

    return new_pol;
    
}

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
    double polygon_energy = energy(vertices_size, polygon.area(), area_convex_hull, min_max);

    while(temperature > 0){
        double new_energy;
        Polygon_2D new_pol;
        if(annealing.compare("local") == 0){
            new_pol = local_algorithm(new_polygon, vertices_size, internal_points);
        }   
        else if(annealing.compare("global") == 0){
            new_pol = global_step(new_polygon, min_max);
        }
        else{
            cout << "hh" << endl;
        }

        // Energy for new
        double new_pol_energy = energy(vertices_size, new_pol.area(), area_convex_hull, min_max);
        double def_energy = new_pol_energy - polygon_energy;
        if(def_energy < 0){
            new_polygon = new_pol;
        }
        else{
            new_polygon = new_pol;
        }
        temperature = temperature - (1/L);
    }

    return new_polygon;
}

