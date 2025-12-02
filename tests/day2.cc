#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>
#include <unordered_map>

std::string global_test_input_path;
using namespace string_helpers;

#define IS_EVEN(number) (number%2==0)

inline int count_digits(uint64_t number) {
    int digits = 0; 
    while (number != 0) {
        number /= 10; 
        digits++; 
    }
    return digits;
}

TEST_CASE( "day2", "day2" ) {
    auto inputs = get_inputs_from_file(global_test_input_path,',');
    auto entries = inputs.size();
    uint64_t result = 0;
    for (auto i_str: inputs) {
        auto pair = get_list_seperated_with_delim(i_str,'-');
        /* pair[0] < pair[1] */
        for(uint64_t i = pair[0]; i<=pair[1]; i++) {
            /* Odd digits cannot be invalid */ 
            if(!IS_EVEN(count_digits(i)))
                continue;
            /* Divide int to half */
            std::string num_str = std::to_string(i);
            int len = num_str.length()/2;
            std::string rstr = num_str.substr(0,len);
            std::string lstr = num_str.substr(len,len);
            // std::cout<<lstr<<" -- "<<rstr<<std::endl;
            if(rstr==lstr) {
                // std::cout<<num_str<<std::endl;
                result+=i;
            }
        }
    }
    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);

    /* This is to see how many possible repitions are possible for a number of digits */
    std::unordered_map<int,std::vector<int>> multi;
    for (int i=1;i<20;i++) {
        for (int j=1;j<i;j++) {
            if(i%j==0) {
                multi[i].push_back(j);
            }
        }
    }

    result=0;
    for (auto i_str: inputs) {
        auto pair = get_list_seperated_with_delim(i_str,'-');
        /* pair[0] < pair[1] */
        for(uint64_t i = pair[0]; i<=pair[1]; i++) {
            std::string num_str = std::to_string(i);
            auto len = num_str.length();
            bool add = false;
            for(const auto & v: multi[len]) {
                    bool chk = true;
                    std::string subs= num_str.substr(0,v);
                    for(std::size_t p=v;p<num_str.length();p+=v) {
                        std::string check = num_str.substr(p,v);
                        if(check==subs) continue;
                        else { 
                            chk=false; 
                            break;
                        }
                    }
                    if(chk)
                        add=true;
            }
            if(add) 
                result+=i;
        }
    }
    UNSCOPED_INFO("Part 2 result: "<<result);
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