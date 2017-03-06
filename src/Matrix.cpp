/*
 *AUTHOR:       Alexander Adranly
 *
 *DESCRIPTION:  Implementation of the Matrix abstract data type
 */
#include <iostream>
#include <cassert>
#include "Matrix.hpp"

/* CONSTRUCTORS */
Matrix::Matrix(size_t width){
  /*
    @param: (size_t) width: defines the width of the square matrix
    @description: given a width, this function constructs a square matrix
  */
  // assign descriptors
  WIDTH = width;

  // allocate matrix
  field = new int*[WIDTH];

  for(int r = 0; r < WIDTH; r++)
    field[r] = new int[WIDTH];

  // set all values in matrix to zero
  clear();
}

/* DESTRUCTOR */
Matrix::~Matrix(){
  /*
    @description: de-allocates the memory associated to the ADT
  */
  // free memory associated to the 2d array
  for(int r = 0; r < WIDTH; r++)
    delete [] field[r];

  delete [] field;
}

/* COPY CONSTRUCTOR */
Matrix::Matrix(const Matrix& src){
  /*
    @param: (const Matrix&) src:
    @description:
  */
  WIDTH = src.WIDTH;

  // allocate new matrix
  field = new int*[WIDTH];

  for(int r = 0; r < WIDTH; r++)
    field[r] = new int[WIDTH];

  // copy the matrices
  for(int r = 0; r < WIDTH; r++){
    for(int c = 0; c < WIDTH; c++){
      field[r][c] = src.field[r][c];
    }
  }
}

/* ACCESSORS */
int Matrix::getMinOfRow(size_t row){
  /*
    @param: (size_t) row:
    @description:
  */
  assert(row < WIDTH);
  int minimum_value = field[row][0]; // first element
  for(int c = 1; c < WIDTH; c++){
    minimum_value = std::min(field[row][c], minimum_value);
  }
  return minimum_value;
}

int Matrix::getMinOfCol(size_t col){
  /*
    @param: (size_t) col:
    @description:
  */
  assert(col < WIDTH);
  int minimum_value = field[0][col]; // first element
  for(int r = 1; r < WIDTH; r++){
    minimum_value = std::min(field[r][col], minimum_value);
  }
  return minimum_value;
}

/* MUTATORS */
void Matrix::clear(){
  /*
    @description: sets all elements in the matrix to zero
  */
  for(int r = 0; r < WIDTH; r++){
    for(int c = 0; c < WIDTH; c++){
      field[r][c] = 0;
    }
  }
}

void Matrix::randomize(int limit){
  /*
    @param: (int) limit:
    @description: assigns random values from the matrix of 0 to limit
  */
  srand(17);
  for(int r = 0; r < WIDTH; r++){
    for(int c = 0; c < WIDTH; c++){
      field[r][c] = (rand() % limit) + 1;
    }
  }
}

/* DISPLAY */
void Matrix::hungarianState(int row_reduce[], int col_reduce[]){
  /* */
  // ASSUMING ARRAYS PASSED HAVE SAME LENGTH AS WIDTH OF MATRIX
  // display column reduction
  std::cout << "\t\t[";
  for(int c = 0; c < WIDTH; c++)
    printf("\t%d\t", col_reduce[c]);
  std::cout << "]\n" << std::endl;

  // display row and column
  for(int r = 0; r < WIDTH; r++){
    printf("Machine %d: [%d]\t[", r, row_reduce[r]);
    for(int c = 0; c < WIDTH; c++){
      std::cout << "\t" << field[r][c] << "\t";
    }
    std::cout << "]" << std::endl;
  }
}

/* OPERATORS */
int& Matrix::operator()(size_t row, size_t col){
  /*
    @param: (size_t) row:
    @param: (size_t) col:
    @description: for retrieving and manipulating elements from the matrix
  */
  assert(row < WIDTH && col < WIDTH);
  return field[row][col];
}

std::ostream& operator<<(std::ostream& out, const Matrix src){
  /*
    @param: (std::ostream&) out:
    @param: (const Matrix) src:
    @description:
  */

  for(int r = 0; r < src.WIDTH; r++){
    out << "Machine " << r << " [";
    for(int c = 0; c < src.WIDTH; c++){
      out << "\t" << src.field[r][c] << "\t";
    }
    out << "]" << std::endl;
  }
  return out;
}
