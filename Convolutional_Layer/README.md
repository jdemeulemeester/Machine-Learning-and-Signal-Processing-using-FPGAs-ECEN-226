To create this project do the following:
1. Set folder as work directory in Vitis
2. Open a terminal
3. Enter the following in the terminal and hit enter: vitis-run --mode hls --tcl build_conv.tcl

The purpose of this project was to learn how to implement a convolutional layer on FPGA for machine learning processing. The Python scripts were provided by the instructor but I wrote the code for extracting the data files and turning into c++ 
header files. This project used the GEMM approach to convolution layers which first translates the input data using the Im2col function which then feeds into matrix multiplication. The top module GemmConv2d0 allowed me to setup a continuous 
flow of data between the data rearrangement and multiplication. The layer used fixed point data and had average error of 0.0074% and max error of 1.12%. The final Initiation Interval was 676, the same number as the number of nodes in the layer.
