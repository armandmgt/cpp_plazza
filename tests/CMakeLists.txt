set(SOURCE_FILES
        test_args.cpp
        ../srcs/args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        container/test_SplitMap.cpp
        ../srcs/master/Master.cpp
        ../include/Search.hpp
        ../srcs/Search.cpp
        test_search.cpp)


add_custom_target(data DEPENDS hiden_data)

configure_file(hiden_data hiden_data COPYONLY)
add_executable(tests_run ${SOURCE_FILES})

add_dependencies(tests_run data)

target_link_libraries(tests_run criterion)

add_custom_command(TARGET tests_run POST_BUILD COMMAND ./tests_run)
