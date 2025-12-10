#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>
#include <geometry.hpp>

#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace geo;
using namespace geo_helpers;
using P2 = point2D<uint64_t>;
using namespace string_helpers;

using PQpoints2D_mx =
            std::priority_queue<
                std::pair<int,int>,
                std::vector<std::pair<int,int>>,
                std::greater<>
                >;

std::string global_test_input_path;

TEST_CASE( "day8", "day8" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    std::vector<P2> coords;
    PQpoints2D_mx pq;
    for(auto in:inputs) {
        P2 p2 = get_coords_from_string_2D(in);
        coords.push_back(p2);
        pq.push({p2.x,p2.y});
    }

    uint64_t mx = 0;
    int n  = coords.size();
    for(int i =0;i<n;i++) {
        for(int j=i+1;j<n;j++){
            int64_t dx = coords[i].x-coords[j].x+1;
            int64_t dy = coords[i].y-coords[j].y+1;
            uint64_t mul = static_cast<uint64_t>(std::llabs(dx)) *
               static_cast<uint64_t>(std::llabs(dy));
            mx = std::max(mul,mx);
        }
    }
    std::cout<<mx<<std::endl;

    std::vector<int> xmap;
    std::vector<int> ymap;

    for(auto & coord:coords) {
        xmap.push_back((int)coord.x);
        ymap.push_back((int)coord.y);
    }
    
    std::sort(xmap.begin(),xmap.end());
    xmap.erase(std::unique(xmap.begin(),xmap.end()),xmap.end());
    std::sort(ymap.begin(),ymap.end());
    ymap.erase(std::unique(ymap.begin(),ymap.end()),ymap.end());
    
    /* This is a baseline */

    std::unordered_map<int,int> uxmap, uymap;
    /* All map coordinates are compressed */
    for(int i=0;i<xmap.size();i++) uxmap[xmap[i]]=i;
    for(int i=0;i<ymap.size();i++) uymap[ymap[i]]=i;

    const int M = ymap.size();
    const int N = xmap.size();
    std::cout<<"M,N:"<<M<<","<<N<<std::endl;
    
    std::vector<std::vector<char>> 
            inclusion(M,std::vector<char>(N,'0'));
    
    for (int k=0;k<n;k++) {
        P2 xn = coords[k];
        P2 xn1 = coords[(k+1)%n];
        if(xn.x==xn1.x) {
            int m1y = uymap[std::min(xn.y,xn1.y)];
            int m2y = uymap[std::max(xn.y,xn1.y)];
            for (int i=m1y;i<=m2y;i++) {
                /* Identify them as a included in the shape */
                inclusion[i][uxmap[xn.x]]='1';
            }
        }
        else if(xn.y==xn1.y) {
            int m1x = uxmap[std::min(xn.x,xn1.x)];
            int m2x = uxmap[std::max(xn.x,xn1.x)];
            for (int i=m1x;i<=m2x;i++) {
                /* Identify them as a included in the shape */
                inclusion[uymap[xn.y]][i]='1';
            }
        }
    }

    /* dir */
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    std::queue<std::pair<int,int>> q;
    /* Do a flood fill */
    for(int i=0;i<M;i++) {
        if(inclusion[i][0]=='0') {
            inclusion[i][0]='E';
            q.push({i,0});
        }
        if(inclusion[i][N-1]=='0') {
            inclusion[i][N-1]='E';
            q.push({i,N-1});
        }
    }

    for(int i=0;i<N;i++) {
        if(inclusion[0][i]=='0') {
            inclusion[0][i]='E';
            q.push({0,i});
        }
        if(inclusion[M-1][i]=='0') {
            inclusion[M-1][i]='E';
            q.push({M-1,i});
        }
    }

    while(!q.empty()) {
        auto [j,i] =q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = j + dy[d];
            int nx = i + dx[d];
            if(ny>=0 && ny<M && nx>=0 && nx<N && inclusion[ny][nx]=='0'){
                inclusion[ny][nx]='E';
                q.push({ny,nx});
            }
        }
    }

    for(auto & inc:inclusion) {
        for(auto & in:inc) {
            if(in=='0') in='1';
        }
    }

    mx = 0;
    for(int i=0;i<n;i++) {
        for(int j=i;j<n;j++) {
            int64_t dx = std::llabs(coords[i].x-coords[j].x)+1;
            int64_t dy = std::llabs(coords[i].y-coords[j].y)+1;

            auto [xi,yi]=std::pair<int,int>({uxmap[coords[i].x],uymap[coords[i].y]});
            auto [xj,yj]=std::pair<int,int>({uxmap[coords[j].x],uymap[coords[j].y]});
            auto [xk,yk]=std::pair<int,int>({xi,yj});
            auto [xl,yl]=std::pair<int,int>({xj,yi});

            // (xj,yi)   *****************   (xi,yi)
            //           *****************
            //           EEE**************
            // (xj,yj)   *****************   (xi,yj)
            
            
            if(xi==xj) continue;
            if(yi==yj) continue;
            if(inclusion[yk][xk]=='1' && inclusion[yl][xl]=='1') {
                bool iscrossing =false;
                int xstart = std::min(xi,xj);
                int xend   = std::max(xi,xj);
                int ystart = std::min(yi,yj);
                int yend   = std::max(yi,yj);

                // Check vertical edges
                for (int y = ystart; y <= yend; y++) {
                    if (inclusion[y][xi] == 'E' || inclusion[y][xj] == 'E') {
                        iscrossing = true;
                        break;
                    }
                }

                // Check horizontal edges
                for (int x = xstart; x <= xend; x++) {
                    if (inclusion[yi][x] == 'E' || inclusion[yj][x] == 'E') {
                        iscrossing = true;
                        break;
                    }
                }

                if(iscrossing) {
                    continue;
                }
                else {
                    uint64_t mul = static_cast<uint64_t>(std::llabs(dx)) *
                    static_cast<uint64_t>(std::llabs(dy));
                    mx = std::max(mul,mx);
                }
            }
        }
    }
    std::cout<<"Result-2 "<<mx<<std::endl;
}

AOC_MAIN(global_test_input_path)