set(EXAMPLES ex101_creating_a_plot ex102_mouse_and_keyboard_events ex103_multiple_plots ex104_style_and_color ex105_axes ex106_surface_and_contour ex107_3d_line_and_surface ex108_animation)
foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cc)
    target_link_libraries(${example} cpplot)
endforeach(example)

