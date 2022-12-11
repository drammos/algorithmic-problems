#include "incremental.hpp"
#include "convex_hull_algorithmic.hpp"
#include "../first-project/to_polygon.hpp"
#include "local_search.hpp"
#include "simulated_annealing.hpp"
#include "subdivision.hpp"

Polygon_2D setup(vector<Point_2>);

int main(int argc, char* argv[]){
    if(argc != 12){
        cout<<"Not enough arguments\n";
        return -1;
    }
    string filename = argv[2];
    string output_file = argv[4];

    // Cout in file
    ofstream cout(output_file);
    std::cout.rdbuf(cout.rdbuf());
    
    // Read input file
    vector<Point_2> points;

    ifstream input_file;
    input_file.open(filename);

    int num;
    double x;
    double y;
    string line;

    // Read the first 2 lines with (#)
    getline(input_file, line);
    getline(input_file, line);
    
    
    // Add the point from input-file
    while(input_file >> num >> x >> y)
    {   
        Point_2 new_point(x,y);
        // Add the points in vector
        points.push_back( new_point);
    }

    // Close the file
    input_file.close();
    
    // Start the time
    int time_start = clock();

    string algorithm_2 = argv[6];
    int L = atoi(argv[8]);
    string min_max = argv[9];

     cout<<"Optimal Area Polygonization"<<endl;


    Polygon_2D new_pol;
    string annealing;

    cout<<"Algorithm: "<<algorithm_2<<"_"<<min_max<<endl;


    if(algorithm_2.compare("simulated_annealing") == 0){

        annealing = argv[11];

        if(annealing.compare("subdivision") == 0){
            if(points.size() <= 1000){
                string step;
                if(points.size()%2 == 0){
                    step = "local";
                }
                else{
                    step = "global";
                }
                Polygon_2D polygon = setup(points);
                new_pol = simulated_annealing(polygon, L, min_max, step, nullptr, nullptr);
            }
            new_pol = subdivision(points, L, min_max);

        }
        else{
            Polygon_2D polygon = setup(points);
            new_pol = simulated_annealing(polygon, L, min_max, annealing, nullptr, nullptr);
        }
    }
    else if( algorithm_2.compare("local_search") == 0){
        double threshold = atof(argv[11]);
        Polygon_2D polygon = setup(points);
        new_pol = local_search(polygon, L, min_max, threshold);
    }


    Points vertices = new_pol.vertices();
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices.at(i) << endl;
    }

    for(const Segment_2& e  : new_pol.edges()){
        cout << e << endl;
    }

    cout<<"area:"<<new_pol.area()<<endl;

    Polygon_2D KP1;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP1));

    cout<<"ratio:"<<new_pol.area()/KP1.area()<<endl;

    int time_end = clock();
    int time = time_end - time_start;
    cout << "construction time: " << time << endl;
    
    
    cout << "\n\nThe polygon is simple: " << new_pol.is_simple() << endl;
    
    return 0;
}

/// @brief 
/// @param points 
/// @return 
Polygon_2D setup(vector< Point_2> points){

    string algorithm = "convex_hull";
    // string algorithm = "incremental";

    string init = "1a";
    int edge_selection = 1;
    Polygon_2D polygon;

    if( algorithm.compare("convex_hull") == 0){
        Segment_2* edge1 = nullptr;
        Segment_2* edge2 = nullptr;
        polygon = convex_hull(points, edge_selection, edge1, edge2);
    }
    else{
        polygon = incremental(points, edge_selection, init);
    }

    Polygon_2D KP;
    CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(KP));
    double ratio_initial = polygon.area()/KP.area();

    cout<<"ratio_initial:"<<ratio_initial<<endl;
    cout<<"area_initial:"<<polygon.area()<<endl;
    
    return polygon;
}