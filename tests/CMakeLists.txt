set(SOURCE_FILES
        test_args.cpp
        ../srcs/args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        ../srcs/globals.cpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        container/test_SplitMap.cpp
        ../srcs/master/Master.cpp
        ../include/Search.hpp
        ../srcs/Search.cpp
        test_search.cpp
        ../include/Shell.hpp
        ../srcs/Shell/Shell.cpp
        ../srcs/CLIParser/CLIParser.cpp
        ../include/CLIParser.hpp
        ../include/Data.hpp
        ../srcs/Slave/Slave.cpp
        ../include/Slave.hpp
        ../include/Load.hpp
        ../include/Serialization.hpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run criterion)

add_custom_command(TARGET tests_run POST_BUILD COMMAND ./tests_run)
