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

 #define WIDTH 5
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

 /* HUNGARIAN ALGORITHM STEPS */

 /* STEP 1 (Subtract Row Minima):
    For each row, find the lowest element and subtract it from each element
    in that row.*/
  void subtractRowMinima(){
    /* */
  }


 /* STEP 2 (Subtract Column Minima):
    Similarly, for each column, find the lowest element and subtract it from
    each element in that column. */
  void subtractColMinima(){
    /* */
  }


/*  STEP 3 (Cover all zeros with a minimum number of lines):
    Cover all zeros in the resulting matrix using a minimum number of horizontal
    and vertical lines. If n lines are required, an optimal assignment exists
    among the zeros. The algorithm stops.
    If less than n lines are required, continue with Step 4. */
  void coverZeroes(){
    /* */
  }

/* STEP 3.5 Check if the cover is assignable or not */
  void isAssignable(){
    /* */
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

   // REDUCTION SETUP
   // FIRST: ROW, SECOND: COLUMN
   pair<int*, int*> reduction (int[WIDTH], int[WIDTH]);

   // COVERING SETUP
   // FIRST: ROW, SECOND: COLUMN
   pair<int*, int*> cover (int[WIDTH], int[WIDTH]);

   // STATE SETUP
   STATE state = SUB_ROW; // initialize the state to step 1

   /* INTRODUCTION */
   cout << setfill('-') << setw(80) << "-" << endl;
   cout << "Hungarian Algorithm (C++)" << endl;
   cout << setfill('-') << setw(80) << "-" << endl;

   /* HUNGARIAN ALGORITHM FSM */
   while(!(state == COMPLETE)){

     switch(state){
       case(SUB_ROW):
        printf("\nstate: subtract row minima\n");
        state = SUB_COL;
        break;

       case(SUB_COL):
        printf("\nstate: subtract column minima\n");
        state = COVER_ZEROES;
        break;

       case(COVER_ZEROES):
        printf("\nstate: minimum zero covering\n");
        state = CREATE_ZEROES;
        break;

       case(CREATE_ZEROES):
        printf("\nstate: create zeroes\n");
        state = ASSIGN;
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
   cout << solution << endl;

   return 0;
 }
