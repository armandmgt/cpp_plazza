set(SOURCE_FILES
        main.cpp
        args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        globals.cpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        master/Master.cpp
        ../include/Search.hpp
        Search.cpp
        ../include/Shell.hpp
        ../srcs/Shell/Shell.cpp
        ../srcs/CLIParser/CLIParser.cpp
        ../include/CLIParser.hpp
        ../include/Data.hpp
        Slave/Slave.cpp
        ../include/Slave.hpp
        ../include/Load.hpp
        ../include/Serialization.hpp)

add_executable(plazza ${SOURCE_FILES})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
