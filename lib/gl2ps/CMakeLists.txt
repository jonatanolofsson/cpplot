project(GL2PS)
set(CMAKE_CXX_FLAGS "-ggdb -Wall -Wextra -fPIC")
add_library(gl2ps SHARED gl2ps.c)
