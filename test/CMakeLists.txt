enable_testing()

add_executable(ntr_test ntr_test.cpp) 
target_link_libraries(ntr_test PRIVATE ntr)
add_test(ntr_test ntr_test)