add_library(myopt optimizer.cpp optimizer.hpp)

# include the Eigen directory
include_directories(${EIGEN_DIR})
target_include_directories(myopt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
