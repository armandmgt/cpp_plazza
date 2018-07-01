project(plazza)

set(CORE
        main.cpp
        master/Master.cpp
        master/Master.hpp
        parser/Parser.cpp
        parser/Parser.hpp
        slave/Slave.cpp
        slave/Slave.hpp
        enums.hpp
        )

set(NETWORK
        network/LinkDescriptor.cpp
        network/LinkDescriptor.hpp
        serializable/ISerializable.hpp
        network/createSlave.cpp
        network/SocketStream.cpp
        network/SocketStream.hpp
        )

set(DATA
        serializable/Command.hpp
        serializable/Command.cpp
        serializable/Data.hpp
        serializable/Data.cpp
        )

set(SOURCE_FILES
        ${CORE}
        ${NETWORK}
        ${DATA}
        )

set(INCLUDES ${CMAKE_SOURCE_DIR}/srcs)

if (${GRAPHICAL})
    add_subdirectory(gui)
    link_directories(${GTKMM_LIBRARY_DIRS})
    include_directories(${GTKMM_INCLUDE_DIRS})
endif (${GRAPHICAL})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (${GRAPHICAL})
    target_compile_definitions(${PROJECT_NAME} PRIVATE GRAPHICAL=true)
    target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
endif (${GRAPHICAL})

target_link_libraries(${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/srcs)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
