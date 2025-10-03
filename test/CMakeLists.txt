set(T basic_test)

add_executable(${T} main.c)
target_include_directories(${T} PRIVATE ${CRITERION_DIR}/include)
target_link_directories(${T} PRIVATE ${CRITERION_DIR}/lib)
target_link_libraries(${T} PRIVATE edu_sort_and_search criterion m)
target_compile_options(${T} PRIVATE -Wall -Wextra -pedantic -Werror)

add_test(NAME ${T} COMMAND ${T})
