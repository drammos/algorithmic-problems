#include "subdivision.hpp"
#include "simulated_annealing.hpp"
#include "convex_hull_algorithmic.hpp"
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
    if(start == 0){
        start = -1;
    }
    // Check for left side
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
Polygon_2D subdivision(vector<Point_2> points, int L, string min_max){
    // RANDOM for 100<= m <= 1000 

    random_device random_;
    mt19937 generate_(random_());    
    uniform_int_distribution<> dis_(100, 1000);
    int m = dis_(generate_);

   
    // Sort the points
    sort(points.begin(), points.end(), check_the_x);

    vector<struct Spal*> spals;
    int vertices_size = points.size();
    int i_vertices = 0;
    int num = 0;
    int num_from_spal = 1;
    

    bool last = false;
    while(true){
        Spal* spal = new struct Spal;
        spal->is_first = false;
        spal->is_last = false;
        spal->number = num_from_spal;
        int num = 1;
                
        for(int i = i_vertices; i < points.size(); i++){    
            // Add point in points for spal
            Point_2 point = points.at(i);
            spal->points.push_back(point);

            // Check is first and save it
            if(num == 1){
                spal->first_in_spal = i;
                if(i == 0){
                    spal->left = point;
                    spal->is_first = true;
                }
                else{
                    // is the first from new spal
                    spal->left = point;
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
                if(find_lowers){
                    spal->right = point;
                    i_vertices = i;
                    break;
                }
            }
            num++;
        }   
        spals.push_back(spal);
        num_from_spal++;
        if(last){
            break;
        }

    }


    for(int num = 0; num < spals.size(); num++){
        Spal* spal = spals.at(num);
        vector<Point_2> spal_points = spal->points;
        Points result;

        // Create the convex hull
        CGAL::convex_hull_2(spal_points.begin(), spal_points.end(), std::back_inserter(result));
        // Create the polygon
        Polygon_2D polygon;
        for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
            polygon.push_back(*iter);
        }


        if(!polygon.is_clockwise_oriented()){
            polygon.reverse_orientation();
        }
        result = polygon.vertices();

        if(spal->is_first){
            Point_2 right_point = spal->right;          
            
            for(int i = 0; i < result.size(); i++){
                
                Point_2 the_point = result.at(i);
                if(right_point == the_point){
                    if( i == result.size() - 1){
                        Point_2 next = result.at(0);
                        spal->edge_right = Segment_2(next, right_point);
                    }
                    else{
                        Point_2 next = result.at(i+1);
                        spal->edge_right = Segment_2(next, right_point);
                    }
                }
            }
        }
        else if(spal->is_last){
            Point_2 left_point = spal->left;          
            
            for(int i = 0; i < result.size(); i++){
                
                Point_2 the_point = result.at(i);
                if(left_point == the_point){
                    if( i == 0){
                        Point_2 next = result.at(result.size() - 1);
                        spal->edge_left = Segment_2(left_point, next);
                    }
                    else{
                        Point_2 next = result.at(i+1);
                        spal->edge_left = Segment_2(left_point, next);
                    }
                }
            }

        }
        else{
            Point_2 right_point = spal->right;          
            Point_2 left_point = spal->left;
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
                        Point_2 next = result.at(result.size() - 1);
                        spal->edge_left = Segment_2(left_point, next);
                    }
                    else{
                        Point_2 next = result.at(i+1);
                        spal->edge_left = Segment_2(left_point, next);
                    }
                }
            }
            // vrisko akmes kai gia ta duo
        }

        Polygon_2D new_polygon_convex;
        Segment_2* edge1;
        Segment_2* edge2;

        // Call convex hull algorithm
        if(spal->is_first){
            edge1 =  new Segment_2;
            *edge1 = spal->edge_right;
            edge2 = nullptr;

            new_polygon_convex = convex_hull(spal->points, 1, edge1, edge2);

        }
        else if(spal->is_last){
            edge2 =  new Segment_2;
            *edge2 = spal->edge_left;
            edge1 = nullptr;

            new_polygon_convex = convex_hull(spal->points, 1, edge1, edge2);
        }
        else{
            edge1 =  new Segment_2;
            *edge1 = spal->edge_right;
            edge2 =  new Segment_2;
            *edge2 = spal->edge_left;

            new_polygon_convex = convex_hull(spal->points, 1, edge1, edge2);
        }

        // Call global
        Polygon_2D new_pol_simulated = simulated_annealing(new_polygon_convex, L, min_max, "global", edge1, edge2);        
        
        if(!new_pol_simulated.is_clockwise_oriented()){
            new_pol_simulated.reverse_orientation();
        }

        spal->points_polygon = new_pol_simulated.vertices();
    }

    Points last_points_list;

    for(int num = 0; num < spals.size(); num++){
        Spal* spal = spals.at(num);
        Points points_polygon = spal->points_polygon;
        Point_2 left = spal->left;
        Point_2 right = spal->right;

        int start = 0;
        for(int i = 0; i < points_polygon.size(); i++){
            if(left == points_polygon.at(i)){
                last_points_list.push_back(left);
                start = i + 1;
                break;
            }
        }

        // start
        bool find_right = false;
        for(int i = start; i < points_polygon.size(); i++){
            Point_2 point = points_polygon.at(i);
            if(right == point){
                find_right = true;
                break;
            }
            last_points_list.push_back(point);
        }

        if(!find_right){
            for(int i = 0; i < points_polygon.size(); i++){
                Point_2 point = points_polygon.at(i);
                if(right == point){
                    break;
                }
                last_points_list.push_back(point);
            }
        }
    }

    // exo valei ola ta panw ta aristera kathena left kai ta koina
    // tora eimai terma deksia sto arisero tou teleutaiou kai prepei na to kanw anapoda
    int inter = last_points_list.size() - 1;
    for(int num = spals.size() - 1; num >= 0; num--){
        Spal* spal = spals.at(num);
        Points points_polygon = spal->points_polygon;
        Point_2 left = spal->left;
        Point_2 right = spal->right;

        int start = 0;
        for(int i = 0; i < points_polygon.size(); i++){
            if(right == points_polygon.at(i)){
                if(spal->is_last){
                    last_points_list.push_back(right);
                }
                start = i + 1;
                break;
            }
        }

        // start
        bool find_left = false;
        for(int i = start; i < points_polygon.size(); i++){
            Point_2 point = points_polygon.at(i);
            if(left == point){
                find_left = true;
                break;
            }

            last_points_list.push_back(point);
        }

        if(!find_left){
            for(int i = 0; i < points_polygon.size(); i++){
                Point_2 point = points_polygon.at(i);
                if(left == point){
                    break;
                }

                last_points_list.push_back(point);
            }
        }
    }

    Polygon_2D polygon_last;

    for (pveciterator iter=last_points_list.begin(); iter!=last_points_list.end(); ++iter){
        polygon_last.push_back(*iter);
    }  

    return polygon_last;
}