cmake_minimum_required(VERSION 3.8)

project(rt-intro)
set(CMAKE_CXX_STANDARD 17)

add_executable(raytrace main.cpp Sphere.cpp IHittable.cpp HittableList.cpp)
