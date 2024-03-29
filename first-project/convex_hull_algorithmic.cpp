#include "convex_hull_algorithmic.hpp"

// Algorithmic for edge with Min Area
Polygon_2 min_area(vector<Point_2> internal_points, Polygon_2 polygon){
    
    while( !internal_points.empty() ){
        
        
        // min area is MAX 
        double min_area = numeric_limits<double>::max();
        Point_2 internal_point;
        Segment_2 edge;
        int num_internal_point = 0;

        for(const Segment_2& e  : polygon.edges()){

            // min distance is MAX            
            double min_distance = numeric_limits<double>::max();
            Point_2 internal_point_to_choise;

            int num_internal_point_to_choise = 0;
            bool flag_find_point = false;


            Point_2 p_1 = e.point(0);
            Point_2 p_2 = e.point(1);

            // I will find the internal point with minimum distance from edge
            // And I will save it
            for(int i=0; i < internal_points.size(); i++){
                Point_2 point = internal_points.at(i);

                bool flag = false;

                Segment_2 seg1( p_1, point);
                Segment_2 seg2( p_2, point);

                // Check for the edges and internalpoints
                // Because the polygon must be simple every time
                for(const Segment_2& edge_ :polygon.edges()){

                    Point_2 first_point = edge_.point(0);
                    Point_2 second_point = edge_.point(1);

                    // For the same points in differents eges
                    if( first_point != p_1 && second_point != p_1){
                        if(CGAL::do_intersect(seg1, edge_) == true){
                            flag = true;
                            break;
                        }
                    }

                    // For the same points in differents eges
                    if( first_point != p_2 && second_point != p_2){
                        if(CGAL::do_intersect(seg2, edge_) == true){
                            flag = true;
                            break;
                        }
                    }

                }
                
                // If flag == true continue with next internal point
                if( flag == true){
                    continue;
                }
    
                // Find the distance
                double distance = CGAL::squared_distance(e, point);

                
                if( distance < min_distance){
                    flag_find_point = true;
                    min_distance = distance;
                    internal_point_to_choise = point;
                    num_internal_point_to_choise = i;
                }
            }  

            // If you save internal point for the edge -e
            if(flag_find_point == true){
                Point_2 p1 = e.point(0);
                Point_2 p2 = e.point(1);
                
                // I will find the area for p1, p2 and internal_point_to_choise
                double area = CGAL::area( p1, p2, internal_point_to_choise);

                // Min Area
                if( area < min_area){
                    min_area = area;
                    internal_point = internal_point_to_choise;
                    num_internal_point = num_internal_point_to_choise;
                    edge = e;
            
                }
            }
        }

        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);

        // Take the points from edge
        Point_2 p1 = edge.point(0);
        Point_2 p2 = edge.point(1);


        
        VertexIterator iter;
        for( 
            iter = polygon.vertices_begin();
            iter != polygon.vertices_end();
            ++iter
        ){
            if( iter->x() == p2.x() && iter->y() == p2.y()){
                break;
            }
        }

        // Change the polygon
        polygon.insert(iter, internal_point);

    }

    return polygon;
}

// Algorithmic for edge with Max Area
Polygon_2 max_area(vector<Point_2> internal_points, Polygon_2 polygon){
    
    while( !internal_points.empty() ){
        
        // max area is MAX 
        double max_area = numeric_limits<double>::min();
        Point_2 internal_point;
        Segment_2 edge;
        int num_internal_point = 0;

        for(const Segment_2& e  : polygon.edges()){

            // min distance is MAX            
            double min_distance = numeric_limits<double>::max();
            Point_2 internal_point_to_choise;

            int num_internal_point_to_choise = 0;
            bool flag_find_point = false;

            Point_2 p_1 = e.point(0);
            Point_2 p_2 = e.point(1);
            // I will find the internal point with minimum distance from edge
            // And I will save it
            for(int i=0; i < internal_points.size(); i++){
                Point_2 point = internal_points.at(i);


                bool flag = false;

                Segment_2 seg1( p_1, point);
                Segment_2 seg2( p_2, point);

                // Check for the edges and internalpoints
                // Because the polygon must be simple every time
                for(const Segment_2& edge_ :polygon.edges()){

                    Point_2 first_point = edge_.point(0);
                    Point_2 second_point = edge_.point(1);

                    // For the same points in differents eges
                    if( first_point != p_1 && second_point != p_1){
                        if(CGAL::do_intersect(seg1, edge_) == true){
                            flag = true;
                            break;
                        }
                    }
            
                    // For the same points in differents eges
                    if( first_point != p_2 && second_point != p_2){
                        if(CGAL::do_intersect(seg2, edge_) == true){
                            flag = true;
                            break;
                        }
                    }
                }

                // If flag == true continue with next internal point
                if( flag == true){
                    continue;
                }

                // Find the distance
                double distance = CGAL::squared_distance(e, point);

                if( distance < min_distance){
                    flag_find_point = true;
                    min_distance = distance;
                    internal_point_to_choise = point;
                    num_internal_point_to_choise = i;
                }
            }   
            
            // If you save internal point for the edge -e
            if(flag_find_point == true){
                
                Point_2 p1 = e.point(0);
                Point_2 p2 = e.point(1);
            
                // I will find the area for p1, p2 and internal_point_to_choise
                double area = CGAL::area( p1, p2, internal_point_to_choise);

                //Max Area
                if( area > max_area){
                    max_area = area;
                    internal_point = internal_point_to_choise;
                    num_internal_point = num_internal_point_to_choise;
                    edge = e;
                }
            }

        }

        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);
        
        // Take the points from edge
        Point_2 p1 = edge.point(0);
        Point_2 p2 = edge.point(1);

        
        VertexIterator iter;
        for( 
            iter = polygon.vertices_begin();
            iter != polygon.vertices_end();
            ++iter
        ){
            if( iter->x() == p2.x() && iter->y() == p2.y()){
                break;
            }
        }
        
        // Change the polygon
        polygon.insert(iter, internal_point);
    }

    return polygon;
}

// Algorithmic for random-edge
Polygon_2 random_edge(vector<Point_2> internal_points, Polygon_2 polygon){
    
    srand(time(NULL));

    while( !internal_points.empty() ){
        
        bool flag_find_point = false;
        Segment_2 edge;
        Point_2 internal_point;
        int num_internal_point = 0;

        vector<Segment_2> edges;
        for(const Segment_2& edge  : polygon.edges()){
            edges.push_back(edge);
        }

        while( flag_find_point == false){

            int my_rand = rand();
            int num_edges = polygon.edges().size();;
            
            int num_edge = my_rand%num_edges;

            // Take the random edge
            edge = edges.at(num_edge);


            Point_2 p_1 = edge.point(0);
            Point_2 p_2 = edge.point(1);
            
            // min distance is MAX            
            double min_distance = numeric_limits<double>::max();
            Point_2 internal_point_to_choise;

            int num_internal_point_to_choise = 0;
        
            // I will find the internal point with minimum distance from edge
            // And I will save it
            for(int i=0; i < internal_points.size(); i++){
                Point_2 point = internal_points.at(i);

                bool flag = false;

                Segment_2 seg1(p_1, point);
                Segment_2 seg2(p_2, point);

                // Check for the edges and internalpoints
                // Because the polygon must be simple every time
                for(const Segment_2& edge_ :polygon.edges()){

                    Point_2 first_point = edge_.point(0);
                    Point_2 second_point = edge_.point(1);

                    // For the same points in differents eges
                    if( first_point != p_1 && second_point != p_1){
                        if(CGAL::do_intersect(seg1, edge_) == true){
                            flag = true;
                            break;
                        }
                    }

                    // For the same points in differents eges
                    if( first_point != p_2 && second_point != p_2){
                        if(CGAL::do_intersect(seg2, edge_) == true){
                            flag = true;
                            break;
                        }
                    }

                }

                // If flag == true continue with next internal point
                if( flag == true){
                    continue;
                }

                // Find the distance
                double distance = CGAL::squared_distance(edge, point);

                if( distance < min_distance){
                    flag_find_point = true;
                    min_distance = distance;
                    internal_point_to_choise = point;
                    num_internal_point_to_choise = i;
                }
            }   
        
            internal_point = internal_point_to_choise;
            num_internal_point = num_internal_point_to_choise;
        }
    
        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);
        
        // Take the point-2 from edge
        Point_2 p2 = edge.point(1);

        
        VertexIterator iter;
        for( 
            iter = polygon.vertices_begin();
            iter != polygon.vertices_end();
            ++iter
        ){
            if( iter->x() == p2.x() && iter->y() == p2.y()){
                break;
            }
        }

        // Change the polygon
        polygon.insert(iter, internal_point);

    }
    

    return polygon;
}



/// @brief
/// @param points 
/// @param edge_selection 
/// @return 
Polygon_2 convex_hull( vector<Point_2> points, int edge_selection){
    
    Points result;

    // Create the convex hull
    CGAL::convex_hull_2( points.cbegin(), points.cend(), std::back_inserter(result) );
    
    // Create the polygon
    Polygon_2 polygon;
    for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
        polygon.push_back(*iter);
    }

    // Vector with internals_points
    vector<Point_2> internal_points;
    
    // Find internal points
    for(int i = 0; i < points.size(); i++){
        Point_2 point = points.at(i);
        bool find = false;
        for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
            if( point == *iter){
                find = true;
                break;
            }
        }
        if( find == false){
            internal_points.push_back(point);
        }
    }

    

    if( edge_selection == 1){
        polygon = random_edge(internal_points, polygon);
    }
    else if( edge_selection == 2){
        polygon = min_area(internal_points, polygon);
    }
    else{
        polygon = max_area(internal_points, polygon);
    }

    // Take the vertices from polyhon
    for(const Point_2& point : polygon.vertices()){
        std::cout << point << std::endl;
    }
    
    // Take the edges from polygon
    for(const Segment_2& edge  : polygon.edges()){
        std::cout<< edge << std::endl;
    }

    long double area = polygon.area();

    Polygon_2 KP;
    CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(KP));

    cout<<"ratio: "<< area/KP.area() <<endl;

    return polygon;

}