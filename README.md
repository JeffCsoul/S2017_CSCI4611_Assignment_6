# CSCI4611_Project_06
## Information
* Name: Tiannan Zhou
* Student ID: 5232494
* Email: zhou0745@umn.edu

## Config
Please replace the value of `shaderDir` in `config.hpp` file with the full path of your source code folder to make sure that the program can find the data to run the project properly.

## Compile
This program is based on Linux and you just need to use GNU Makefile to compile the whole project.
```
make
```
The recommended environment for compiling this project is CSELAB Ubuntu Linux 16.04.

## Run
You can find a executive program which is named `PencilPhysics` in the folder where the source code located in. You also can simply run command `./PencilPhysics` in terminal to start the program.

## Description
1. This project is based on OpenGL, GLM and Box2D libiary.
2. I added another parameter for Box and Circle class which name is `fixed: bool`, which is used to determine whether this box (or circle) is a static item. If the value is true, it will create a static box (or circle). This would highly reduce the number of repeated code.
3. I added a boolean variable to help control the mouse attaching action. The original way (using considering `NULL`) is a bit easy to cause misunderstanding.
