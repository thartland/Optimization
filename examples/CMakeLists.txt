add_executable(rosenbrock rosenbrock.cpp rosenbrock.cpp)
target_link_libraries(rosenbrock PRIVATE myopt)
target_include_directories(rosenbrock PUBLIC ${EIGEN_DIR})
