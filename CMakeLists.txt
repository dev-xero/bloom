cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project ( BLOOM LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD 11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

# this would be included later
# set ( EXTERNAL external/stb_image.h )

# this is where we specify source files and headers
set ( SOURCE_BLOOM 
    src/materials/lambertian.cc
    src/materials/metal.cc
    src/camera.cc
    src/color.cc
    src/hittable.cc
    src/hittable_list.cc
    src/interval.cc
    src/main.cc
    src/ray.cc
    src/sphere.cc
    src/vec3.cc
)

# executables
# add_executable(bloom ${EXTERNAL} ${SOURCE_BLOOM})
add_executable( bloom ${SOURCE_BLOOM} )

target_include_directories( bloom PRIVATE include )
