open_component ./MLP1 -reset

set_top mlp

# add c++ source files
add_files mlp.cpp
add_files layer1.cpp
add_files layer2.cpp
add_files activation.cpp
add_files -tb mlp_tb.cpp
add_files -tb x_test.dat
add_files -tb y_test.dat

# add headers
add_files mlp.h
add_files layer1.h
add_files layer2.h
add_files activation.h
add_files w1.h
add_files w2.h
add_files b1.h
add_files b2.h
add_files sigmoid_coeffs.h

# hw and clock
set_part {xc7k160tfbg676-2}
create_clock -period 6.667 -name default

# directives
set_directive_pipeline layer1/col
set_directive_pipeline layer2/col

csim_design
csynth_design
cosim_design

# run implementation
export_design -flow impl
close_component