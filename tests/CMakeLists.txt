set(SOURCE_FILES test_args.cpp ../srcs/args_check.cpp ../include/plazza.hpp ../include/Exceptions.hpp ../srcs/globals.cpp ../include/Master.hpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run criterion)

add_custom_command(TARGET tests_run POST_BUILD COMMAND ./tests_run)
