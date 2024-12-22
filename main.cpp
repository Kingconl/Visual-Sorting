/*  Author: Connor Liu
    Program Description: A program that visually displays the insertion sort algorithm.
    Date Created: 5/3/2024
    Date Modified: 7/3/2024

    Replit Link: https://replit.com/join/kxrogwavbu-connorliu2
*/

// =================== Preprocessor Commands =========================
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h>
#include <termios.h>
#include <limits> 
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

//getch code I copied from VLE.
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
  return buf;
 }

// ===================  Function Prototypes  ==========================

int menu(string, string[], int);
void legend();
void displayArray(int[], int, int, int, int, int);
void randomArray(int [], int);
void insert(int [], int, int);
void insertionSort(int[], int, bool);
void legend(); 
void question(int[], int, int);
void arrayReset(int[], int[], int);

// ===================  Function Definitions  ==========================

int main() {
  srand(time(NULL));
  
  int userInput = 0;
 // int unsortedArray[10] = {0,0,0,0,0,0,0,0,0,-9};
  int unsortedArray[10] = {1,2,-1,6,0,9,3,-7,-3,1};
  int unsortedArrayValue[10] = {1,2,-1,6,0,9,3,-7,-3,1};
  int arrayLength = 10;
  string promt = "Insertion Sort Visual Display and Questionnaire";
  string promtOptions [6] = {"Legend", "Randomize", "Visual Display", "Questionnaire", "Array Reset", "Exit Program"};
  int numberOfPromtOptions = 6;


  do{userInput = menu(promt, promtOptions, numberOfPromtOptions);

    switch(userInput)
    {
      case 1:
        legend();
      break;
      
      case 2:
        randomArray(unsortedArray, arrayLength);
        arrayReset(unsortedArray, unsortedArrayValue, arrayLength);
      break;
      
      case 3:
        insertionSort(unsortedArray, arrayLength, false);
      break;
      
      case 4:
        insertionSort(unsortedArray, arrayLength, true);
      break;
      case 5:
      arrayReset(unsortedArrayValue, unsortedArray, arrayLength);//since after insertionSort or question the elements change, we need to rest them. 
      (void)system("clear");
        cout << "Array had been reset." << endl << "Press any key to continue" << endl;
      getch();
      case 6:
        (void)system("clear");
      cout << "Exiting program";
      break;
    }
  }while(userInput != numberOfPromtOptions);

  return 0;
}

//======================================================================

void insertionSort(int arrayToBeSorted[], int arraySize, bool questionStatus)
{
  int largestValue = arrayToBeSorted[0]; //largestValue and lowestValue are both set to the array at element 0 since that allows the program to skip a step and not have to calculate for arrayToBeSorted[0] in the for loop.
  int lowestValue = arrayToBeSorted[0];
  int shiftNumber = 0;

  for(int i = 1; i < arraySize; i++)//finds the lowest and larest values in the arrays. This is vital to build our array. It is more efficient to find it once in the insertionSort function then to constantly refind them in the displayArray function(the lowst and largest values never change)
    {
      if(arrayToBeSorted[i]<lowestValue)
      {
        lowestValue = arrayToBeSorted[i];
      }
      else if (arrayToBeSorted[i] > largestValue)
      {
        largestValue = arrayToBeSorted[i];
      }
    }


  for (int i = 1 ; i  < arraySize; i++)//This for loop will run until i reaches the last value. We do not have to check for 0 since array[0] has nothing to compare too and therefor will never move if you check it first in insertion sort.  
    {
      shiftNumber = i -1;//since the number we compare to i will be the one that precedes it. 
     displayArray(arrayToBeSorted, arraySize, i, shiftNumber, largestValue, lowestValue);
      
      if(questionStatus == true)//since the user will not always wanting to use the question function, the program will only use the question function if the bool variable,questionStatus, is true. 
      {
        question(arrayToBeSorted, i, shiftNumber);
      }
      else
      {
        cout << "Press any key to continue" << endl;
        getch();//since if we do not use the question function the program would rush past the display and instantly move onto the next display and on and on(the getch is build into the question function). To solve this, we use the function getch if the user does not choose to enable questions.  
      }
      
      while(shiftNumber >= 0 and (arrayToBeSorted[shiftNumber] > arrayToBeSorted[i])) //shiftNumber has to be >=0 since there is no values for any array with a negative element but we also need to check to see if our i is in the right position or not. We do this by comparing the array at element i and shiftNumber.    
        {
        shiftNumber--;//if both of the status are true, we have to check the value that precedes the shiftNumber to check if I is smaller than that too. 
          if (shiftNumber >=0)// Because our shiftNumber can drop to -1, we do not want to displat that so we only display if it so >= 0 . 
          {
            displayArray(arrayToBeSorted, arraySize, i, shiftNumber, largestValue, lowestValue);
            if(questionStatus == true)//After each display a question is asked for the next display. 
            {
              question(arrayToBeSorted, i, shiftNumber);
            }
            else 
            {
              cout << "Press any key to continue" << endl;
              getch();
          }
          }
        }
      if (shiftNumber != i-1)//only insert of the shiftNumer had change since if it has not then the array[i] is in the right position.
      { 
        insert(arrayToBeSorted, i, shiftNumber + 1);
      }
    }
    displayArray(arrayToBeSorted, arraySize, -1, -1, largestValue, lowestValue);//-1 since we are done the sorting algorithm and just want the results. Therefore we dont need the i or the shift value. At -1 no value will be green or red since j(in the displayArray function) will never be less than 0. 
  cout << "Sorting Done" << endl << "Press any key to continue" << endl;
  getch();
  return;
}

//======================================================================

void insert(int array[], int currentPosition, int desiredPosition)
{
  int holdingValue = array[currentPosition];//since array[currentPosition] will be lost in the forloop but we will still need it later on. 

  for (int i = currentPosition; i > desiredPosition; i--)
    {
      array[i] = array[i-1];//insertion sort so array[shiftNumber] will become array[i] and everything until element i will have to shift accordingly. 
    }

  array[desiredPosition] = holdingValue;
  return;
}

//======================================================================

int menu(string question, string option[], int numberOfOptions)
{
  int userReponse = 0;
  do {
    (void)system ("clear");

    cout << question << endl;

    for (int i = 0; i < numberOfOptions; i++ )
      {
         cout << i+1 <<"- " << option[i] << endl;//couts the options
      }
    
      cin >> userReponse;
    if(cin.fail())//sets any value that cant be stored as an int as 0. 
    {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (userReponse < 1 or userReponse > numberOfOptions)
      {cout << "Invalid answer. Try again" << endl << "Press any key to continue.";
                getch();
                (void)system ("clear");
      }
    } while (userReponse < 1 or userReponse > numberOfOptions);//if it does not fall within the parameters, loop again.
  return userReponse; 
}

//======================================================================

void displayArray(int arrayOfInts[], int arraySize, int currentValue, int comparedValue, int largestValue, int lowestValue)
{
  (void)system ("clear");
  
    //create the positive side of the visuals
    for(int i = 0; i <= (largestValue); i++)//<= because we need 1 more row for the value of the column(if there array[6] had the value of 3, it said 3 above it)
      {
      for(int j = 0; j < arraySize; j++)// To build it a horizontal row, we need to do repeat the for loop arraySize times(since arrays start at element 0).  
        {
          if (j == currentValue)//makes our key red
          {
            cout << RED;
          }
          else if (j == comparedValue)//makes our step red
          {

            cout << GREEN;
          }

          if(arrayOfInts[j] == largestValue-i)
          {
          cout << " " << arrayOfInts[j] << " ";
          }
          else if(arrayOfInts[j] > largestValue-i)//Since we added an extra column to the bottom, it will be cancled out by the fact that the square at the top will be replaced with the value of the column. 
            {
            cout << "██ ";//it will only cout the square if at array[x] > largestValue-i as this will make it so that it will create x-1 columns. This may seem bad but in reality it is the same as creating x columnns since the value of the column is already replacing what is in the top space and one extra row is being added to compensate, everything works flawlessly.   
            } 
          else{
            cout << "   ";//if there should not be any squares, then we have to add empty space to not mess up the visuals. 
          }
          cout << RESET;//resets colours
        }
        cout << endl;
  }
//  creates the zero line as well as the element so that the questions are easier to visualize/write down. 
  for(int k = 0; k < arraySize; k++)
    {
      cout << k+1 << "--";
    }
    cout << "-0" << endl; //an extra "-" so it looks nicer

  //creates the negative portion of the visuals
  for(int i = 0; i >= lowestValue; i--)//<= because we need 1 more row for the value of the column
    {

    for(int j = 0; j < arraySize; j++)
      {
        if (j == currentValue)
          {
            cout << RED;
          }
          else if (j == comparedValue)
          {
            cout << GREEN;
          }

        if(arrayOfInts[j] == i  && arrayOfInts[j] < 0)//Since we added an extra column to the bottom, it will be cancled out by the fact that the square at the top will be replaced with the value of the column. 
        {
          cout << arrayOfInts[j] << " ";
        }
        else if(arrayOfInts[j] < i && arrayOfInts[j] < 0)
          {
          cout << "██ "; // same thing with the positive. Everything cancels each other out resulting in X columns being made(verticlty)
          }
        else{
          cout << "   ";
        }
        cout << RESET;
      }
      cout << endl;
      }

return;
    }

//======================================================================

void randomArray(int array[], int size)
{
  for(int i = 0; i < size; i++)
    {
      array[i] = rand()%19-9;// since a double diget number will break the value counter, i have set the random to only give values between -9, 9 inclusive
      
    }
  (void)system("clear");
  cout << "The new array is (";// Tells the user the values of the new array
  for (int i = 0; i <= (size-1); i++)
  {
    cout << array[i];
      if (i != size-1)
    {
     cout << ", ";
    }
  }
  cout << ")";

  cout << endl << "Press any key to continue";
  getch();
return;
}

//======================================================================

void legend()
{ //the legend. It tells the user what the highlights and numbers mean. 
  (void)system("clear");
  cout << "This is the legend. It is a guide on the visual noations used on the visual display of the insertion sorting algorithm." << endl << endl;
    
  cout << RED << "RED" << RESET << ": Red indicates the value being sorted. The algorith compares it to the 'Step'(Green highlight) to check if it is in the right position." << endl << endl;
  
  cout << GREEN << "GREEN" << RESET << ": GREEN indicates the value being compared with. The algorith compares it to the 'Key'(Red highlight) to check if the key is in the right position and if the key is not in the right position, where the key should be inserted into." << endl << endl;
  
  cout << "1--2--3--4--5--ect: This represents the position of the column within the array" << endl << endl; 
  
  cout << "--0: This represents the zero line. The line where the values above it are positive and the values below it are negative";
  cout << endl << endl << "Press any key to continue" << endl;
  getch();
  return;
}

//======================================================================

// used to test the user to see if they fully understand the Insertion sort algorithm. 
// note the i is the key and the shiftNumber is the step
void question(int arrayToBeSorted[], int i, int shiftNumber)
  {
    int userInput = 0;
    int answer = 0;
        if(arrayToBeSorted[shiftNumber] <= arrayToBeSorted[i] && arrayToBeSorted[shiftNumber+1] > arrayToBeSorted[i])// if the array[shiftNumber+1] > array[i] then that means that 
         {
        answer = 3;
         }
        else if(arrayToBeSorted[shiftNumber] <= arrayToBeSorted[i])//if the shiftNumber is less or equal to i then that means that i is in the right spot
        {
          answer = 1;
        }
        else if(shiftNumber -1 < 0)//the only time that when we insert our key in front of the step is if there is no value in front of the step. Another statment that needs to be true is arrayToBeSorted[shiftNumber] > arrayToBeSorted[i] but since the previous else if has arrayToBeSorted[shiftNumber] <= arrayToBeSorted[i], all values that pass to this else if will be arrayToBeSorted[shiftNumber] > arrayToBeSorted[i] so we do not need it. 
        {
          answer = 2;
        }
        else//the only other option is to look for a better spot to insert the key
        {
          answer = 4;
        }
    cout << "What shoule we do?" << endl;
    cout << "1- We should do nothing, our key(red) is in the right spot" << endl;
    cout << "2- We should insert the key(red) in front of our step(green)" << endl;
    cout << "3- We should insert the key(red) in behind of our step(green)" << endl;
    cout << "4- We should keep looking to see if this is the best spot to insert our key" << endl;
    cout << "5- Skip" << endl;
        do{
          cin >> userInput;
          if(cin.fail())
            {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
          if (userInput == 5)
          {
            cout << "The answer is " << answer << "." << endl << "press any key to continue.";
            getch();
          }
          else if (userInput != answer)
            {
              cout << RED << "Incorrect answer. Please Try Again." << RESET << endl;
             }
          else
            {
              cout << GREEN << "Correct Answer!"<< RESET << endl << "press any key to continue.";
               getch();
            }
          
          }while(userInput != answer && userInput != 5);
    return;
  }

//======================================================================

  void arrayReset(int arrayOne[], int arrayTwo[], int arraySize)
  {//resets the array after insertArray or question since the positions of the element change. 
    for(int i = 0; i < arraySize; i++)
      {
      arrayTwo[i] = arrayOne[i];
      }
    return;
  }