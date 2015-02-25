//Nathan Kowaleski
//Lab 5 Part 1
//Sudoku puzzle
//game.cpp file
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

int v;
int x;
int y;//row
int z=0;//check
Puzzle<int> p("sudoku.txt",9);
p.print();

while(z==0)
{

cout << "Please enter the column you would like to change. (All values should be 1-9)" << endl;
cin >> y;
cout << "Please enter the row you would like to change. (All values should be 1-9)" << endl;
cin >> x;
cout << "Please enter the number you would like to insert or enter 0 to quit" << endl;
cin >> v;
x--;
y--;
if(v==0)//quit program early
{

break;

}

if(p.check(x,y,v)==0||x>8||y>8||v>9||x<0||y<0||v<0)//check to see if valid entry
{

cout << "this is not a valid submission" << endl;
p.print();

}

else
{

p.set(x,y,v);
p.print();

}

z=p.isComplete();

}//end while

p.print();
cout << "Done" << endl;

}// end program
