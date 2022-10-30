#include <CGAL/convex_hull_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include "utils.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 9){
        cout<<"Not enough arguments\n";
        return -1;
    }
    string input_file = argv[2];
    string output_file = argv[4];
    string algorithm = argv[6];
    int edge_selection = atoi(argv[8]);
    string init;
    if(argc == 11){
        init = argv[10];
    }
    return 0;               
}