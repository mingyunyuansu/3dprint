cmake_minimum_required(VERSION 3.21)
project(neo)

set(CMAKE_CXX_STANDARD 14)

add_executable(neo main.cpp Point.cpp Point.h InputFromSTL.cpp InputFromSTL.h Constants.h Facet.cpp Facet.h OptimizedModel.cpp OptimizedModel.h STL2VTK.cpp STL2VTK.h)
