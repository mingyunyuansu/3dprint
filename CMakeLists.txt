cmake_minimum_required(VERSION 3.21)
project(neo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(neo main.cpp Point.cpp Point.h InputFromSTL.cpp InputFromSTL.h Constants.h Facet.cpp Facet.h OptimizedModel.cpp OptimizedModel.h STL2VTK.cpp STL2VTK.h Segment.cpp Segment.h Polygon.cpp Polygon.h Slicer.cpp Slicer.h Layer.cpp Layer.h Layers2VTK.cpp Layers2VTK.h Filler.cpp Filler.h)
