set(SOURCE_FILES
        ../include/Graphic.hpp
        Graphic.cpp)

add_executable(plazza ${SOURCE_FILES})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
