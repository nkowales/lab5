//Nathan Kowaleski
//Lab 5 Part 1
//Sudoku puzzle
//main.cpp file
// 02-24-15

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Puzzle.h"
using namespace std;
using namespace std;

int main()
{

Puzzle<int> p("sudoku.txt",9);
p.print();


}
