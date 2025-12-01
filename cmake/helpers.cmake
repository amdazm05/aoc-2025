macro(SetCXXVersion EXECUTABLE_NAME COMPILER_STRING)
        target_compile_features(${EXECUTABLE_NAME} PRIVATE ${COMPILER_STRING})
endmacro()

macro(IncludeHeaderFolderToSource EXECUTABLE_NAME INCLUDE_PATH)
        target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_PATH})
endmacro()
