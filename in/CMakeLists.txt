set(PROJECT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/tests/)

# Create the output folder
file(MAKE_DIRECTORY ${PROJECT_OUTPUT_DIR})

# Copy all .in files to bin directory
file(GLOB INPUT_FILES "${PROJECT_INPUT_DIR}/*.in")
foreach(f ${INPUT_FILES})
    configure_file(${f} ${PROJECT_OUTPUT_DIR} COPYONLY)
endforeach()