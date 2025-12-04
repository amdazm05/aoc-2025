#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string_utils.hpp>

using namespace string_helpers;
std::string global_test_input_path;

// |  j
// -> i
inline int grid_check(int i, int j, std::vector<std::string> & grid) {
    if(i > (grid.size()-1) || j > (grid[0].size()-1))
        return 0;
    if(i < 0 || j<0) return 0;
    if(grid[i][j]=='@') return 1;
    if(grid[i][j]=='x') return 1;
    /* default . case */
    return 0;
}


TEST_CASE( "day4", "day4" ) {
    auto inputs = get_inputs_from_file(global_test_input_path);
    auto entries = inputs.size();
    auto & grid = inputs;
    int result = 0;
    for (int i = 0; auto & row: grid) {
        for (int j = 0; j < row.size();j++) {
            if(row[j] == '.') continue;
            int sum =
                grid_check(i+1,j+1,grid) +
                grid_check(i+1,j-1,grid) +
                grid_check(i+1,j,grid) +
                grid_check(i-1,j+1,grid) +
                grid_check(i-1,j-1,grid) +
                grid_check(i-1,j,grid) +
                grid_check(i,j+1,grid) +
                grid_check(i,j-1,grid);
            if (sum<4) {
                result++;
            }
        }
        i++;
    }

    UNSCOPED_INFO("Part-1: "<<result);
    CHECK(true);
    int prev = 1;
    int accum =0;
    while(prev!=0){
        result = 0;
        for (int i = 0; auto & row: grid) {
            for (int j = 0; j < row.size();j++) {
                if(row[j] == '.') continue;
                int sum =
                    grid_check(i+1,j+1,grid) +
                    grid_check(i+1,j-1,grid) +
                    grid_check(i+1,j,grid) +
                    grid_check(i-1,j+1,grid) +
                    grid_check(i-1,j-1,grid) +
                    grid_check(i-1,j,grid) +
                    grid_check(i,j+1,grid) +
                    grid_check(i,j-1,grid);
                if (sum<4) {
                    row[j]='x';
                    result++;
                }
            }
            i++;
        }

        for(auto &row : grid) {
            for(auto &col:row) {
                if(col =='x')
                    col = '.';
            }
        }
        accum+=result;
        prev = result;
    }

    UNSCOPED_INFO("Part-2: "<<accum);
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


//@@@
//...
//...