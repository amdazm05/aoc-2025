function(CompileTestFile TEST_NAME FILE_PATH)
    add_executable(${TEST_NAME} ${FILE_PATH})
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2)
endfunction(CompileTestFile FILE_PATH)
