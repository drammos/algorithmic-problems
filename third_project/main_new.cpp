#include "PolygonsAlgorithm/incremental.hpp"
#include "PolygonsAlgorithm/convex_hull_algorithmic.hpp"
#include "LocalSearch/local_search.hpp"
#include "SimulatedAnnealing/simulated_annealing.hpp"
#include "SimulatedAnnealing/subdivision.hpp"
#include <dirent.h>

bool compare(string file1, string file2){
    ifstream file;
    file.open(file1);

    string line;
    int count1 = 0;
    while (getline(file, line))
        count1++;
    file.open(file2);
    int count2 = 0;

    while (getline(file, line))
        count2++;
    return count1<count2;
}

int main(int argc, char* argv[]){
    if(argc < 5){
        cout<<"Not enough arguments\n";
        return -1;
    }
    char* path = argv[2];
    string output = argv[4];

    // Cout in file
    ofstream cout(output);
    std::cout.rdbuf(cout.rdbuf());

    cout<<" ||  Incremental-Local Search    ||  Convex Hull-Local Search    ||  Incremental-Simulated Annealing-Local Step  ||  Convex Hull-Simulated Annealing-Local Step  ||  Incremental-Simulated Annealing-Global Step  ||  Convex Hull-Simulated Annealing-Global Step    ||  Convex Hull-Simulated Annealing-Subdivision"<<endl;


    DIR *dir;
    struct dirent *ent;
    vector<string> files;
    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
                files.push_back(ent->d_name);
            }
        }
        closedir (dir);

    }
    else {
        perror ("");
        return EXIT_FAILURE;
    }
    sort(files.begin(), files.end(), compare);

    int lines = 10;
    int sum_min = 0;
    int sum_max = 0;
    double bound_max = 2.0;
    double bound_min = -2.0;

    cout<<files.size()<<endl;


    int time_start = 0;
    int time_end = 0;
    int time = 0;

    for(int i = 0; i < files.size(); i++){
        // Read input file
        string s = "/";
        string path1 = path+s+files.at(i);

        vector<Point_2> points;

        ifstream input_file;
        input_file.open(path1);

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

        if(points.size() > lines){
            //PRINTING

            sum_min = 0;
            sum_max = 0;
            bound_max = 2.0;
            bound_min = -2.0;
            lines = points.size();
        }

        int cut_off = 500*points.size()/1000; //500

        // Close the file
        input_file.close();

        ////////////////////////
        ///

        //incremental-local_search-min
        time_start = clock();
        Polygon_2D pol = incremental(points, 3, "1a");
        time_end = clock();
        time = time_end - time_start;

        cut_off -= time;
        int next_cut_off = cut_off;
        if(cut_off < 0){
            return -1;
        }
    
        Polygon_2D new_pol = local_search(pol,3,"-min",0.3, cut_off);



        if(new_pol.orientation() == -1){
            new_pol.reverse_orientation();
        }
        Polygon_2D KP1;
        CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP1));

        double ratio1 = new_pol.area()/KP1.area();
        sum_min+=ratio1;
        if(ratio1 > bound_min){
            bound_min = ratio1;
        }

        ///
        ////////////////////////

        ////////////////////////
        ///        
        //incremental-local_search-max

        new_pol = local_search(pol,3,"-max",0.3, next_cut_off);
        if(new_pol.orientation() == -1){
            new_pol.reverse_orientation();
        }

        Polygon_2D KP2;
        CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP2));
        double ratio2 = new_pol.area()/KP2.area();

        sum_max+=ratio2;
        if(ratio1 < bound_max){
            bound_max = ratio2;
        }

        ///
        ////////////////////////
 
    }
    

            
    return 0;
}