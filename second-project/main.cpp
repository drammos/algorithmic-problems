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
    // ofstream cout(output_file);
    // std::cout.rdbuf(cout.rdbuf());
    
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
    

    string algorithm_2 = argv[6];
    int L = atoi(argv[8]);
    string min_max = argv[9];
    double threshold = atof(argv[11]);

    Polygon_2D new_pol;
    string annealing;

    if(algorithm_2.compare("simulated_annealing") == 0){
        if(argc < 14){
            cout<<" Not enough arguments\n" << argc << endl;
            return -1;
        }
        annealing = argv[13];
        if(annealing.compare("subdivision") == 0){
            // if(points.size() <= 1000){
            //     string step;
            //     if(points.size()%2 == 0){
            //         step = "local";
            //     }
            //     else{
            //         step = "global";
            //     }
            //     Polygon_2D polygon = setup(points);
            //     new_pol = simulated_annealing(polygon, L, min_max, threshold, step);
            // }
            new_pol = subdivision(points, L, min_max);

        }
        else{
            Polygon_2D polygon = setup(points);
            new_pol = simulated_annealing(polygon, L, min_max, threshold, annealing);
        }
    }
    else if( algorithm_2.compare("local_search") ){
        Polygon_2D polygon = setup(points);
        cout << "Local search algorithmic" << endl;
    }
    
    return 0;
}

Polygon_2D setup(vector< Point_2> points){
    // Start the time
    int time_start = clock();

    cout<<"Optimal Area Polygonization"<<endl;

    string algorithm = "incremental";
    string init = "1a";
    int edge_selection = 1;
    Polygon_2D polygon;

    if( algorithm.compare("convex_hull") == 0){
        polygon = convex_hull(points, edge_selection);
    }
    else{
        polygon = incremental(points, edge_selection, init);
    }

    Polygon_2D KP;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(KP));
    double ratio_initial = pol.area()/KP.area();

    if(!algorithm.compare("incremental")){
        cout << " initialization: " << init << endl;
    }
    else{
        cout << endl;
    }
    int time_end = clock();
    
    int time = time_end - time_start;
    cout << "area: " << polygon.area() << endl;

    cout << "construction time: " << time << endl;
    return polygon;
}

    // cout<<"ratio_initial:"<<ratio_initial<<endl;

// ./main -i input.txt -o outfile -algorithm simulated_annealing -L 5 -max -threshold 2.2 -annealing subdivision
