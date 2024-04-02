# One-shot-learning

This program implements a linear regression algorithm to predict output values based on input data. It reads two files: a training file and a data file. The training file contains input and output values used to train the model, while the data file contains input values for which the output values need to be predicted.

## Output

The program will output the predicted output values for each row in the data file, one value per line.

## Implementation Details

The program performs the following steps:

1. Read the training and data files, and store the input and output values in dynamic 2D arrays.
2. Perform matrix operations (transpose, multiplication, and inversion) to calculate the weight vector `W` using the normal equation.
3. Use the weight vector `W` and the input data from the data file to predict the output values.
4. Print the predicted output values to the console.

## Memory Management

The program dynamically allocates memory for the 2D arrays used to store the input and output data, as well as the intermediate matrices used in the calculations. All dynamically allocated memory is properly deallocated before the program exits.

## Dependencies

This program requires the C standard library (`stdio.h` and `stdlib.h`) to be included.