#include "incremental.hpp"
#include "convex_hull_algorithmic.hpp"
#include "../first-project/to_polygon.hpp"
#include "local_search.hpp"
#include "simulated_annealing.hpp"

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
    vector< Point_2> points;

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

    int edge_selection = 1;
    
    // Start the time
    int time_start = clock();
    Polygon_2D pol;

    cout<<"Optimal Area Polygonization"<<endl;

    string algorithm = "incremental";
    string init = "1a";

    if( algorithm.compare("convex_hull") == 0){
        pol = convex_hull(points, edge_selection);
    }
    else{
        pol = incremental(points, edge_selection, init);
    }

    Polygon_2D KP;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(KP));
    double ratio_initial = pol.area()/KP.area();

    int L = atoi(argv[8]);
    string min_max = argv[9];
    double threshold = atof(argv[11]);

    string algorithm_2 = argv[6];
    cout<<"Algorithm: "<<algorithm_2<<"_"<<min_max<<endl;

    cout<<"area_initial:"<<pol.area()<<endl;

    
    Polygon_2D new_pol;
    string annealing;
    if(!algorithm_2.compare("simulated_annealing")){
        annealing = argv[11];
        new_pol = simulated_annealing(pol, L, min_max, annealing);
    }
    else if(!algorithm_2.compare("local_search")){
        new_pol = local_search(pol, L, min_max, threshold);
    }
    
    cout<<"area:"<<new_pol.area()<<endl;

    cout<<"ratio_initial:"<<ratio_initial<<endl;

    Polygon_2D KP1;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP1));

    cout<<"ratio:"<<new_pol.area()/KP1.area()<<endl;

    int time_end = clock();
    int time = time_end - time_start;
    cout << "construction time: " << time << endl;
    return 0;
}
