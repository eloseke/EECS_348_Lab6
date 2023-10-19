/*
Author: Eric Loseke
KUID: 3082068
Date created: 18 October 2023
Lab: lab6
Purpose: Perform sum, product, and difference opeations on two square matrices
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Functional prototypes
void print_matrix(int matrix[], int size);
int * matrix_sum(int matrix_a[], int matrix_b[], int size);
int * matrix_product(int matrix_a[], int matrix_b[], int size);
int * matrix_difference(int matrix_a[], int matrix_b[], int size);

int main() //Run program
{
	int SIZE = 100;
	int size = 0;
	int matrix_a[SIZE];
	int matrix_b[SIZE];

	//Print header and get file name from the user
	string file_name = "";
	cout << "\nEric Loseke\nLab #6: Matrix manipulation\n\nEnter name of input file: ";
	cin >> file_name;

	//Open file
	ifstream inFile;
	inFile.open(file_name);

	//Add integers from file to two 1D arrays containing matrices A and B
	try
	{
		if (inFile.is_open())
		{
			inFile >> size;
			if (size > SIZE)
			{
				//Size of matrices must be less than or equal to 100
				inFile.close();
				throw(runtime_error("Size must be less than or equal to 100"));
			}
			for (int i=0; i<(size*size*2); i++)
			{
				if (i < (size*size))
				{
					inFile >> matrix_a[i];
				}
				else
				{
					inFile >> matrix_b[i-(size*size)];
				}
			}
		}
		else
		{
			//File name is invalid
			throw(runtime_error("Invalid file name"));
		}

		//Close file
		inFile.close();

		//Print matrix A
		cout << "\nMatrix A:\n";
		print_matrix(matrix_a, size);

		//Print matrix B
		cout << "\nMatrix B:\n";
		print_matrix(matrix_b, size);

		//Store sum of matrices A and B and print the sum
		cout << "\nMatrix Sum (A + B):\n";
		int *sum_matrix = matrix_sum(matrix_a, matrix_b, size);
		print_matrix(sum_matrix, size);

		//Store product of matrices A and B and print the product
		cout << "\nMatrix Product (A * B):\n";
		int *product_matrix = matrix_product(matrix_a, matrix_b, size);
		print_matrix(product_matrix, size);

		//Store difference of matrices A and B and print the difference
		cout << "\nMatrix Difference (A - B):\n";
		int *difference_matrix = matrix_difference(matrix_a, matrix_b, size);
		print_matrix(difference_matrix, size);
		cout << "\n";

		return 0; //End the function
	}

	//Print error message
	catch(runtime_error& rte)
	{
		cout << "Error: " << rte.what() << "\n";
	}
}

void print_matrix(int matrix[], int size) //Print matrix
{
	int width = 0;

	//Set width of matrix columns
	for (int i=0; i<(size*size); i++)
	{
		if (int(log10(matrix[i])+1) > width)
		{
			width = int(log10(matrix[i])+1);
		}
	}

	//Print 1D array as a matrix
	for (int i=0; i<(size*size); i++)
	{
		cout << right << setw(width) << matrix[i] << " ";
		if ((i+1) % size == 0)
		{
			cout << "\n";
		}
	}
}

int * matrix_sum(int matrix_a[], int matrix_b[], int size) //Return sum of two matrices
{
	static int output_matrix[sizeof (size*size)]; //Create 1D array for sum of matrices

	//Sum each element in the matrices and add result to corresponding element in output array
	for (int i=0; i<(size*size); i++)
	{
		output_matrix[i] = matrix_a[i] + matrix_b[i];
	}
	return output_matrix; //Return 1D array containing the sum of two matrices
}

int * matrix_product(int matrix_a[], int matrix_b[], int size) //Return product of two matrices
{
	int a[size][size];
	int b[size][size];
	int c[size][size];

	//Convert 1D input arrays into 2D arrays
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			a[i][j] = matrix_a[i*size+j];
			b[i][j] = matrix_b[i*size+j];
		}
	}

	static int output_matrix[sizeof (size*size)]; //Create 1D array for product of matrices
	int element_sum;

	//Calculate product of two matrices and add result to each element of a 2D array
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			element_sum = 0;
			for (int k=0; k<size; k++)
			{
				element_sum += (a[i][k]*b[k][j]);
				c[i][j] = element_sum;
			}
		}
	}

	//Convert 2D array to 1D array
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			output_matrix[(3*i)+j] = c[i][j];
		}
	}
	return output_matrix; //Return 1D array containing the product of two matrices
}

int * matrix_difference(int matrix_a[], int matrix_b[], int size) //Return difference of two matrices
{
	static int output_matrix[sizeof (size*size)]; //Create 1D array for difference of matrices

	//Get A-B for each element in the matrices and add result to the corresponding element in output array
	for (int i=0; i<(size*size); i++)
	{
		output_matrix[i] = matrix_a[i] - matrix_b[i];
	}
	return output_matrix; //Return 1D array containing the difference of two matrices
}
