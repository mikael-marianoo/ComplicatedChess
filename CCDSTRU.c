#include <stdio.h>
#include <stdbool.h>

typedef int Coordinates[2];
typedef Coordinates Player[5];
typedef Coordinates Field5[5];
typedef Coordinates Field18[18];

void howToPlay() {
	
	printf("\n========================================\n");
	printf("\n%27s\n", "CCDSTRU Project"); //prints center at 20 spaces
	printf("%27s\n", "~ How to Play ~"); //prints center at 20 spaces
	printf("\n----------------------------------------\n");
	
	printf("\n%s\n%s\n%s\n%s\n\n%s\n%s\n\n[1] %s\n\n[2] %s\n%s\n\n%s\n%s\n\n%s\n",
	
		"The CCDSTRU Machine Project ", 
		"specifications describe a board game ", 
		"that is played by two people (Alpha ", 
		"and Beta) each with 5 pieces.", 
    
		"The map consists of 7 rows and 5 columns ", 
		"wherein the goal is to either: ", 
    
		"eat all of the opponent's pieces or", 
		"capture the initial positions of ", 
		"the opponent", 
    
		"The first player to do at least one of ", 
		"these conditions wins.", 
    
		"Have Fun!"
		
	);
	
	printf("\n========================================\n\n");
	
}//howToPlay function

void invalidInput(int minVal, int maxVal) {

  printf("\nInvalid Input. Only enter values from %d - %d\n", minVal, maxVal);
  
}//invalidInput

void invalidMove() {

  printf("\nInvalid Move \n");
  
}//invalidMove

void movementPrompt() {

  printf("Which piece do you want to move?\n");
  
}//movementPrompt

void nextMovementPrompt(Coordinates prev) {

  printf("\nWhere do you want to move (%d, %d)?\n", prev[0], prev[1]);
  
}//nextMovementPrompt

void enterRowText() {

  printf("Input row #: ");
  
}//enterXText

void enterColText() {

  printf("Input column #: ");
  
}//enterYText

void playerTurn(bool aTurn) {

  if (aTurn == true) {
    printf("\n****************************************\n");
    printf("\n%26s\n", "Alpha's Turn");//prints center at 20 spaces
    printf("\n****************************************\n\n");
    
  } else {
    printf("\n****************************************\n");
    printf("\n%25s\n", "Beta's Turn");//prints center at 20 spaces
    printf("\n****************************************\n\n");
  }
  
}//playerTurn

void winnerText(int num) {

  if (num == 1) {
    printf("%s", "          --------------------");
    printf("\n%s", "          |                  |");
    printf("\n%s%15s%s", "          |", "Alpha Wins!", "   |");
    printf("\n%s", "          |                  |");
    printf("\n%s\n\n", "          --------------------");
  } else if (num == 2) {
    printf("%s", "          --------------------");
    printf("\n%s", "          |                  |");
    printf("\n%s%14s%s", "          |", "Beta Wins!", "    |");
    printf("\n%s", "          |                  |");
    printf("\n%s\n\n", "          --------------------");
  }
  
}//winnerText

void legends(char alphaPiece, char betaPiece) {

  printf("  %c%s\n", alphaPiece, " - Alpha Pieces");
  printf("  %c%s\n", betaPiece, " - Beta Pieces");
  printf("  %s\n", "[ ] - Flags");
  printf("  %s\n", "( ) & [ ] - Danger Spaces");

  printf("\n");
  
}//legends

int inputChecker(int input, int minVal, int maxVal) {
	
	if (input >= minVal && input <= maxVal) {
		return 1;//input is within range
	}
	
	return 0;//input is outside range
	
}//inputChecker

void pieceMover(Coordinates prev, Coordinates next, Player player, int playerNum) {

  int i;

  //replaces value of prev piece with next
  for (i = 0; i < playerNum; i++) {
    if (player[i][0] == prev[0] && player[i][1] == prev[1]) {
      player[i][0] = next[0];
      player[i][1] = next[1];
    }
  }//for
  
}//pieceMover

void pieceRemover(Coordinates next, Player enemy, int* enemyNum) {

  int i, index;

  for (i = 0; i < *enemyNum; i++) {
    if (next[0] == enemy[i][0] && next[1] == enemy[i][1]) {
      index = i;//stores index of piece equal to next
    }//if 
  }//for 

  //replaces coordinate that equal next with coordinates to its right
  for (i = index + 1; i < *enemyNum + 1; i++) {
    enemy[index][0] = enemy[i][0];
    enemy[index][1] = enemy[i][1];

    index++;//incerments with i
  }//for
  
  *enemyNum -= 1;//minus one piece
}//pieceRemover

int oppPieceChecker(Coordinates next, Player enemy, int enemyNum) {

  int i;
  int counter = 0;

  //count++ if next is a member of enemy
  for (i = 0; i < enemyNum; i++) {
    if (next[0] == enemy[i][0] && next[1] == enemy[i][1]) {
      counter++;
    }
  }

  //return 1 if true
  //return 0 if false
  return counter;
  
}//oppPieceChecker

int dangerSpaceChecker(Coordinates next, Field18 dangerSpace, int dangerSpaceNum) {

  int i;
  int counter = 0;

  //count++ if next is a member of dangerSpace
  for (i = 0; i < dangerSpaceNum; i++) {
    if (next[0] == dangerSpace[i][0] && next[1] == dangerSpace[i][1]) {
      counter++;
    }
  }
  
  //return 1 if true
  //return 0 if false
  return counter;
  
}//oppPieceChecker

void alphaInputPrevCoordinates(Player player, Player enemy, Field18 dangerSpace, int dangerSpaceNum, int enemyNum, int playerNum, Coordinates prev, int row, int col) {

  int i;
  Coordinates tempStraight;
  Coordinates tempDiagLeft;
  Coordinates tempDiagRight;
  int selfPieceChecker = 0;//if input is player's piece
  int canMoveChecker = 0;//checks if the piece can move

  //loop if input not equal to any piece or if piece can move
  while (selfPieceChecker == 0 || canMoveChecker == 0) {
    
    movementPrompt();
    enterRowText();
    scanf("%d", &prev[0]);
  
    //input checker
    while (inputChecker(prev[0], 1, row) == 0) {
      invalidInput(1, row);//prints invalid input
      
      enterRowText();
      scanf("%d", &prev[0]);
    }//while
  
    //user enters y coordinate
    enterColText();
    scanf("%d", &prev[1]);
  
    //input checker
    while (inputChecker(prev[1], 1, col) == 0) {
      invalidInput(1, col);//prints invalid input
      
      enterColText();
      scanf("%d", &prev[1]);
    }//while
  
    //iterates through player pieces and checks if prev is one of the pieces
    for (i = 0; i < playerNum; i++) {
      if (prev[0] == player[i][0] && prev[1] == player[i][1]) {
        selfPieceChecker = 1;
      }//if
    }//for

    //initialize temp variables
    tempStraight[0] = prev[0] - 1;
    tempStraight[1] = prev[1];
    
    tempDiagLeft[0] = prev[0] - 1;
    tempDiagLeft[1] = prev[1] - 1;
    
    tempDiagRight[0] = prev[0] - 1;
    tempDiagRight[1] = prev[1] + 1;

    //checks if the piece can move
    if (prev[1] == 1) {//if piece is far left
      
      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagRight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagRight, dangerSpace, dangerSpaceNum)) {//if diag right space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagRight, enemy, enemyNum) == 0) {//if no enemy on straight and diag right
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagRight, player, playerNum) == 0 //diag right space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else
      
    } else if (prev[1] == 5) {//if piece is far right

      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagLeft, dangerSpace, dangerSpaceNum)) {//if diag left space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 0) {//if no enemy on straight and diag left
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagLeft, player, playerNum) == 0 //diag left space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else

    } else {

      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagLeft, dangerSpace, dangerSpaceNum)) {//if diag left space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagRight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagRight, dangerSpace, dangerSpaceNum)) {//if diag right space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagRight, enemy, enemyNum) == 0) {//if no enemy on straight AND diag left AND diag right
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagLeft, player, playerNum) == 0 || //diag left space does not have a player piece OR
            oppPieceChecker(tempDiagRight, player, playerNum) == 0 //diag right space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else
      
    }//if else
    

    if (selfPieceChecker == 0) {
      printf("\nYou don't own a piece at (%d, %d)\n\n", prev[0], prev[1]);
    } else if (canMoveChecker == 0) {
      printf("\n(%d, %d) cannot move\n\n", prev[0], prev[1]);
    }
    
  }//while  
  
}//alphaInputPrevCoordinates

void betaInputPrevCoordinates(Player player, Player enemy, Field18 dangerSpace, int dangerSpaceNum, int enemyNum, int playerNum, Coordinates prev, int row, int col) {

  int i;
  Coordinates tempStraight;
  Coordinates tempDiagLeft;
  Coordinates tempDiagRight;
  int selfPieceChecker = 0;//if input is player's piece
  int canMoveChecker = 0;//checks if the piece can move

  //loop if input not equal to any piece or if piece can move
  while (selfPieceChecker == 0 || canMoveChecker == 0) {
    
    movementPrompt();
    enterRowText();
    scanf("%d", &prev[0]);
  
    //input checker
    while (inputChecker(prev[0], 1, row) == 0) {
      invalidInput(1, row);//prints invalid input
      
      enterRowText();
      scanf("%d", &prev[0]);
    }//while
  
    //user enters y coordinate
    enterColText();
    scanf("%d", &prev[1]);
  
    //input checker
    while (inputChecker(prev[1], 1, col) == 0) {
      invalidInput(1, col);//prints invalid input
      
      enterColText();
      scanf("%d", &prev[1]);
    }//while
  
    //iterates through player pieces and checks if prev is one of the pieces
    for (i = 0; i < playerNum; i++) {
      if (prev[0] == player[i][0] && prev[1] == player[i][1]) {
        selfPieceChecker = 1;
      }//if
    }//for

    //initialize temp variables
    tempStraight[0] = prev[0] + 1;
    tempStraight[1] = prev[1];
    
    tempDiagLeft[0] = prev[0] + 1;
    tempDiagLeft[1] = prev[1] - 1;
    
    tempDiagRight[0] = prev[0] + 1;
    tempDiagRight[1] = prev[1] + 1;

    //checks if the piece can move
    if (prev[1] == 1) {//if piece is far left
      
      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagRight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagRight, dangerSpace, dangerSpaceNum)) {//if diag right space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagRight, enemy, enemyNum) == 0) {//if no enemy on straight and diag right
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagRight, player, playerNum) == 0 //diag right space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else
      
    } else if (prev[1] == 5) {//if piece is far right

      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagLeft, dangerSpace, dangerSpaceNum)) {//if diag left space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 0) {//if no enemy on straight and diag left
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagLeft, player, playerNum) == 0 //diag left space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else

    } else {

      if (oppPieceChecker(tempStraight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempStraight, dangerSpace, dangerSpaceNum)) {//if straight space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagLeft, dangerSpace, dangerSpaceNum)) {//if diag left space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempDiagRight, enemy, enemyNum) == 1 && dangerSpaceChecker(tempDiagRight, dangerSpace, dangerSpaceNum)) {//if diag right space has enemy piece AND is in danger space 
        canMoveChecker = 1;
      } else if (oppPieceChecker(tempStraight, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagLeft, enemy, enemyNum) == 0 && oppPieceChecker(tempDiagRight, enemy, enemyNum) == 0) {//if no enemy on straight AND diag left AND diag right
        if (oppPieceChecker(tempStraight, player, playerNum) == 0 || //straight space does not have a player piece OR
            oppPieceChecker(tempDiagLeft, player, playerNum) == 0 || //diag left space does not have a player piece OR
            oppPieceChecker(tempDiagRight, player, playerNum) == 0 //diag right space does not have a player piece
          ) {
          canMoveChecker = 1;
        }//if
      }//if else
      
    }//if else
    

    if (selfPieceChecker == 0) {
      printf("\nYou don't own a piece at (%d, %d)\n\n", prev[0], prev[1]);
    } else if (canMoveChecker == 0) {
      printf("\n(%d, %d) cannot move\n\n", prev[0], prev[1]);
    }
    
  }//while  
  
}//betaInputPrevCoordinates

void betaInputNextCoordinates(Coordinates prev, Coordinates next, Player enemy, Player beta, Field18 dangerSpace, int row, int col, int enemyNum, int betaNum, int dangerSpaceNum) {

  nextMovementPrompt(prev);
  enterRowText();
  scanf("%d", &next[0]);

  //input checker
  while (inputChecker(next[0], 1, row) == 0 || next[0] != prev[0] + 1) {
    invalidMove();
    
    enterRowText();
    scanf("%d", &next[0]);
  }//while

  //user enters y coordinate
  enterColText();
  scanf("%d", &next[1]);

  //input checker
  while (inputChecker(next[1], 1, col) == 0 || //if input is not between 1 - col
        //if not moving straight, diagonal left of right
        (next[1] != prev[1] && next[1] != prev[1] + 1 && next[1] != prev[1] - 1) || 
        // if attempting eating but not in danger space
        (oppPieceChecker(next, enemy, enemyNum) == 1 && dangerSpaceChecker(next, dangerSpace, dangerSpaceNum) == 0) || 
        //if next is already occupied by beta piece
        (oppPieceChecker(next, beta, betaNum) == 1)
    ) {
    invalidMove();
    
    enterColText();
    scanf("%d", &next[1]);
  }//while
  
}//betaInputNextCoordinates

void alphaInputNextCoordinates(Coordinates prev, Coordinates next, Player enemy, Player alpha, Field18 dangerSpace, int row, int col, int enemyNum, int alphaNum, int dangerSpaceNum) {

  nextMovementPrompt(prev);
  enterRowText();
  scanf("%d", &next[0]);

  //input checker
  while (inputChecker(next[0], 1, row) == 0 || prev[0] != next[0] + 1) {
    invalidMove();
    
    enterRowText();
    scanf("%d", &next[0]);
  }//while

  //user enters col
  enterColText();
  scanf("%d", &next[1]);

  //input checker
  while (inputChecker(next[1], 1, col) == 0 || //if input is not between 1 - col
        //if not moving straight, diagonal left of right
        (next[1] != prev[1] && next[1] != prev[1] + 1 && next[1] != prev[1] - 1) ||
        // if attempting eating but not in danger space
        (oppPieceChecker(next, enemy, enemyNum) == 1 && dangerSpaceChecker(next, dangerSpace, dangerSpaceNum) == 0) ||
        //if next is already occupied by alpha piece
        (oppPieceChecker(next, alpha, alphaNum) == 1)
    ) {
    invalidMove();
    
    enterColText();
    scanf("%d", &next[1]);
  }//while
  
}//alphaInputNextCoordinates

int gamOver(bool over, int alphaNum, int betaNum, Player alpha, Player beta, Field5 alphaInitial, Field5 betaInitial) {

  int i, j;
  int alphaChecker = 0;
  int betaChecker = 0;

  //if alpha piece is in beta flags checker
  for (i = 0; i < alphaNum; i++) {
    for (j = 0; j < 5; j++) {
      if(alpha[i][0] == betaInitial[j][0] && alpha[i][1] == betaInitial[j][1]) {
        alphaChecker++;
      }
    }//for
  }//for

  //if beta piece is in alpha flags checker
  for (i = 0; i < betaNum; i++) {
    for (j = 0; j < 5; j++) {
      if(beta[i][0] == alphaInitial[j][0] && beta[i][1] == alphaInitial[j][1]) {
        betaChecker++;
      }
    }//for
  }//for
  
  if (betaNum == 0 || (alphaNum != 0 && alphaChecker == alphaNum)) {//if wala nang pieces si beta or no. of times alpha piece matches with betaInitial == no. of alpha pieces
    return 1;//alpha wins
  } else if (alphaNum == 0 || (betaNum != 0 && betaChecker == betaNum)) {//if wala nang pieces si alpha or no. of times beta piece matches with alphaInitial == no. of beta pieces
    return 2;//beta wins
  } else {
    return 0;//game is not over
  }
  
}//gamOver

void board(Player alpha, Player beta, Field18 dangerSpace, 
           Field5 alphaInitial, Field5 betaInitial,
           int alphaNum, int betaNum, int dangerSpaceNum, 
           int row, int col,
           char alphaPiece, char betaPiece) {

  int i, j, k, count;
  printf("\n       1   2   3   4   5 \n\n");
   printf("\n    +===+===+===+===+===+\n");
   printf("\n    +---+---+---+---+---+\n");
  //printf("          ┌───┬───┬───┬───┬───┐\n");

  for (i = 0; i < row; i++) {
    printf("%d   ", i + 1);
    
    for(j = 0; j < col; j++) {

      // Leftmost wall
      if (j == 0) {
        printf("|");
      }

      //determines whether to print <> or []
      count = 0;      
      
      for (k = 0; k < dangerSpaceNum; k++) {//iterates through dangerSpace
        if (
                (dangerSpace[k][0] == i + 1 && dangerSpace[k][1] == j + 1) &&
                  (
                    (alphaInitial[k - 13][0] == i + 1 && alphaInitial[k - 13][1] == j + 1) ||
                    (betaInitial[k][0] == i + 1 && betaInitial[k][1] == j + 1)
                  )
              ) { 
          // && ( () || () ) // is danger AND flag?
          printf("["); // print [
          count++;
        } else if (dangerSpace[k][0] == i + 1 && dangerSpace[k][1] == j + 1) { // just danger, not flag
          printf("(");
          count++;
        }
      } //for
      
      //prints " " if no flag is detected
      if (count == 0) {
        printf(" ");
      }

      //prints pieces; iterates through both players arrays 
      count = 0;
      for (k = 0; k < betaNum; k++) {//beta array iteration
        if (beta[k][0] == i + 1 && beta[k][1] == j + 1) {
          printf("%c", betaPiece);
          count++;
        } 
      }
      for (k = 0; k < alphaNum; k++) {//alpha array iteration
        if (alpha[k][0] == i + 1 && alpha[k][1] == j + 1) {
          printf("%c", alphaPiece);
          count++;
        } 
      }//for
      
      //prints space if no piece is detected
      if (count == 0) {
        printf(" ");
      }
      
      //determines whether to print <> or []
      count = 0;      
      
      for (k = 0; k < dangerSpaceNum; k++) {//iterates through dangerSpace
        if (
                (dangerSpace[k][0] == i + 1 && dangerSpace[k][1] == j + 1) &&
                  (
                    (alphaInitial[k - 13][0] == i + 1 && alphaInitial[k - 13][1] == j + 1) ||
                    (betaInitial[k][0] == i + 1 && betaInitial[k][1] == j + 1)
                  )
              ) { 
          // && ( () || () ) // is danger AND flag?
          printf("]"); // print [
          count++;
        } else if (dangerSpace[k][0] == i + 1 && dangerSpace[k][1] == j + 1) { // just danger, not flag
          printf(")");
          count++;
        }
      } //for
      
      //prints [] if no flag is detected
      if (count == 0) {
        printf(" ");
      }

      printf("|");
    }//for

    if (i == 6) {
       printf("\n\n    +===+===+===+===+===+\n");
      //printf("\n          └───┴───┴───┴───┴───┘\n");
      //            
    } else {
       printf("\n    +---+---+---+---+---+\n");
      //printf("\n          ├───┼───┼───┼───┼───┤\n");
      // https://en.wikipedia.org/wiki/Box-drawing_character
    }
   
  }//for

  printf("\n\n");

  printf("%32s\n\n", "------------------------");
  
}//board

int main() {
  
  //==================System Variables + Initialization==================
  //==================System Variables + Initialization==================
  
  bool over = false;
  bool aTurn = true;
  Player alpha = {
                  {6, 2}, {6, 4}, 
                  {7, 1}, {7, 3}, {7, 5}
                 };// Alpha player position
  Player beta = {
                  {1, 1}, {1, 3}, {1, 5},
                  {2, 2}, {2, 4}
                };// Beta player position
  
  Field5 alphaInitial = {
                          {6, 2}, {6, 4}, 
                          {7, 1}, {7, 3}, {7, 5}
                        }; // Starting coordinates or initial positions of Alpha
  Field5 betaInitial = {
                        {1, 1}, {1, 3}, {1, 5},
                        {2, 2}, {2, 4}
                       }; // Starting coordinates or initial positions of Alpha
  Field18 dangerSpace = {
                          {1, 1}, {1, 3}, {1, 5},
                          {2, 2}, {2, 4},
                          {3, 1}, {3, 3}, {3, 5},
                          {4, 2}, {4, 4},
                          {5, 1}, {5, 3}, {5, 5},
                          {6, 2}, {6, 4}, 
                          {7, 1}, {7, 3}, {7, 5}
                        };
  //**********
  Coordinates prev;
  Coordinates next;
  int dangerSpaceNum = 18;
  int row = 7;
  int col = 5;
  
  int alphaNum = 5;
  int betaNum = 5;
  
  char betaPiece = '*';
  char alphaPiece = '@';
  
  //==================System Variables + Initialization==================
  //==================System Variables + Initialization==================

  //instructions
  howToPlay();

  //testing gameOver function
  //printf("%d", gamOver(over, alphaNum, betaNum, alpha, beta, alphaInitial, betaInitial));

  while(gamOver(over, alphaNum, betaNum, alpha, beta, alphaInitial, betaInitial) == 0) {
    
    //board ui
    board(alpha, beta, dangerSpace, alphaInitial, betaInitial, alphaNum, betaNum, dangerSpaceNum, row, col, alphaPiece, betaPiece);
    legends(alphaPiece, betaPiece);
    playerTurn(aTurn);
  
    //user enters x coordinate of prev
    if(aTurn == true) {//alpha turn
      alphaInputPrevCoordinates(alpha, beta, dangerSpace, dangerSpaceNum, betaNum, alphaNum, prev, row, col);//input prev
      alphaInputNextCoordinates(prev, next, beta, alpha, dangerSpace, row, col, betaNum, alphaNum, dangerSpaceNum);//input next

      //eating pieces
      if (oppPieceChecker(next, beta, betaNum) == 1) {//checks if next is opponent piece
        pieceRemover(next, beta, &betaNum);//removes piece eaten
      }//if
      
      pieceMover(prev, next, alpha, alphaNum);//moves piece
    } else {//beta turn
      betaInputPrevCoordinates(beta, alpha, dangerSpace, dangerSpaceNum, alphaNum, betaNum, prev, row, col);//input prev
      betaInputNextCoordinates(prev, next, alpha, beta, dangerSpace, row, col, alphaNum, betaNum, dangerSpaceNum);//input next

      //eating pieces
      if (oppPieceChecker(next, alpha, alphaNum) == 1) {//checks if next is opponent piece
        pieceRemover(next, alpha, &alphaNum);//removes piece eaten
      }//if
      
      pieceMover(prev, next, beta, betaNum);//moves piece
    }//if else

    //allows for alternate turns
    aTurn = !aTurn;

  }//while

  //board ui
  board(alpha, beta, dangerSpace, alphaInitial, betaInitial, alphaNum, betaNum, dangerSpaceNum, row, col, alphaPiece, betaPiece);

  //congratulatory text to winner
  winnerText(gamOver(over, alphaNum, betaNum, alpha, beta, alphaInitial, betaInitial));
  
  return 0;
}//main