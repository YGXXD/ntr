enable_testing()

add_executable(ntr_test ntr_test.cpp) 
add_executable(object_test object_test.cpp) 

target_link_libraries(ntr_test PRIVATE ntr)
target_link_libraries(object_test PRIVATE ntr)

add_test(ntr_test ntr_test)
add_test(object_test object_test)