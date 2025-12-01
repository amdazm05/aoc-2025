# include helpers
include(helpers)

file(GLOB SRC_FILES ${PROJECT_SRC_DIR}/*.cc 
                    ${PROJECT_SRC_DIR}/*.cpp)

add_library(aoc_src_lib STATIC ${SRC_FILES})
IncludeHeaderFolderToSource(aoc_src_lib ${PROJECT_INCLUDE_DIR})
SetCXXVersion(aoc_src_lib ${COMPILER_CXX_VERSION})
