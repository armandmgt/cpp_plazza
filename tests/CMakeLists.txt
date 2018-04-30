set(SOURCE_FILES
        test_args.cpp
        ../srcs/args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        ../srcs/globals.cpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        container/test_SplitMap.cpp
        ../srcs/master/Master.cpp ../srcs/shell/Shell.hpp ../srcs/shell/Shell.cpp ../srcs/CLIParser/CLIParser.cpp ../srcs/CLIParser/CLIParser.hpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run criterion)

add_custom_command(TARGET tests_run POST_BUILD COMMAND ./tests_run)
