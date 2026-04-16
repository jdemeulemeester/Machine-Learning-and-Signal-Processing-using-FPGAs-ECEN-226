This code implements a 3-layer mutlilayer perceptron. This nueral network is trained in python using the MNIST test set in Jupyter Notebook to identify hand written digits from 0 - 9. In the Python code the model is trained and accuracy displayed.
After training the model in Python, then the weights and biases are quantized to simulate fixed point on the FPGA and get an idea for the expected accuracy using fixed point before implementing on FPGA. The python also saves the input and output 
test sets as dat files to use in the C++ testbench. The weights (w1.h and w2.h) and biases (b1.h and b2.h) were converted from data structures in python into c++ .h files so that they can easily be imported into Vitis HLS and so that 
they can be intiallized as stored memory during synthesis instead of inputs. The accuracy achieved with a fixed point implementation is 90.3% and the resources/timing achieved are: 
BRAM 63
DSP48 5
FF 1542
LUT 3270
Initiation Interval (II) 20611
