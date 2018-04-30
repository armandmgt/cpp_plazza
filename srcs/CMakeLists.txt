set(SOURCE_FILES
        main.cpp
        args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        globals.cpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        master/Master.cpp shell/Shell.hpp shell/Shell.cpp CLIParser/CLIParser.cpp CLIParser/CLIParser.hpp)

add_executable(plazza ${SOURCE_FILES})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
