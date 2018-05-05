set(SOURCE_FILES
        main.cpp
        args_check.cpp
        ../include/plazza.hpp
        ../include/Exceptions.hpp
        tools.cpp
        ../include/Master.hpp
        ../include/container/SplitMap.hpp
        Master/Master.cpp
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
        ../include/Serialization.hpp
        Serialization.cpp)

if (${GRAPHICAL})
    add_subdirectory(gui)
    link_directories(${GTKMM_LIBRARY_DIRS})
    include_directories(${GTKMM_INCLUDE_DIRS})

    add_executable(plazza ${SOURCE_FILES})
    target_compile_definitions(plazza PRIVATE GRAPHICAL=true)
    target_link_libraries(plazza ${GTKMM_LIBRARIES})
else (${GRAPHICAL})
    add_executable(plazza ${SOURCE_FILES})
endif (${GRAPHICAL})

target_link_libraries(plazza pthread)

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
