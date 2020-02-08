set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        test_args.cpp
        test_search.cpp
        container/test_SplitMap.cpp
	../srcs/constants.hpp
	../srcs/enums.hpp
	../srcs/main.cpp
        ../srcs/master/Master.hpp
        ../srcs/master/Master.cpp
	../srcs/network/LinkDescriptor.hpp
	../srcs/network/LinkDescriptor.cpp
	../srcs/network/SocketStream.hpp
	../srcs/network/SocketStream.cpp
	../srcs/network/createSlave.cpp
	../srcs/parser/Parser.hpp
	../srcs/parser/Parser.cpp
	../srcs/serializable/Command.hpp
	../srcs/serializable/Command.cpp
	../srcs/serializable/Data.hpp
	../srcs/serializable/Data.cpp
	../srcs/serializable/ISerializable.hpp
	../srcs/slave/Slave.hpp
        ../srcs/slave/Slave.cpp
        )

add_custom_target(data DEPENDS hiden_data)

configure_file(hiden_data hiden_data COPYONLY)
add_executable(tests_run ${SOURCE_FILES})

add_dependencies(tests_run data)

target_include_directories(tests_run PRIVATE /usr/local/Cellar/criterion/2.3.3/include/)
target_link_libraries(tests_run criterion)

add_custom_command(TARGET tests_run POST_BUILD COMMAND ./tests_run)
