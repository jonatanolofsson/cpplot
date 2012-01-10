include_directories(${PROJECT_SOURCE_DIR}/src)
add_library(cpplot SHARED cpplot.cpp math.cpp glut.cpp figure.cpp layer.cpp axes.cpp color.cpp drawing.cpp line.cpp patch.cpp surface.cpp text.cpp)
target_link_libraries(cpplot
    ${GLUT_LIBRARY}
    ${OPENGL_LIBRARY}
    ${Boost_LIBRARIES}
    gl2ps)
