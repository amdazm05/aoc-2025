#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <unordered_map>
#include <unordered_set>
#include <stack>

std::string global_test_input_path;
using namespace string_helpers;

uint64_t max_num_from_digits (const std::string & s, int digits) {
    int remove_bank=s.length()-digits;
    std::stack<char> st;
    std::string str;

    if(s.length() < digits) {
        return 0;
    }

    for(const auto & ch: s) {
        while(!st.empty() && ch > st.top() && remove_bank>0) {
            st.pop();
            remove_bank--;
        }
        st.push(ch);
    }
    while(st.size()>digits) st.pop();

    while(!st.empty()) {
        str = st.top() + str;
        st.pop();
    }
    return std::stoll(str);
}

TEST_CASE( "day3", "day3" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    int result = 0;

    /* Iterate each row */
    for (const auto & in: inputs) {
        int mx = INT32_MIN;
        for(int l=0;l<in.length();l++) {
            for(int r=in.length()-1;r>l;r--) {
                std::string num_str;
                num_str+=in[l];
                num_str+=in[r];
                mx = std::max(mx,std::stoi(num_str));
            }
        }
        result+=mx;
    }

    /* exactly twelve Joltages */
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);

    uint64_t result_p2 = 0;
    int window_size=12;
    for(int i =0; const auto &in: inputs) {
        result_p2+= max_num_from_digits (in,window_size);
        i++;
    }

    UNSCOPED_INFO("Part 2 result: "<<result_p2);
    CHECK(true);
}

int main(int argc, char* argv[]) {
    Catch::Session session;

    using namespace Catch::Clara;

    auto cli =
        session.cli()
        | Opt(global_test_input_path, "file")
            ["--input"]
            ("input file for test");

    session.cli(cli);

    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0)
        return returnCode;

    return session.run();
}


/* */