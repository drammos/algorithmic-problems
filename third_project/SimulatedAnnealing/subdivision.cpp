#include "subdivision.hpp"
#include "simulated_annealing.hpp"
#include "../PolygonsAlgorithm/convex_hull_algorithmic.hpp"
#include <random>
using namespace std;

struct Spal{
    Point_2 left;
    Point_2 right;
    Segment_2 edge_left;
    Segment_2 edge_right;
    vector<Point_2> points;
    vector<Point_2> points_polygon;
    int number; 
    int first_in_spal;
    bool is_last;
    bool is_first;
};

/// @brief 
/// @param i 
/// @param start 
/// @param points 
/// @return 
bool check_for_lowers(int i, int start, vector<Point_2> points){

    bool find = false;
    Point_2 point = points.at(i);
    for(int num = start + 1; num < i; num++){
        Point_2 p = points.at(num);
        if(p.y() < point.y()){
            find = true;
            break;
        }
    }
    if(!find){
        return false;
    }
    
    find = false;
    // Check for right side
    for(int num = i + 1; num < points.size(); num++){
        Point_2 p = points.at(num);
        if(p.y() < point.y()){
            find = true;
            break;
        }
    }

    return find;
}


/// @brief
/// @param points 
/// @param L 
/// @param min_max 
/// @param threshold 
/// @return 
Polygon_2D subdivision(vector<Point_2> points, int L, string min_max, int cut_off){
    // RANDOM for 10<= m <= 100 

    random_device random_;
    mt19937 generate_(random_());    
    uniform_int_distribution<> dis_(10, 100);
    int m = dis_(generate_);
    m= 29;
   
    // Sort the points
    sort(points.begin(), points.end(), check_the_x);

    vector<struct Spal*> spals;
    int vertices_size = points.size();
    int i_vertices = 0;
    int num_from_spal = 1;
    
    bool last = false;
    while(true){
        Spal* spal = new struct Spal;
        spal->is_first = false;
        spal->is_last = false;
        spal->edge_left = Segment_2(Point_2(0,0),Point_2(0,1));
        spal->edge_right = Segment_2(Point_2(0,0),Point_2(0,1));

        spal->number = num_from_spal;
        int num = 1;
        int time_start1 = clock();     
        for(int i = i_vertices; i < points.size(); i++){    
            // Add point in points for spal
            Point_2 point = points.at(i);
            spal->points.push_back(point);

            // Check is first and save it
            if(num == 1){
                spal->left = point;
                spal->first_in_spal = i;
                if(i == 0){
                    spal->is_first = true;
                }
                else{
                    spal->is_first = false;
                }
            }
            //an den exoume gemisei me ta m pou prepei
            if(num >= m){
                // CHECK FOR THE OTHE POINTS IN LIST 
                int difference_from_end = points.size() - i;
                // Check for the last spal
                if (difference_from_end < m){
                    spal->is_last = true;
                    for( int start_is = i + 1; start_is < points.size(); start_is++){
                        Point_2 the_point = points.at(start_is);
                        spal->points.push_back(the_point);
                    }                 
                    spal->right = points.at(points.size() - 1);
                    last = true;
                    break;
                }
                // Check for lowers points from left and right side in pointset
                bool find_lowers =  check_for_lowers(i, spal->first_in_spal, points);
                if(find_lowers == true){
                    spal->right = point;
                    i_vertices = i;
                    break;
                }
            }
            num++;
        }   
        spals.push_back(spal);
        
        int time_end1 = clock();
        int time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        num_from_spal++;
         
        if(last == true){
            break;
        }

    }

    for(int num = 0; num < spals.size(); num++){
        Spal* spal = spals.at(num);
        vector<Point_2> spal_points = spal->points;

        Points result1;

        // Create the convex hull
        CGAL::convex_hull_2(spal_points.begin(), spal_points.end(), std::back_inserter(result1));

        // Create the polygon
        Polygon_2 polygon_1;
        int time_start1 = clock();
        for (pveciterator iter=result1.begin(); iter!=result1.end(); ++iter){
            polygon_1.push_back(*iter);
        }

        if(!polygon_1.is_clockwise_oriented()){
            polygon_1.reverse_orientation();
        }

        // Vector with internals_points
        vector<Point_2> internal_points;
        
        // Find internal points
        for(int i = 0; i < points.size(); i++){
            Point_2 point = points.at(i);
            bool find = false;
            for (pveciterator iter=result1.begin(); iter!=result1.end(); ++iter){
                if( point == *iter){
                    find = true;
                    break;
                }
            }
            if( find == false){
                internal_points.push_back(point);
            }
        }

        Points remove_points;

        for(int i=0; i < internal_points.size(); i++){
            Point_2 point = internal_points.at(i);
            for(
                EdgeIterator edge = polygon_1.edges_begin();
                edge != polygon_1.edges_end();
                edge++
            ){
                if(edge->has_on(point)){

                    for(VertexIterator itr = polygon_1.vertices_begin();
                        itr != polygon_1.vertices_end();
                        itr++
                    ){
                        if( itr->x() == edge->point(1).x() && itr->y() == edge->point(1).y()){
                            polygon_1.insert(itr, point);
                            break;         
                        }    
                    }

                    remove_points.push_back(point);
                    break;
                }

            }

        }


        for(int i = 0; i < remove_points.size(); i++){
            Point_2 point = remove_points.at(i);
            for(VertexIterator itr = internal_points.begin();
                itr != internal_points.end();
                itr++
            ){
                if( itr->x() == point.x() && itr->y() == point.y()){
                    internal_points.erase(itr);
                    break;
                }
            }
        }

        int time_end1 = clock();
        int time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        Points result = polygon_1.vertices();

        Point_2 right_point = spal->right;          
        Point_2 left_point = spal->left;

        time_start1 = clock();
        for(int i = 0; i < result.size(); i++){
            Point_2 the_point = result.at(i);
            if(right_point == the_point){

                if( i == result.size() - 1){
                    Point_2 next = result.at(0);
                    spal->edge_right = Segment_2(right_point, next);
                }
                else{
                    Point_2 next = result.at(i+1);
                    spal->edge_right = Segment_2(right_point, next);
                }
            }

            if(left_point == the_point){
                if( i == 0){
                    Point_2 previous = result.at(result.size() - 1);
                    spal->edge_left = Segment_2(left_point, previous);
                }
                else{
                    Point_2 previous = result.at(i-1);
                    spal->edge_left = Segment_2(left_point, previous);
                }
            }

        }
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }
        Polygon_2D new_polygon_convex;
        Segment_2 el = spal->edge_left;
        Segment_2 er = spal->edge_right;
        time_start1 = clock();
        
        new_polygon_convex = convex_hull(internal_points, 1, &polygon_1, false,  &el, &er);
        
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        if(!new_polygon_convex.is_clockwise_oriented()){
            new_polygon_convex.reverse_orientation();
        }

        Polygon_2D p1 = new_polygon_convex;

        time_start1 = clock();
        // Call global
        Polygon_2D new_pol_simulated = simulated_annealing(new_polygon_convex, L, min_max, "global", &spal->edge_right, &spal->edge_left, cut_off);        

        if(!new_pol_simulated.is_clockwise_oriented()){
            new_pol_simulated.reverse_orientation();
        }
        spal->points_polygon = new_pol_simulated.vertices();  
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }  
    }

    Points last_points_list;
    Polygon_2D last_p1;

    for(int num = 0; num < spals.size(); num++){
        Spal* spal = spals.at(num);
        Points points_polygon = spal->points_polygon;
        
        
        Point_2 left = spal->left; // aristera
        Point_2 right = spal->right; // dekia


        int start = 0;
        int time_start1 = clock();
        for(int i = 0; i < points_polygon.size(); i++){
            if(left == points_polygon.at(i)){
                last_points_list.push_back(left);
                start = i + 1;
                break;
            }
        }
        int time_end1 = clock();
        int time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        // start
        bool find_right = false;
        time_start1 = clock();
        for(int i = start; i < points_polygon.size(); i++){
            Point_2 point = points_polygon.at(i);
            if(right == point){
                find_right = true;
                break;
            }
            last_points_list.push_back(point);
        }
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }
        
        
        //
        time_start1 = clock();
        if(find_right == false){
            for(int i = 0; i < points_polygon.size(); i++){
                Point_2 point = points_polygon.at(i);
                if(right == point){
                    break;
                }
                last_points_list.push_back(point);
            }
        }
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }
    }

    int inter = last_points_list.size() - 1;
    for(int num = spals.size() - 1; num >= 0; num--){
        Spal* spal = spals.at(num);
        Points points_polygon = spal->points_polygon;
        Point_2 left = spal->left;
        Point_2 right = spal->right;

        int start = 0;
        int time_start1 = clock();
        for(int i = 0; i < points_polygon.size(); i++){
            if(right == points_polygon.at(i)){
                if(spal->is_last == true){
                    last_p1.push_back(right);
                    last_points_list.push_back(right);
                }
                start = i + 1;
                break;
            }
        }

        int time_end1 = clock();
        int time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        

        // start
        bool find_left = false;
        time_start1 = clock();
        for(int i = start; i < points_polygon.size(); i++){
            Point_2 point = points_polygon.at(i);
            if(left == point){
                find_left = true;
                break;
            }
            last_points_list.push_back(point);
        }
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

        time_start1 = clock();
        if(!find_left){
            for(int i = 0; i < points_polygon.size(); i++){
                Point_2 point = points_polygon.at(i);
                if(left == point){
                    break;
                }
                last_points_list.push_back(point);
            }
        }
        time_end1 = clock();
        time1 = time_end1 - time_start1;
        cut_off -= time1;
        if(cut_off < 0){
            exit(EXIT_FAILURE);
        }

    }

    Polygon_2D polygon_last;

    for (pveciterator iter=last_points_list.begin(); iter!=last_points_list.end(); ++iter){
        polygon_last.push_back(*iter);
    }  

    // local


    if(!polygon_last.is_collinear_oriented()){
        polygon_last.reverse_orientation();
    }

    return polygon_last;
}