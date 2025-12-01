macro(SetCXXVersion EXECUTABLE_NAME COMPILER_STRING)
        target_compile_features(EXECUTABLE_NAME PRIVATE COMPILER_STRING)
endmacro()
