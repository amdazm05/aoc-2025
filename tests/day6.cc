#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>
#include <algorithm>

using namespace string_helpers;
std::string global_test_input_path;

TEST_CASE( "day6", "day6" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();

    /* Must have 3 entries */
    CHECK(entries>=3);

    std::string ops = inputs[entries-1];
    std::vector<std::string> ops_list = get_list_seperated_with_delim_st(ops,' ');
    inputs.pop_back();
    std::vector<std::vector<uint64_t>> rows;
    rows.reserve(entries);
    
    for (const auto in:inputs) {
        rows.push_back(get_list_seperated_with_delim(in,' '));
    }

    uint64_t result = 0;
    int n = rows.size();
    int m = rows[0].size();
    for (int i=0;i<m;i++) {
        uint64_t accum =0;
        for (int j=0;j<n;j++) {
            if(j==0) {
                accum +=rows[j][i];
                continue;
            }
            if(ops_list[i]=="*") {
                accum *=rows[j][i];
            }
            if(ops_list[i]=="+") {
                accum +=rows[j][i];
            }
        }
        result+=accum;
    }

    /* We have */
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);

    int nx = inputs.size();
    int mx = inputs[0].length();
    std::vector<std::vector<uint64_t>> rows_(ops_list.size());

    int count =0;
    int countx =0;
    for (int i=0;i<mx;i++) {
        std::string vs;
        for (int j=0;j<nx;j++) {
            /* j,i */
            if(inputs[j][i]==' ') continue;
            vs.push_back(inputs[j][i]);
        }
        if(vs.empty()) {
            count++;
            continue;
        }
        rows_[count].push_back(std::stoll(vs));
    }

    result = 0;
    int ny = rows_.size();
    for(int i =0; i<ny;i++) {
        uint64_t accum=0;
        accum+=rows_[i][0];
        for(int j =1; j<rows_[i].size();j++) {
            if(ops_list[i]=="*") {
                accum *=rows_[i][j];
            }
            if(ops_list[i]=="+") {
                accum +=rows_[i][j];
            }
        }
        result+=accum;
    }

    UNSCOPED_INFO("Part-2: "<<result);
    CHECK(true);
}

AOC_MAIN(global_test_input_path)
