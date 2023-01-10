#include "local_search.hpp"

using namespace std;

list<vector<Point_2>> find_paths(vector<Point_2> vertices, int L){
    list<vector<Point_2>> paths;
    int first_vertex = 0;

    //each time we start with a different edge and find all the paths with max length of L
    while(first_vertex < vertices.size()){

        for(int i = first_vertex; i < L+first_vertex; i++){
            vector<Point_2> path;
            int j = first_vertex;
            int k = j;
            while(j <= i){
                if(j >= vertices.size()){
                    k = 0;
                }
                path.push_back(vertices.at(k));

                j++;
                k++;
            }
            paths.push_back(path);
            
        }
        first_vertex++;
    }

    return paths;
}

//removes the pathy from the existing polygon
Polygon_2D remove_path(vector<Point_2> path, Polygon_2D pol){
    for(int i = 0; i< path.size(); i++){
        VertexIterator vit = pol.vertices_begin();
        while(vit != pol.vertices_end()){

            if(vit->x() == path.at(i).x() && vit->y() == path.at(i).y()){
                pol.erase(vit);
                break;
            }
            vit++;

        }
    }
    return pol;
}

//adds the path to a different edge
Polygon_2D change_path(vector<Point_2> path, Segment_2 edge, Polygon_2D pol){

    for(VertexIterator vit = pol.vertices_begin(); vit != pol.vertices_end(); vit++){

        if(vit->x() == edge.point(1).x() && vit->y() == edge.point(1).y()){
            pol.insert(vit, path.at(0));

            for(int i = 1; i < path.size(); i++){

                VertexIterator vit = pol.vertices_begin();
                while(vit != pol.vertices_end()){

                    if(vit->x() == path.at(i-1).x() && vit->y() == path.at(i-1).y()){

                        pol.insert(vit, path.at(i));
                        break;
                    }

                    vit++;
                }
            }
            break;
        }
    }

    return pol;
}


Polygon_2D local_search(Polygon_2D pol, int L, string min_max, double threshold, int cut_off){
    // int time_start = clock();

    if(L >= pol.edges().size()){
        perror("L is too high");
    }

    double dif = threshold;
    Polygon_2D best = pol;
    Polygon_2D prev;
    while(dif >= threshold){
        prev = best;
        vector<Point_2> vertices;

        int time_start1 = clock();
        for(const Point_2& v  : best.vertices())
            vertices.push_back(v);

        //finding all the possible paths of the polygon
        list<vector<Point_2>> paths = find_paths(vertices, L);
        vector<Polygon_2D> alternatives;
        int time_end1 = clock();
        int time1 = time_end1 - time_start1;
        cut_off -= time1;

        if(cut_off<0){
            exit(EXIT_FAILURE);
        }

        int time_start2 = clock();

        for(vector<Point_2> path: paths){
            
            Polygon_2D new_pol = remove_path(path, best);
            for(Segment_2 edge: new_pol.edges()){
                //moves the path to different edge
                Polygon_2D final_pol = change_path(path, edge, new_pol);

                if(final_pol.is_simple()){
                    double area1 = best.area();
                    double area2 = final_pol.area();

                    if(!min_max.compare("-min")){
                        if(area1 > area2){
                            alternatives.push_back(final_pol);
                        }
                    }
                    else{
                        if(area1 < area2){
                            alternatives.push_back(final_pol);
                        }
                    }
                }
            }
        }
        
        int time_end2 = clock();
        int time2 = time_end2 - time_start2;
        cut_off -= time2;


        int time_start3 = clock();
        if(alternatives.size() > 0){
            //finding polygon of min or max area
            if(!min_max.compare("-min")){
                double min = alternatives.at(0).area();
                Polygon_2D min_pol = alternatives.at(0);

                for(int i = 1; i< alternatives.size(); i++){
                    if(alternatives.at(i).area() < min){
                        min = alternatives.at(i).area();
                        min_pol = alternatives.at(i);
                    }
                }

                if(min_pol.area() < best.area())
                    best = min_pol;
            }
            else{
                double max = alternatives.at(0).area();
                Polygon_2D max_pol = alternatives.at(0);

                for(int i = 1; i< alternatives.size(); i++){
                    if(alternatives.at(i).area() > max){
                        max = alternatives.at(i).area();
                        max_pol = alternatives.at(i);
                    }
                }

                if(max_pol.area() > best.area())
                    best = max_pol;
            }
        }
        
        int time_end3 = clock();
        int time3 = time_end3 - time_start3;
        cut_off -= time3;
        
        dif = abs(best.area() - prev.area());
    }
    best = prev;
    
    // int time_end = clock();
    // int time = time_end - time_start;
    // cut_off -= time;
    
    if(cut_off < 0){
        exit(EXIT_FAILURE);
    }

    return best;
}