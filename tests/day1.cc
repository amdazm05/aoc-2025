#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <helper_macros.hpp>

#include <unordered_map>

using namespace string_helpers;
std::string global_test_input_path;

/* Return a pair first entry is direction -1, or 1 and second is rotation */ 
const std::pair<int,int> get_pair_from_rotation_string(const std::string & rot) {
    if(rot.empty()) throw std::runtime_error("null string");
    auto num_str = rot.substr(1,rot.length()-1);
    return {rot[0]=='L'?-1:1 , std::stoi(num_str)};
}

TEST_CASE( "day1", "day1" ) {

    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    int dial_start = 50; 
    std::unordered_map<uint8_t, int> countmap;
    std::unordered_map<uint8_t, int> countmap_pt2;
    std::vector<std::pair<int,int>> rotations_seq;

    for (auto input: inputs) {
        rotations_seq.emplace_back(get_pair_from_rotation_string(input));
    }

    for(auto rotation: rotations_seq) {
            int amount = rotation.second % 100;
            if (rotation.first < 0) {
                dial_start = (dial_start - amount + 100) % 100;
            } else {
                dial_start = (dial_start + amount) % 100;
            }
            countmap[dial_start]++;
    }
    UNSCOPED_INFO("Password Pt1:" << countmap[0]);
    CHECK(true);

    dial_start =50;
    for(auto rotation: rotations_seq) {
        int amount = rotation.second % 100;
        int zero_crossings = rotation.second/100;
        if (rotation.first < 0) {
            if((dial_start < amount) && dial_start!=0)
                countmap_pt2[0]++;
            dial_start = (dial_start - amount + 100) % 100;
        } else {
            if(dial_start + amount > 100)
                countmap_pt2[0]++;
            dial_start = (dial_start + amount) % 100;
        }
        countmap_pt2[dial_start]++;
        countmap_pt2[0]+=zero_crossings;
    }
    UNSCOPED_INFO("Password Pt2: "<< countmap_pt2[0]);
    CHECK(true);
}

AOC_MAIN(global_test_input_path)