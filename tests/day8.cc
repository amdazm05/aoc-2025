#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>
#include <geometry.hpp>
#include <disjoint_set.hpp>

#include <queue>

using namespace string_helpers;
using namespace geo;
using namespace geo_helpers;
using P3 = point3D<uint64_t>;
using PQpoints3D = 
            std::priority_queue<
                std::pair<uint64_t,std::pair<int,int>>,
                std::vector<std::pair<uint64_t,std::pair<int,int>>>,
                std::greater<>
                >;

std::string global_test_input_path;

TEST_CASE( "day8", "day8" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    std::vector<P3> coords;

    for(auto in:inputs) {
        auto p3 = get_coords_from_string(in);
        coords.push_back(p3);
    }

    PQpoints3D pq;
    auto n = coords.size();
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            auto p3D = to_point_distance_sqrd(coords[i],coords[j]);
            /* Parent-i and Child -j*/
            pq.push({p3D,{i,j}});
        }
    }
    
    PQpoints3D pq2=pq;
    disjoint_set dsu(n);
    std::vector<int> size;
    int limit = 10; /* This needs to be configured */
    while(limit>0 && !pq.empty()) {
        auto [_,a] = pq.top();
        auto [i,j] = a;
        pq.pop();
        dsu.unite(i,j);
        limit--;
    }

    for(int i =0;i<n;i++) {
        if(dsu.find(i) == i) {
            size.push_back(dsu.get_size(i));
        }
    }
    std::sort(size.begin(),size.end(),std::greater<int>());
    int result = size[0]*size[1]*size[2];
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);

    disjoint_set dsu2(n);
    limit = n;
    auto [li,lj] = std::pair<int,int> (-1,-1);
    while(limit>1 and !pq2.empty()) {
        auto [_,a] = pq2.top();
        auto [i,j] = a;
        pq2.pop();
        if(dsu2.unite(i,j)) {
            limit--;
            li = i;
            lj = j;
        }
    }

    uint64_t x1 = coords[li].x;
    uint64_t x2 = coords[lj].x;
    result = x1*x2;
    UNSCOPED_INFO("Part-2: "<<result);
    CHECK(true);

}

AOC_MAIN(global_test_input_path)
