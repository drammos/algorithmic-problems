#include "PolygonsAlgorithm/incremental.hpp"
#include "PolygonsAlgorithm/convex_hull_algorithmic.hpp"
#include "LocalSearch/local_search.hpp"
#include "SimulatedAnnealing/simulated_annealing.hpp"
#include "SimulatedAnnealing/subdivision.hpp"
#include <dirent.h>
#include <iomanip>

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

void local_search_results(Polygon_2D pol, double& sum_min, double& sum_max, double& bound_min, double& bound_max){
    Polygon_2D new_pol = local_search(pol,3,"-min",0.3);
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

    new_pol = local_search(pol,3,"-max",0.3);
    if(new_pol.orientation() == -1){
        new_pol.reverse_orientation();
    }

    Polygon_2D KP2;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP2));
    double ratio2 = new_pol.area()/KP2.area();

    sum_max+=ratio2;
    if(ratio1 < bound_max){
        bound_max= ratio2;
    }

}

void annealing_local_step(Polygon_2D pol, double& sum_min, double& sum_max, double& bound_min, double& bound_max){
    Polygon_2D new_pol = simulated_annealing(pol, 1000, "-min", "local", nullptr, nullptr);
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

    new_pol = simulated_annealing(pol, 1000, "-max", "local", nullptr, nullptr);
    if(new_pol.orientation() == -1){
        new_pol.reverse_orientation();
    }
    Polygon_2D KP2;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP2));
    double ratio2 = new_pol.area()/KP2.area();

    sum_max+=ratio2;
    if(ratio2 < bound_max){
        bound_max = ratio2;
    }

}

void annealing_global_step(Polygon_2D pol, double& sum_min, double& sum_max, double& bound_min, double& bound_max){
    Polygon_2D new_pol = simulated_annealing(pol, 1000, "-min", "global", nullptr, nullptr);
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

    new_pol = simulated_annealing(pol, 1000, "-max", "global", nullptr, nullptr);
    if(new_pol.orientation() == -1){
        new_pol.reverse_orientation();
    }
    Polygon_2D KP2;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP2));
    double ratio2 = new_pol.area()/KP2.area();

    sum_max+=ratio2;
    if(ratio2 < bound_max){
        bound_max = ratio2;
    }

}

void convex_hull_subdivision(Polygon_2D pol, double& sum_min, double& sum_max, double& bound_min, double& bound_max){
    Polygon_2D new_pol = simulated_annealing(pol, 1000, "-min", "subdivision", nullptr, nullptr);
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

    new_pol = simulated_annealing(pol, 1000, "-max", "subdivision", nullptr, nullptr);
    if(new_pol.orientation() == -1){
        new_pol.reverse_orientation();
    }
    Polygon_2D KP2;
    CGAL::convex_hull_2(new_pol.begin(), new_pol.end(), std::back_inserter(KP2));
    double ratio2 = new_pol.area()/KP2.area();

    sum_max+=ratio2;
    if(ratio2 < bound_max){
        bound_max = ratio2;
    }
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

    cout<<"     ||          Incremental-Local Search             ||             Convex Hull-Local Search          ||   Incremental-Simulated Annealing-Local Step  ||   Convex Hull-Simulated Annealing-Local Step  ||  Incremental-Simulated Annealing-Global Step  ||  Convex Hull-Simulated Annealing-Global Step  ||  Convex Hull-Simulated Annealing-Subdivision  ||"<<endl;
    cout<<"Size || min score | max score | min bound | max bound || min score | max score | min bound | max bound || min score | max score | min bound | max bound || min score | max score | min bound | max bound || min score | max score | min bound | max bound || min score | max score | min bound | max bound || min score | max score | min bound | max bound ||"<<endl;

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
    double sum_min_inc_loc = 0;
    double sum_max_inc_loc = 0;
    double bound_max_inc_loc = 2.0;
    double bound_min_inc_loc = -2.0;

    double sum_min_conv_loc = 0;
    double sum_max_conv_loc = 0;
    double bound_max_conv_loc = 2.0;
    double bound_min_conv_loc = -2.0;

    double sum_min_inc_sim_loc = 0;
    double sum_max_inc_sim_loc = 0;
    double bound_max_inc_sim_loc = 2.0;
    double bound_min_inc_sim_loc = -2.0;

    double sum_min_conv_sim_loc = 0;
    double sum_max_conv_sim_loc = 0;
    double bound_max_conv_sim_loc = 2.0;
    double bound_min_conv_sim_loc = -2.0;

    double sum_min_inc_sim_glob = 0;
    double sum_max_inc_sim_glob = 0;
    double bound_max_inc_sim_glob = 2.0;
    double bound_min_inc_sim_glob = -2.0;

    double sum_min_conv_sim_glob = 0;
    double sum_max_conv_sim_glob = 0;
    double bound_max_conv_sim_glob = 2.0;
    double bound_min_conv_sim_glob = -2.0;

    double sum_min_conv_sub = 0;
    double sum_max_conv_sub = 0;
    double bound_max_conv_sub = 2.0;
    double bound_min_conv_sub = -2.0;

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
        
        cout<<fixed<<setprecision(5);
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<lines<<" || "<<sum_min_inc_loc<<"   |  "<<sum_max_inc_loc<<"  |  "<<bound_min_inc_loc<<"  |  "<<bound_max_inc_loc<<"  ||";
            sum_min_inc_loc = 0;
            sum_max_inc_loc = 0;
            bound_max_inc_loc = 2.0;
            bound_min_inc_loc = -2.0;
            // lines = points.size();
        }

        int cut_off = 500*points.size()/1000; //500

        // Close the file
        input_file.close();

        ////////////////////////
        ///

        //incremental-local_search
        time_start = clock();
        Polygon_2D pol = incremental(points, 1, "1a");
        local_search_results(pol, sum_min_inc_loc, sum_max_inc_loc, bound_min_inc_loc, bound_max_inc_loc);

        // time_end = clock();
        // time = time_end - time_start;

        // cut_off -= time;
        // int next_cut_off = cut_off;
        // if(cut_off < 0){
        //     return -1;
        // }
    

        ///
        ////////////////////////
        //convex hull- local search
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<sum_min_conv_loc<<"  |  "<<sum_max_conv_loc<<"  |  "<<bound_min_conv_loc<<"  |  "<<bound_max_conv_loc<<"  ||";
            sum_min_conv_loc = 0;
            sum_max_conv_loc = 0;
            bound_max_conv_loc = 2.0;
            bound_min_conv_loc = -2.0;
            // lines = points.size();
        }

        Polygon_2D pol1 = convex_hull(points, 1, nullptr, nullptr);
        local_search_results(pol1, sum_min_conv_loc, sum_max_conv_loc, bound_min_conv_loc, bound_max_conv_loc);

        

        //incremental - simmulated annealing - local step
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<sum_min_inc_sim_loc<<"  |  "<<sum_max_inc_sim_loc<<"  |  "<<bound_min_inc_sim_loc<<"  |  "<<bound_max_inc_sim_loc<<"  ||";
            sum_min_inc_sim_loc = 0;
            sum_max_inc_sim_loc = 0;
            bound_max_inc_sim_loc = 2.0;
            bound_min_inc_sim_loc = -2.0;
            // lines = points.size();
        }
        
        annealing_local_step(pol, sum_min_inc_sim_loc, sum_max_inc_sim_loc, bound_min_inc_sim_loc, bound_max_inc_sim_loc);

        //convex hull - simmulated annealing - local step
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<sum_min_conv_sim_loc<<"  |  "<<sum_max_conv_sim_loc<<"  |  "<<bound_min_conv_sim_loc<<"  |  "<<bound_max_conv_sim_loc<<"  ||";
            sum_min_conv_sim_loc = 0;
            sum_max_conv_sim_loc = 0;
            bound_max_conv_sim_loc = 2.0;
            bound_min_conv_sim_loc = -2.0;
            // lines = points.size();
        }

        annealing_local_step(pol1, sum_min_conv_sim_loc, sum_max_conv_sim_loc, bound_min_conv_sim_loc, bound_max_conv_sim_loc);

        //incremental - simulated annealing - global step
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<sum_min_inc_sim_glob<<"  |  "<<sum_max_inc_sim_glob<<"  |  "<<bound_min_inc_sim_glob<<"  |  "<<bound_max_inc_sim_glob<<"  ||";
            sum_min_inc_sim_glob = 0;
            sum_max_inc_sim_glob = 0;
            bound_max_inc_sim_glob = 2.0;
            bound_min_inc_sim_glob = -2.0;
            // lines = points.size();
        }

        annealing_global_step(pol, sum_min_inc_sim_glob, sum_max_inc_sim_glob, bound_min_inc_sim_glob, bound_max_inc_sim_glob);

        //convex hull - simulated annealing - global step
        if(points.size() > lines){
            //PRINTING
            cout<<setprecision(5)<<"  "<<sum_min_conv_sim_glob<<"  |  "<<sum_max_conv_sim_glob<<"  |  "<<bound_min_conv_sim_glob<<"  |  "<<bound_max_conv_sim_glob<<"  ||";
            sum_min_conv_sim_glob = 0;
            sum_max_conv_sim_glob = 0;
            bound_max_conv_sim_glob = 2.0;
            bound_min_conv_sim_glob = -2.0;
            // lines = points.size();
        }

        annealing_global_step(pol1, sum_min_conv_sim_glob, sum_max_conv_sim_glob, bound_min_conv_sim_glob, bound_max_conv_sim_glob);

        //convex hull - subdivision
        if(points.size() > lines){
            if(lines>1000){
                cout<<setprecision(5)<<"  "<<sum_min_conv_sub<<"  |  "<<sum_max_conv_sub<<"  |  "<<bound_min_conv_sub<<"  |  "<<bound_max_conv_sub<<"  ||";
                sum_min_conv_sim_glob = 0;
                sum_max_conv_sim_glob = 0;
                bound_max_conv_sim_glob = 2.0;
                bound_min_conv_sim_glob = -2.0;
                lines = points.size();
            }
            else{
                cout<<endl;
                lines = points.size();

            }
        }
        if(lines > 1000)
            convex_hull_subdivision(pol1, sum_min_conv_sub, sum_max_conv_sub, bound_min_conv_sub, bound_max_conv_sub);
    }
    
    //last print
    cout<<setprecision(5)<<"  "<<lines<<" || "<<sum_min_inc_loc<<"   |  "<<sum_max_inc_loc<<"  |  "<<bound_min_inc_loc<<"  |  "<<bound_max_inc_loc<<"  ||";
    cout<<setprecision(5)<<"  "<<sum_min_conv_loc<<"  |  "<<sum_max_conv_loc<<"  |  "<<bound_min_conv_loc<<"  |  "<<bound_max_conv_loc<<"  ||";
    cout<<setprecision(5)<<"  "<<sum_min_inc_sim_loc<<"  |  "<<sum_max_inc_sim_loc<<"  |  "<<bound_min_inc_sim_loc<<"  |  "<<bound_max_inc_sim_loc<<"  ||";
    cout<<setprecision(5)<<"  "<<sum_min_conv_sim_loc<<"  |  "<<sum_max_conv_sim_loc<<"  |  "<<bound_min_conv_sim_loc<<"  |  "<<bound_max_conv_sim_loc<<"  ||";
    cout<<setprecision(5)<<"  "<<sum_min_inc_sim_glob<<"  |  "<<sum_max_inc_sim_glob<<"  |  "<<bound_min_inc_sim_glob<<"  |  "<<bound_max_inc_sim_glob<<"  ||";
    cout<<setprecision(5)<<"  "<<sum_min_conv_sim_glob<<"  |  "<<sum_max_conv_sim_glob<<"  |  "<<bound_min_conv_sim_glob<<"  |  "<<bound_max_conv_sim_glob<<"  ||";
    if(lines > 1000){
        cout<<setprecision(5)<<"  "<<sum_min_conv_sub<<"  |  "<<sum_max_conv_sub<<"  |  "<<bound_min_conv_sub<<"  |  "<<bound_max_conv_sub<<"  ||";

    }
            
    return 0;
}