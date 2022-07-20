function(configure_compiler TARGET_NAME)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        #target_compile_options(${TARGET_NAME} PRIVATE "/Wall")
        target_compile_options(${TARGET_NAME} PRIVATE /W4)
    endif()

endfunction()
