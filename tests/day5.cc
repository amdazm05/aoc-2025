#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>

#include <unordered_map>
#include <unordered_set>
#include <algorithm>


using namespace string_helpers;
std::string global_test_input_path;

TEST_CASE( "day5", "day5" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();

    std::vector<std::pair<uint64_t,uint64_t>> ranges;
    std::vector<uint64_t> store;
    std::unordered_set<uint64_t> uset;

    bool later_half =false;

    for(auto & in: inputs) {
        if(in.size()==0) {
            later_half = true;
            continue;
        }
        if(later_half) {
            store.push_back(std::stoll(in));
            continue;
        }
        if(!later_half) {
            auto res =get_list_seperated_with_delim(in,'-');
            ranges.push_back({res[0],res[1]});
        }
    }

    int result = 0;
    for (auto st: store) {
        for(auto p:ranges) {
            if(p.first <= st && p.second >= st){
                result++;
                break;
            }
        }
    }
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);

    uint64_t result_ = 0;
    /* Sorts by the first value by default */
    std::sort(ranges.begin(),ranges.end());
    std::vector<std::pair<uint64_t,uint64_t>> merged;

    int n = ranges.size();
    for(int i=0;i<n;i++) {
        auto [start,end] = ranges[i];
        if(!merged.empty() && merged.back().second >= end)
            continue;
        for(int k=i+1;k<n;k++) {
            if(ranges[k].first<=end) {
                end = std::max(end, ranges[k].second);
            }
        }
        merged.push_back({start,end});
        result_+=end-start+1;
    }

    UNSCOPED_INFO("Part-2: "<<result_);
    CHECK(true);
}

AOC_MAIN(global_test_input_path)
