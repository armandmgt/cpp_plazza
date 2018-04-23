set(SOURCE_FILES main.cpp args_check.cpp ../include/plazza.hpp ../include/Exceptions.hpp globals.cpp ../include/Master.hpp master.cpp)

add_executable(plazza ${SOURCE_FILES})

add_custom_command(TARGET plazza POST_BUILD COMMAND cp plazza ${PROJECT_SOURCE_DIR})
