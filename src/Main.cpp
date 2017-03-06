/*
 *AUTHOR:       Alexander Adranly
 *
 *DESCRIPTION:  Implementation of the Hungarian Algorithm
 *              Reference:
 *              http://www.hungarianalgorithm.com/hungarianalgorithm.php
 */
 #include <algorithm>
 #include <iostream>
 #include <iomanip>
 #include <stack>
 #include <vector>
 #include "Matrix.hpp"

 #define WIDTH 4
 #define LIMIT 10

 using namespace std;

 /* HUNGARIAN ALGORITHM STATES */
 enum STATE{
  SUB_ROW,
  SUB_COL,
  COVER_ZEROES,
  CREATE_ZEROES,
  ASSIGN,
  COMPLETE
 };

/* DEFINING MATRIX COVER */
 enum COVER{
   UNCOVERED,
   COVERED
 };

/* HUNGARIAN ALGORITHM STEPS */
void subtractRowMinima(Matrix* matrix, pair<int*, int*>* reduction){
    /*
      @param: (Matrix *) matrix:
      @param: (pair<int*, int*>*) reduction:
      @description:

      STEP 1 (Subtract Row Minima):
         For each row, find the lowest element and subtract it from each element
         in that row.
    */
    int smallest_in_row;
    for(int r = 0; r < WIDTH; r++){
      smallest_in_row = (*matrix).getMinOfRow(r);
      (*reduction).first[r] = smallest_in_row;

      for(int c = 0; c < WIDTH; c++){
        (*matrix)(r,c) -= smallest_in_row;
      }
    }
  }

void subtractColMinima(Matrix* matrix, pair<int*, int*>* reduction){
    /*
      @param: (Matrix *) matrix:
      @param: (pair<int*, int*>*) reduction:
      @description:

      STEP 2 (Subtract Column Minima):
         Similarly, for each column, find the lowest element and subtract it from
         each element in that column.
    */
    int smallest_in_col;
    for(int c = 0; c < WIDTH; c++){
      smallest_in_col = (*matrix).getMinOfCol(c);
      (*reduction).second[c] = smallest_in_col;

      for(int r = 0; r < WIDTH; r++){
        (*matrix)(r,c) -= smallest_in_col;
      }
    }
  }

void coverZeroes(Matrix matrix, pair<int*, int*>* cover){
    /*
      @param: (Matrix) matrix:
      @param: (pair<int*, int*>*) cover:
      @description:

      STEP 3 (Cover all zeros with a minimum number of lines):
          Cover all zeros in the resulting matrix using a minimum number of horizontal
          and vertical lines. If n lines are required, an optimal assignment exists
          among the zeros. The algorithm stops.
          If less than n lines are required, continue with Step 4.
    */
    int row_zero_count=0, col_zero_count=0;
    stack<int> row_zeroes;

    /* INITIALIZE COVERING */
    for(int i = 0; i < WIDTH; i++)
      (*cover).first[i] = (*cover).second[i] = UNCOVERED;

    for(int r = 0; r < WIDTH; r++){
      row_zero_count = 0;
      // count the zeroes in this row
      for(int c = 0; c < WIDTH; c++){
        // look for zeroes
        if(matrix(r,c) == 0){
          // if there is a zero, record its column index
          // count the zero
          row_zeroes.push(c);
          row_zero_count += 1;
        }
      }

      // backtrack to the zeroes in this row & count up the zeroes in these
      // columns, and make a decision on how to mark
      while(!row_zeroes.empty()){
        int index = row_zeroes.top();
        row_zeroes.pop();
        for(int row = 0; row < WIDTH; row++){
          if(matrix(row, index) == 0){
            col_zero_count += 1;
          }
        }
        // decide if the column has more zeroes or the row and mark the one with
        // more zeroes
        if(col_zero_count > row_zero_count){
          // mark the column
          if((*cover).first[r] != COVERED)
            (*cover).second[index] = COVERED;
        } else{
          // otherwise mark the row
          if((*cover).second[index] != COVERED)
            (*cover).first[r] = COVERED;
        }
        // reset the zero count
        col_zero_count = 0;
      }
    }

    /* PRESENT COVERING */
    printf("row col\n");
    for(int i = 0; i < WIDTH; i++)
      printf("[%d] [%d]\n", (*cover).first[i], (*cover).second[i]);

  }

bool isAssignable(pair<int*, int*> cover){
    /*
      @param: (pair<int*, int*>) cover:
      @description: STEP 3.5 Check if the cover is assignable or not
    */
    int sum=0;
    for(int i = 0; i < WIDTH; i++)
      sum += cover.first[i] + cover.second[i];

    return sum >= WIDTH;
  }

void createZeroes(Matrix* matrix, pair<int*, int*> cover){
  /*
    @param: (Matrix*) matrix:
    @param: (pair<int*, int*>) cover:
    @description:

    STEP 4 (Create additional zeros):
        Find the smallest element (call it k) that is not covered by a line in
        Step 3. Subtract k from all uncovered elements, and add k to all elements
        that are covered twice.
  */
  int min_val = LIMIT;
  // find the smallest element that is not covered
  for(int r = 0; r < WIDTH; r++)
    if(cover.first[r] == UNCOVERED)
      for(int c = 0; c < WIDTH; c++)
        if(cover.second[c] == UNCOVERED)
          min_val = min(min_val, (*matrix)(r,c));

  printf("Smallest uncovered element: %d\n", min_val);
  // subtract from all uncovered elements
  // add it to all doubly covered elements
  // do nothing to singly covered elements
  for(int r = 0; r < WIDTH; r++){
    for(int c = 0; c < WIDTH; c++){
      if(cover.first[r] == COVERED && cover.second[c] == COVERED)
        (*matrix)(r,c) += min_val;
      else if(cover.first[r] == UNCOVERED && cover.second[c] == UNCOVERED)
        (*matrix)(r,c) -= min_val;
      // else do nothing
    }
  }

}

/* FINAL STEPS */
/* ASSIGNMENT */
void assignTasks(Matrix* solution, Matrix* problem, vector<int>* assignment){
  /* */
  vector<vector<int> > zeroes;
  for(int i = 0; i < WIDTH; i++)
    zeroes.push_back(vector<int>());

  // get all the zeroes first
  for(int r = 0; r < WIDTH; r++){
    for(int c = 0; c < WIDTH; c++){
      if((*solution)(r,c) == 0)
        zeroes[r].push_back(c);
    }
  }

  // display zeroes
  for(int r = 0; r < zeroes.size(); r++){
    printf("r: %d, c: ", r);
    for(int c = 0; c < zeroes[r].size(); c++){
      printf(" %d ", zeroes[r][c]);
    }
    printf("\n");
  }

  // actually do the assignment now

  // if a row only has one zero, you gotta take it
  for(int r = 0; r < zeroes.size(); r++){
    if(zeroes[r].size() == 1)
      (*assignment)[r] = zeroes[r][0];
  }
  // if you have a number that no one else has, you got to take it
  for(int r = 0; r < zeroes.size(); r++){
    // skip the ones that have been already been assigned at this point
    if((*assignment)[r] != -1) continue;
    for(int c = 0; c < zeroes[r].size(); c++){

      int value = zeroes[r][c];

      // see if there is any other value like this one
      for(int row = 0; row < zeroes.size(); row++){
        for(int col = 0; col < zeroes[row].size(); col++){
          
        }
      }

    }
  }

  // display assignment
  printf("[");
  for(int i = 0; i < (*assignment).size(); i++)
    printf(" %d ", (*assignment)[i]);
  printf("]\n");

}

/* TOTAL COST */
void calculateTotalCost(){
  /* */

}

/* MAIN FUNCTION */
 int main(){
   /* INITIALIZATION */

   // MATRIX SETUP
   Matrix problem = Matrix(WIDTH);
   problem.randomize(LIMIT);
   Matrix solution = Matrix(problem);

   // ARRAYS FOR STORING COVER AND REDUCTION
   int row_cover[WIDTH], col_cover[WIDTH], row_reduce[WIDTH], col_reduce[WIDTH];
   for(int i = 0; i < WIDTH; i++)
     row_cover[i] = col_cover[i] = row_reduce[i] = col_reduce[i] = 0;

   // REDUCTION SETUP
   // FIRST: ROW, SECOND: COLUMN
   pair<int*, int*> reduction;
   reduction.first = row_reduce;
   reduction.second = col_reduce;

   // COVERING SETUP
   // FIRST: ROW, SECOND: COLUMN
   pair<int*, int*> cover;
   cover.first = row_cover;
   cover.second = col_cover;

   // ASSIGNMENT
   vector<int> assignment;
   for(int i = 0; i < WIDTH; i++) assignment.push_back(-1);

   // STATE SETUP
   STATE state = SUB_ROW; // initialize the state to step 1
   bool assignable = false; // for checking job assignability

   /* INTRODUCTION */
   cout << setfill('-') << setw(80) << "-" << endl;
   cout << "Hungarian Algorithm (C++)" << endl;
   cout << setfill('-') << setw(80) << "-" << endl;

   /* PRESENTATION OF PROBLEM */
   cout << endl << problem << endl;

   /* HUNGARIAN ALGORITHM FSM */
   while(!(state == COMPLETE)){

     switch(state){
       case(SUB_ROW):
        printf("\nstate: subtract row minima\n");
        subtractRowMinima(&solution, &reduction);
        state = SUB_COL;
        break;

       case(SUB_COL):
        printf("\nstate: subtract column minima\n");
        subtractColMinima(&solution, &reduction);
        state = COVER_ZEROES;
        break;

       case(COVER_ZEROES):
        printf("\nstate: minimum zero covering\n");
        coverZeroes(solution, &cover);
        assignable = isAssignable(cover);
        printf("Is this cover Assignable?: %d\n", assignable);

        if(assignable)
          state = ASSIGN;
        else
          state = CREATE_ZEROES;
        break;

       case(CREATE_ZEROES):
        printf("\nstate: create zeroes\n");
        createZeroes(&solution, cover);
        state = COVER_ZEROES;
        break;

       case(ASSIGN):
        printf("\nstate: assignment\n");
        assignTasks(&solution, &problem, &assignment);
        state = COMPLETE;
        break;
       default:
        printf("\nerror: unknown state\n");
     }
   }
   printf("\nstate: complete\n");

   /* PRESENTATION OF SOLUTION */
   printf("\n");
   solution.hungarianState(reduction);

   return 0;
 }
