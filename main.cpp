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
 
// enwsi olo ton pio eksoterikwn simeiwn dimiourgia enos "kuklou"
// tora exo enomena ola ta eksoterika simeia kai esoterika isos
// anoigo for (oso uparxoun esoterika simeia kane)
// ---- vroxos( gia kathe akmi )
// ---- ---- gia kathe simeio vres tin min-distance me akmi 

// int con(){
//     create_polygonumiki_grammi_me_ta_pio_eksoterika();
    
//     while(esoterikes_simeio>0){

//         esoteriko_simeio = Null;
//         //analoga to emvadon epilego kai enwnw simeio_1_akmis kai simeio_2 akmis me simeio epilogis
//         for(akmi from akmes){

//             min = MAX_INT;
//             akmi;
//             simeio_epilogis;

//             for( gia kathe esoteriko simeio){
//                 simeio;
//                 dist = distance( akmi, simeio);
//                 if( dist < min){
//                     min = dist;
//                     simeio_epilogis = simeio;
//                 }
//             }

//             emb = emvadon( simeio_1_akmis, simeio_2_akmis, simeio_epilogis);
//             //analoga to emvadon epilego kai enwnw simeio_1_akmis kai simeio_2 akmis me simeio epilogis
//         }
//     }
// }
typedef K::Segment_2 Segment_2;

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
