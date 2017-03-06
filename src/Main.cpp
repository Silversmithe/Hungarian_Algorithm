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

 enum COVER{
   UNCOVERED,
   COVERED
 };

 /* HUNGARIAN ALGORITHM STEPS */

 /* STEP 1 (Subtract Row Minima):
    For each row, find the lowest element and subtract it from each element
    in that row.*/
  void subtractRowMinima(Matrix* matrix, pair<int*, int*>* reduction){
    /*
      @param: (Matrix *) matrix:
      @param: (pair<int*, int*>*) reduction:
      @description:
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


 /* STEP 2 (Subtract Column Minima):
    Similarly, for each column, find the lowest element and subtract it from
    each element in that column. */
  void subtractColMinima(Matrix* matrix, pair<int*, int*>* reduction){
    /*
      @param: (Matrix *) matrix:
      @param: (pair<int*, int*>*) reduction:
      @description:
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


/*  STEP 3 (Cover all zeros with a minimum number of lines):
    Cover all zeros in the resulting matrix using a minimum number of horizontal
    and vertical lines. If n lines are required, an optimal assignment exists
    among the zeros. The algorithm stops.
    If less than n lines are required, continue with Step 4. */
  void coverZeroes(Matrix matrix, pair<int*, int*>* cover){
    /*
      @param: (Matrix) matrix:
      @param: (pair<int*, int*>*) cover:
      @description:
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

/* STEP 3.5 Check if the cover is assignable or not */
  bool isAssignable(pair<int*, int*> cover){
    /* */
    int sum=0;
    for(int i = 0; i < WIDTH; i++)
      sum += cover.first[i] + cover.second[i];

    return sum >= WIDTH;
  }

/*  STEP 4 (Create additional zeros):
    Find the smallest element (call it k) that is not covered by a line in
    Step 3. Subtract k from all uncovered elements, and add k to all elements
    that are covered twice. */
void createZeroes(){
  /* */
}

/* FINAL STEPS */
/* ASSIGNMENT */
void assignTasks(){
  /* */

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

   // STATE SETUP
   STATE state = SUB_ROW; // initialize the state to step 1

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
        bool assignable = isAssignable(cover);
        printf("Is this cover Assignable?: %d\n", assignable);
        if(assignable)
          state = ASSIGN;
        else
          state = CREATE_ZEROES;
        break;

       case(CREATE_ZEROES):
        printf("\nstate: create zeroes\n");
        
        state = COVER_ZEROES;
        break;

       case(ASSIGN):
        printf("\nstate: assignment\n");
        state = COMPLETE;
        break;
       default:
        printf("\nerror: unknown state\n");
     }
   }

   /* PRESENTATION OF SOLUTION */
   printf("\n");
   solution.hungarianState(reduction);

   return 0;
 }
