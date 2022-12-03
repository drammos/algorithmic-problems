#include "local_search.hpp"

using namespace std;

list<vector<Segment_2>> find_paths(vector<Segment_2> edges, int L){
    list<vector<Segment_2>> paths;
    int first_edge = 0;
    while(first_edge < edges.size()){
        for(int i = first_edge; i < L+first_edge; i++){
            vector<Segment_2> path;
            int j = first_edge;
            int k = j;
            while(j <= i){
                if(j >= edges.size()){
                    k = 0;
                }
                path.push_back(edges.at(k));

                j++;
                k++;
            }
            paths.push_back(path);
            
        }
        first_edge++;
    }

    return paths;
}

Polygon_2D change_path(vector<Segment_2> path, Segment_2 edge, Polygon_2D pol){
    for(VertexIterator vit = pol.vertices_begin(); vit != pol.vertices_end(); vit++){
        if(vit->x() == path.at(0).point(0).x() && vit->y() == path.at(0).point(0).y()){
            pol.erase(vit);
            for(int i = 1; i< path.size(); i++){
                VertexIterator vit = pol.vertices_begin();
                while(vit != pol.vertices_end()){
                    if(vit->x() == path.at(i).point(0).x() && vit->y() == path.at(i).point(0).y()){
                        pol.erase(vit);
                        break;
                    }
                    vit++;
                    if(vit == pol.vertices_end()){
                        vit = pol.vertices_begin();
                    }
                }
            }
            break;
        }
    }
    for(VertexIterator vit = pol.vertices_begin(); vit != pol.vertices_end(); vit++){
        if(vit->x() == edge.point(0).x() && vit->y() == edge.point(0).y()){
            pol.insert(vit, path.at(0).point(0));
            pol.insert(vit, path.at(0).point(1));
            for(int i = 1; i< path.size(); i++){
                VertexIterator vit = pol.vertices_begin();
                while(vit != pol.vertices_end()){
                    if(vit->x() == path.at(i-1).point(1).x() && vit->y() == path.at(i-1).point(1).y()){
                        // pol.insert(vit, path.at(i).point(0));
                        pol.insert(vit, path.at(0).point(1));
                        break;
                    }
                    vit++;
                    if(vit == pol.vertices_end()){
                        vit = pol.vertices_begin();
                    }
                }
            }
            break;
        }
    }

    return pol;
}

Polygon_2D local_search(Polygon_2D pol, int L, string min_max, double threshold){

    if(L >= pol.edges().size()){
        perror("L is too high");
    }

    double dif = threshold;
    Polygon_2D best = pol;

    while(dif >= threshold){

        vector<Segment_2> edges;
        for(const Segment_2& e  : best.edges())
            edges.push_back(e);

        list<vector<Segment_2>> paths = find_paths(edges, L);

        for(vector<Segment_2> path: paths){
            vector<Polygon_2D> alternatives;

            for(Segment_2 edge: best.edges()){
                Polygon_2D new_pol = change_path(path, edge, best);
                cout<<"here"<<endl;

                if(new_pol.is_simple()){
                    double area1 = best.area();
                    double area2 = new_pol.area();

                    if(!min_max.compare("-min")){
                        // dif = area1 - area2;
                        if(area1 > area2){
                            alternatives.push_back(new_pol);
                        }
                    }
                    else{
                        // dif = area2 - area1;
                        if(area1 < area2){
                            alternatives.push_back(new_pol);
                        }
                    }
                }
            }
            if(alternatives.size() > 0){
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
        }
        dif = best.area() - pol.area();
    }
    for(VertexIterator vit = best.vertices_begin(); vit != best.vertices_end(); vit++){
        cout<<vit->x()<<" "<< vit->y()<<endl;
    }
    for(EdgeIterator eit = best.edges_begin(); eit != best.edges_end(); eit++){
        cout<<*eit<<endl;
    }
    return best;
}