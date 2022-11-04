////////////////////////////////
//                            // 
//          main.cpp          // 
//                            //
////////////////////////////////


#include <time.h>
#include "convex_hull_algorithmic.h"

// ./main -i file -o outfile -algorithm convex_hull -edge_selection 1

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
    // Add the point from input-file
    while(input_file >> num >> x >> y)
    {   
        Point_2 new_point(x,y);

        // Add the points in vector
        points.push_back( new_point);
    }
    input_file.close();
    
    // Start the time
    int time_start = clock();
    double area;
    if( algorithm.compare("convex_hull") == 0){
        area = convex_hull(points, edge_selection);
    }
    else{
        cout << "Other" << endl;
    }

    int time_end = clock();
    int time = time_end - time_start;
    cout << "area: " << area << endl;

    cout << "construction time: " << time << endl;

    cout << "The end" << endl;

    return 0;               
}
