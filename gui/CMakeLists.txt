set(SOURCE_FILES
        ../include/Graphic.hpp
        Graphic.cpp
        ../include/MyButton.hpp
        ../include/Master.hpp
        ../srcs/master/Master.cpp
        ../srcs/Shell/Shell.cpp
        ../include/Shell.hpp
        ../include/CLIParser.hpp
        ../srcs/CLIParser/CLIParser.cpp
        ../include/Slave.hpp
        ../srcs/Slave/Slave.cpp
        ../include/Search.hpp
        ../srcs/Search.cpp
        ../srcs/globals.cpp
        ../include/Load.hpp
        MyButton.cpp Frame.cpp
        ../include/Frame.hpp
        Utils.cpp
        ../include/Utils.hpp
        ../srcs/tools.cpp
        ../include/plazza.hpp)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS} )

add_executable(plazzaui ${SOURCE_FILES})

target_link_libraries(plazzaui
        ${GTKMM_LIBRARIES} pthread)

add_custom_command(TARGET plazzaui POST_BUILD
        COMMAND cp plazzaui ${PROJECT_SOURCE_DIR})
