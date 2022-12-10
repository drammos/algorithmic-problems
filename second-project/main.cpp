#include "../first-project/incremental.hpp"
#include "../first-project/convex_hull_algorithmic.hpp"
#include "../first-project/to_polygon.hpp"
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
    // cout << argc << endl;
    
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

    cout<<"Polygonization"<<endl;

    string algorithm = "incremental";
    string init = "1a";

    if( algorithm.compare("convex_hull") == 0){
        pol = convex_hull(points, edge_selection);
    }
    else{
        pol = incremental(points, edge_selection, init);
    }

    cout << "area old: " << pol.area() << endl;


    cout<<"Polygonization"<<endl;
    cout<<"Algorithm: "<<algorithm<<" edge_selection: "<<edge_selection;

    if(!algorithm.compare("incremental")){
        cout << " initialization: " << init << endl;
    }
    else{
        cout << endl;
    }
    

    string algorithm_2 = argv[6];
    int L = atoi(argv[8]);
    string min_max = argv[9];
    

    Polygon_2D new_pol;
    string annealing;

    if(algorithm_2.compare("simulated_annealing") == 0){
        annealing = argv[11];
        new_pol = simulated_annealing(pol, L, min_max, annealing);
    }
    else if( algorithm_2.compare("local_search") ){
        double threshold = atof(argv[11]);
        cout << "Local search algorithmic" << endl;
    }
    int time_end = clock();
    
    int time = time_end - time_start;
    cout << "area: " << new_pol.area() << endl;

    cout << "construction time: " << time << endl;
    
    return 0;
}




// $./optimal_polygon 
//2     –i <point set input file> 
//4     –ο <output file> 
//6     –algorithm <local_search or simulated_annealing or ant_colony> 
//8     -L [L parameter according to algorithm] 
    //10     –max [maximal area polygonization] 
    //12     –min [minimal area polygonization] 
//14     –threshold <double> [in local search] 
//16     –annealing <"local" or "global" or "subdivision" in simulated annealing> 

// ./main -i input.txt -o outfile -algorithm simulated_annealing -L 5 -max 6 -min 1 -threshold 2.2