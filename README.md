# CPSC-335_ScheduleMatcher

My submission for CPSC 335 - Project 1: Schedule Matcher

# My Information

* Institution: California State University Fullerton (CSUF)
* Course: CPSC 335 - Algorithm Engineering (Fall 2023, Section 02, 13543)
* Name: Josue Han Yan Tai Liu
* Email: josue.tai@csu.fullerton.edu

# How to run the program

* The programming language used is C++.
* The executable file is already compiled to run from a Linux terminal.
* If needed, you can recompile again from a Linux terminal by using the command $g++ project1_starter.cpp -o ScheduleMatcher
* To run the executable file from a Linux terminal, use the command $./ScheduleMatcher
* Below is an example of a case input:

  * Case input:
  ```
  [['12:00':'13:00'],['16:00':'18:00']]
  
  ['9:00','19:00']
  
  [['9:00':'10:30'],['12:20':'14:30'],['14:30':'15:00'],['16:00':'17:00']]
  
  ['9:00','18:30']
  
  30

  ```
  * Expected output:
  ```
  [['10:30':'12:00'],['15:00':'16:00'],['18:00':'18:30']]
  ```

* Each case consists of 5 lines in the "input.txt" file.
* Each case should be separated by a new line.
* The time format and interval format should follow the same pattern as in the example.
* The input schedule should already be sorted.
* The program only works for schedules within the same day.
* Outputs will be stored in the "output.txt" file.
* An "input.txt" file is provided with 10 cases as an example, and the generated "output.txt" respectively.
