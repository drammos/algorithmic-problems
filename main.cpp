#include <iostream>

using namespace std;


// Ένα αρχείο κειμένου για την είσοδο του S διαχωρισμένο με στηλοθέτες (tab-separated), με την ακόλουθη
// γραμμογράφηση:


// # <γραμμή περιγραφής σημειοσυνόλου>
// # parameters "convex_hull": {"area": "Χ"} // όπου Χ η επιφάνεια του ΚΠ2


// 0 x0 y0
// 1 x1 y1
// … … …
// n-1 xn yn
// όπου n είναι το πλήθος των σημείων του σημειοσυνόλου και xi, yi οι συντεταγμένες (θετικοί ακέραιοι).
// Το αρχείο εισόδου, το αρχείο εξόδου και οι παράμετροι του αλγόριθμου δίνονται ως παράμετροι γραμμής
// εντολών. Η εκτέλεση γίνεται μέσω της εντολής:



// $./to_polygon 
//–i <point set input file> 
//–ο <output file> 
//–algorithm <incremental or convex_hull or onion> 
//-edge_selection <1 or 2 or 3 | όχι στο onion> 
//-initialization <1a or 1b or 2a or 2b | μόνο στον αυξητικό αλγόριθμο> 


// ./main -i file -o outfile -algorithm convex_hull -edge_selection 1

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <fstream>
#include <time.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::istream_iterator< Point_2 > point2_iterator;
typedef std::vector<Point_2> Points;
typedef std::vector<Point_2>::iterator pveciterator;

typedef CGAL::Polygon_2<K> Polygon_2;



using namespace std;

struct Point1{
    int num;
    double x;
    double y;
};
 
typedef K::Segment_2 Segment_2;
typedef Polygon_2::Vertex_iterator VertexIterator;


Polygon_2 min_area(vector<Point_2> internal_points, Polygon_2 polygon){
    
    srand(time(NULL));

    while( !internal_points.empty() ){
        
        
        // min area is MAX 
        double min_area = numeric_limits<double>::max();
        Point_2 internal_point;
        Segment_2 edge;
        int num_internal_point;
        for(const Segment_2& e  : polygon.edges()){

            // min distance is MAX            
            double min_distance = numeric_limits<double>::max();
            Point_2 internal_point_to_choise;

            // I will find the internal point with minimum distance from edge
            // And I will save it
            for(int i=0; i < internal_points.size(); i++){
                Point_2 point = internal_points.at(i);
                double distance = CGAL::squared_distance(e, point);

                if( distance < min_distance){
                    min_distance = distance;
                    internal_point_to_choise = point;
                    num_internal_point = i;
                }
            }   

            // double area = CGAL::area()
            Point_2 p1 = e.point(0);
            Point_2 p2 = e.point(1);
            
            // I will find the area for p1, p2 and internal_point_to_choise
            double area = CGAL::area( p1, p2, internal_point_to_choise);

            if( area < min_area){
                min_area = area;
                internal_point = internal_point_to_choise;
                edge = e;
            }
        }

        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);
        
        // Take the points from edge
        Point_2 p1 = edge.point(0);
        Point_2 p2 = edge.point(1);

        // Create 2 new edges
        Segment_2 edge_1( p1, internal_point);
        Segment_2 edge_2( p2, internal_point);

        // na diagraspo tin palia akmi apo polygono
        // na prostheso tis dyo nees
        
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


        polygon.insert(iter, internal_point);

    }

    return polygon;
}

Polygon_2 max_area(vector<Point_2> internal_points, Polygon_2 polygon){
    
    srand(time(NULL));

    while( !internal_points.empty() ){
        
        
        // max area is MAX 
        double max_area = numeric_limits<double>::min();
        Point_2 internal_point;
        Segment_2 edge;
        int num_internal_point;
        for(const Segment_2& e  : polygon.edges()){

            // min distance is MAX            
            double min_distance = numeric_limits<double>::max();
            Point_2 internal_point_to_choise;

            // I will find the internal point with minimum distance from edge
            // And I will save it
            for(int i=0; i < internal_points.size(); i++){
                Point_2 point = internal_points.at(i);
                double distance = CGAL::squared_distance(e, point);

                if( distance < min_distance){
                    min_distance = distance;
                    internal_point_to_choise = point;
                    num_internal_point = i;
                }
            }   

            // double area = CGAL::area()
            Point_2 p1 = e.point(0);
            Point_2 p2 = e.point(1);
            
            // I will find the area for p1, p2 and internal_point_to_choise
            double area = CGAL::area( p1, p2, internal_point_to_choise);

            if( area > max_area){
                max_area = area;
                internal_point = internal_point_to_choise;
                edge = e;
            }
        }

        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);
        
        // Take the points from edge
        Point_2 p1 = edge.point(0);
        Point_2 p2 = edge.point(1);

        // Create 2 new edges
        Segment_2 edge_1( p1, internal_point);
        Segment_2 edge_2( p2, internal_point);

        // na diagraspo tin palia akmi apo polygono
        // na prostheso tis dyo nees
        
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


        polygon.insert(iter, internal_point);

    }

    return polygon;
}

Polygon_2 random_edge(vector<Point_2> internal_points, Polygon_2 polygon){
    
    srand(time(NULL));

    while( !internal_points.empty() ){
        
        
        // max area is MAX 
        double max_area = numeric_limits<double>::min();
        Point_2 internal_point;
        Segment_2 edge;
        int num_internal_point;


        int my_rand = rand();
        int num_edges = polygon.edges().size();;
        
        int num = my_rand%num_edges;

        int i = 0;
        Segment_2 e;
        // Change random edge
        for(const Segment_2& edge  : polygon.edges()){
            if( i == num){
                e = edge;
                break;
            }
            i++;
        }


        // min distance is MAX            
        double min_distance = numeric_limits<double>::max();
        Point_2 internal_point_to_choise;

        // I will find the internal point with minimum distance from edge
        // And I will save it
        for(int i=0; i < internal_points.size(); i++){
            Point_2 point = internal_points.at(i);
            double distance = CGAL::squared_distance(e, point);

            if( distance < min_distance){
                min_distance = distance;
                internal_point_to_choise = point;
                num_internal_point = i;
            }
        }   
    
        internal_point = internal_point_to_choise;
        edge = e;

        // Delete the interal point from vector
        internal_points.erase( internal_points.begin() + num_internal_point);
        
        // Take the points from edge
        Point_2 p1 = edge.point(0);
        Point_2 p2 = edge.point(1);

        // Create 2 new edges
        Segment_2 edge_1( p1, internal_point);
        Segment_2 edge_2( p2, internal_point);

        // na diagraspo tin palia akmi apo polygono
        // na prostheso tis dyo nees
        
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


        polygon.insert(iter, internal_point);

    }

    return polygon;
}


/// @brief
/// @param points 
/// @param edge_selection 
/// @return 
int convex_hull( vector<Point_2> points, int edge_selection){
    
    Points result;

    // Create the convex hull
    CGAL::convex_hull_2( points.cbegin(), points.cend(), std::back_inserter(result) );
    
    // Create the polygon
    Polygon_2 polygon;
    for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
        polygon.push_back(*iter);
    }

    std::cout << "\n\nBefore from algorithm:\n\n";
    
    // Take the vertices from polyhon
    for(const Point_2& p : polygon.vertices()){
        std::cout << "Vertices  " << p << std::endl;
    }
    
    // Take the edges from polygon
    for(const Segment_2& e  : polygon.edges()){
        std::cout << "Edge  " << e << std::endl;
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

    // Print the insternal points
    for(int i = 0; i < internal_points.size(); i++){
        cout << "Inernal    " << internal_points.at(i) << endl;
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
    std::cout << "\n\nAfter from algorithm:\n\n";

    // Take the vertices from polyhon
    for(const Point_2& p : polygon.vertices()){
        std::cout << "Vertices  " << p << std::endl;
    }
    
    // Take the edges from polygon
    for(const Segment_2& e  : polygon.edges()){
        std::cout << "Edge  " << e << std::endl;
    }
    
    return EXIT_SUCCESS;

}

int main(int argc, char* argv[]){
    if(argc < 9){
        cout<<"Not enough arguments\n";
        return -1;
    }

    string filename = argv[2];
    string output_file = argv[4];
    string algorithm = argv[6];
    int edge_selection = atoi(argv[8]);
    string init;
    if(argc == 11){
        init = argv[10];
    }


    // Read input file
    vector< Point_2> points;

    ifstream input_file;
    input_file.open(filename);

    int num;
    double x;
    double y;
    while(input_file >> num >> x >> y)
    {   
        Point_2 new_point(x,y);

        // Add the points in vector
        points.push_back( new_point);
    }
    input_file.close();
    
    
    if( algorithm.compare("convex_hull") == 0){
        convex_hull(points, edge_selection);
    }
    else{
        cout << "Other" << endl;
    }
    cout << "The end" << endl;


    return 0;               
}
