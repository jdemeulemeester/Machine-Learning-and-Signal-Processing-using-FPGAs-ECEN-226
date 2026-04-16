open_component ./CNN1 -reset

set_top GemmConv2d0

# add c++ source files
add_files GemmConv2d0.cpp
add_files Im2col.cpp
add_files -tb conv_tb.cpp
add_files -tb image.dat
add_files -tb trace.dat

# add headers
add_files GemmConv2d0.h
add_files Im2col.h
add_files conv2d0_b.h
add_files conv2d0_w.h

# hw and clock
set_part {xc7k160tfbg676-2}
create_clock -period 10 -name default

csim_design
csynth_design

close_component