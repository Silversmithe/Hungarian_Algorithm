/*
 *AUTHOR:       Alexander Adranly
 *
 *DESCRIPTION:  Definition of the Matrix abstract data type
 *              A matrix of integers
 */
 #include <iostream>
 #include <vector>

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix{
public:
  /* SIZE TYPE */
  /* CONSTRUCTOR */
  typedef unsigned int size_t;
  Matrix(size_t width); // square matrix
  /* DESCTRUCTOR */
  ~Matrix();
  /* COPY CONSTRUCTOR */
  Matrix(const Matrix& src);

  /* ACCESSORS */
  int getMinOfRow(size_t row);
  int getMinOfCol(size_t col);

  /* MUTATORS */
  void clear();
  void randomize(int limit);

  /* DISPLAY */
  void hungarianState(int row_reduce[], int col_reduce[]);

  /* OPERATORS */
  // for retrieving an element for the matrix
  int& operator()(size_t row, size_t col);
  friend std::ostream& operator<<(std::ostream& out, const Matrix src);



private:
  /* A two-dimensional matrix that holds all values */
  int ** field;
  /* MATRIX INFORMATION */
  size_t WIDTH;
  /* REDUCTION INFORMATION */
};

#endif
