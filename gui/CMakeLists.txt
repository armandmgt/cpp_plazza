set(SOURCE_FILES
        ../include/Graphic.hpp
        Graphic.cpp
        ../include/MyButton.hpp
        ../include/Master.hpp
        ../srcs/master/Master.cpp
        MyButton.cpp Frame.cpp ../include/Frame.hpp)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS} )

add_executable(plazzaui ${SOURCE_FILES})

target_link_libraries(plazzaui
        ${GTKMM_LIBRARIES} stdc++fs)

add_custom_command(TARGET plazzaui POST_BUILD
        COMMAND cp plazzaui ${PROJECT_SOURCE_DIR})
