#########################################################################
# This README refers only to the directory cuRk4 in which the parallelised
# version of the Runge-Kutta method is implemented using CUDA
#########################################################################

# ------------------- File structure ---------------------
This directory consists of following files/directories:

    - Makefile: Configuration for compilation
                In line: all: ./bin/repr_rk4
                you can modify the name of the compiled program 'repr_rk4'

    - bin: The compiled executable will be stored in this directory
           If you want to change the output directory, you can modify it in the Makefile

    - inc: Includes following header files:
        - chCommandLine.h: simple command line parsing functions.
        - chTimer.h: simple time measurement functions.
        - chTimer.hpp: c++ wrapper class for the chTimer.h functions.
        - runge_kutta.hh: Solvers for Runge-Kutta order 4 method RK4  (normally no need to modify)
        - repressilator.hh: Class Repressilator describing the model: dYdt = S*R - d*Y
        - utility.hh: Helping functions

    - lib: Should be empty, just added for completeness

    - src:
        - repr_rngkutta.cu: Main function creating the biologic system class and calling the solver (adapt parameters here!)

    - script.sh: Bash script to test program for several input sizes (good for testing!)



# --------------------- Requirements ------------------------------
Make sure to have a CUDA compatible GPU with the appropriate driver, and compute capability 3.5 or higher. You also need the cuBLAS library from the CUDA toolkit, available at https://developer.nvidia.com/cuda-toolkit


# ------------------- Getting started ----------------------

1) Compile the program using the Makefile with :
                        > make

                        Remark: If you add or delete some files, don't forget to
                                adapt the Makefile
                        Remark: If you want to delete compiled files
                                > make clean

2) Call program: you can use --help to see what is available in command line options :
                        > ./bin/rk4 --help



# -------------------- Modify programs -------------------------
If you want to modify the programs/parameters, consider the comments of this form:

// !! this is a sample comment !!

Probably you will essentially modify the main function in the file src/repr_rngkutta.cu,
check these type of comments and you will see where you can change parameters/
initial values etc.

If you want to modify the model of the Repressilator, you can do this in the file
inc/repressilator.hh

Normally you don't need to modify the solver Runge-Kutta methods in the file
inc/runge_kutta.hh , except if you optimise it

