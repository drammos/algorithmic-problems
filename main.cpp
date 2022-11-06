#include <CGAL/convex_hull_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "incremental.hpp"

using namespace std;

////////////////////////////////
//                            // 
//          main.cpp          // 
//                            //
////////////////////////////////




// ./main -i file -o outfile -algorithm convex_hull -edge_selection 1 (-initialization <1a or 1b or 2a or 2b>

int main(int argc, char* argv[]){
    if(argc < 9){
        cout<<"Not enough arguments\n";
        return -1;
    }

    string filename = argv[2];
    string output_file = argv[4];

    string algorithm = argv[6];
    if(algorithm.compare("incremental") && algorithm.compare("convex_hull")){
        cout<<"Ivalid algorithm"<<endl;
        return -1;
    }

    int edge_selection = atoi(argv[8]);
    if(edge_selection!=1 && edge_selection!=2 && edge_selection!=3){
        cout<<"Invalid edge selection number"<<endl;
        return -1;
    }

    string init;
    if(argc == 11){
        init = argv[10];
    }

    if(init.compare("1a") && init.compare("1b") && init.compare("2a") && init.compare("2b")){
        cout<<"Ivalid initialization string"<<endl;
        return -1;
    }

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
    
    // Start the time
    int time_start = clock();
    long double area;

    cout<<"Polygonization"<<endl;
    if( algorithm.compare("convex_hull") == 0){
        cout<<"convex hull"<<endl;
    }
    else{
        area = incremental(points, edge_selection, init);
    }
    cout<<"Algorithm: "<<algorithm<<" edge_selection: "<<edge_selection;
    if(!algorithm.compare("incremental")){
        cout<<" initialization: "<<init<<endl;
    }
    else{
        cout<<endl;
    }
    int time_end = clock();
    
    int time = time_end - time_start;
    cout << "area: " << area << endl;

    cout << "construction time: " << time << endl;

    cout << "The end" << endl;

    return 0;               
}