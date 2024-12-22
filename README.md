This program provides a visual representation of the Insertion Sort algorithm and includes an interactive questionnaire to test user understanding of the sorting process.

Features
Visual Display: A clear graphical representation of the array as it undergoes the insertion sort algorithm.
Legend: A guide to the visual notation used in the display.
Random Array Generation: Option to generate a new random array for sorting.
Interactive Questionnaire: Test your knowledge of the insertion sort algorithm at each step.
Array Reset: Reset the array to its initial state after sorting or testing.
Menu Navigation: User-friendly menu to choose actions.
How to Use
Compile and Run: Use a C++ compiler to build and run the program.
Menu Options:
Legend: Learn the meaning of colors and numbers in the visual display.
Randomize: Generate a new random array for sorting.
Visual Display: Observe the step-by-step process of the insertion sort algorithm.
Questionnaire: Answer questions about the sorting process to test your understanding.
Array Reset: Reset the array to its original state.
Exit Program: Exit the application.
Visual Representation
RED: Indicates the key being sorted.
GREEN: Highlights the step being compared to the key.
Array Values: Displayed as columns with positive values above the zero line and negative values below.
Column Numbers: Indicate the positions in the array for easy reference.
Questionnaire
The interactive questionnaire asks you to determine the next step in the sorting process based on the visual display. Immediate feedback is provided for your responses.

Technical Details
Language: C++
Libraries Used:
<iostream>: For input and output.
<stdlib.h>: For system commands like clearing the console.
<time.h>: For random seed initialization.
<limits>: For input validation.
<termios.h>: To handle unbuffered input (getch implementation).
Example Walkthrough
Start the program and view the menu.
Select Visual Display to see how the array elements are sorted step-by-step.
Enable the Questionnaire to test your understanding.
Use Array Reset to return to the original array or generate a new one using Randomize.
Notes
Ensure your terminal supports ANSI escape codes for color output.
The random array generation is limited to integers between -9 and 9 for consistent column widths.
