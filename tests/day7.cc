#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>
#include <algorithm>

using namespace string_helpers;
std::string global_test_input_path;

// void dfs(int i,int j, std::vector<std::string> & map) {
//     /* Beam splitter found */
//     if(i<0 || j<0 || j>=map[0].size() || i>=map.size())
//         return;
//     if(map[i][j]=='^') {
//         dfs(i,j+1,map);
//         dfs(i,j-1,map);
//         return;
//     }
//     map[i][j]='|';
//     dfs(i+1,j,map);
// }

void dfs(int i, int j, std::vector<std::string>& map,std::vector<std::vector<bool>> &visited) {
    int H = map.size();
    int W = map[0].size();
    if(j<0 or j>=W) return;
    if(visited[i][j]) return;
    visited[i][j]=true;
    while (i < H) {
        if (map[i][j] == '^') {
            dfs(i, j-1, map,visited);
            dfs(i, j+1, map,visited);
            return;
        }
        map[i][j] = '|';
        i++;
    }
}

uint64_t dfs_timeline(int i,int j,std::vector<std::string>& map,std::vector<std::vector<uint64_t>> & timelinescache) {
    if (i<0 or j<0 or j>=map[0].size())
        return 0;
    if(timelinescache[i][j]!=0) return timelinescache[i][j];
    if(map[i][j]=='|' and (i==map.size()-1)) return 1;
    if(i==map.size()-1) {
        return 0;
    }
    uint64_t result = 0;
    if(map[i][j]=='^') {
        result = dfs_timeline(i+1,j+1,map,timelinescache)+
                 dfs_timeline(i+1,j-1,map,timelinescache);
    }
    else {
        result = dfs_timeline(i+1,j,map,timelinescache);
    }
    return timelinescache[i][j]=result;
}

bool checkboundries(int i,int j,const std::vector<std::string> & map) {
    if(i<0 or j<0 or j>=map[0].size() or i>= map.size()) {
        return false;
    }
    if(i-1>=map.size())
        return false;
    if(map[i-1][j] == '|') {
        return true;
    }
    return false;
}

TEST_CASE( "day7", "day7" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    std::vector<std::vector<bool>> visited(inputs.size(),
                                    std::vector<bool>(inputs[0].size(),false));

    std::vector<std::vector<uint64_t>> timelinescache(inputs.size(),
                                 std::vector<uint64_t>(inputs[0].size(),0));

    int result = 0;
    std::pair<int,int> scoord;
    for (int i=0; i<inputs.size();i++) {
        for (int j=0;j<inputs[0].size();j++) {
            if(inputs[i][j]=='S') {
                scoord={i,j};
                dfs(i+1,j,inputs,visited);
                break;
            }
        }
    }
    for(int i=0; i<inputs.size();i++) {
        for(int j=0;j<inputs[0].size();j++) {
            if(inputs[i][j]=='^') {
                result += checkboundries(i,j,inputs)?1:0;
            }
        }
    }

    /* We have */
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);
    std::cout<<scoord.first+1<<" "<<scoord.second<<"---"<<inputs[scoord.first+1][scoord.second]<<std::endl;
    uint64_t result_ = dfs_timeline(scoord.first+1,scoord.second,inputs,timelinescache);

    UNSCOPED_INFO("Part-2: "<<result_);
    CHECK(true);
}

AOC_MAIN(global_test_input_path)
