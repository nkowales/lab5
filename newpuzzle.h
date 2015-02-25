//Nathan Kowaleski
//Lab 6 Part 1
//Sudoku puzzle Solver
//Puzzle class .h file

#ifndef PUZZLE_H
#define PUZZLE_H
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template < typename T > class Puzzle
{

public:

  Puzzle (string, int);
  void print ();
  int check (int, int, T);
  void set (int, int, T);
  int isComplete ();
  void solve ();
  void reset ();
  int hiddensingle (int, int);
private:

  int size;
  vector < vector < T > >puz;
  vector < vector < vector < T > > >notsolved;

};

template < typename T > Puzzle < T >::Puzzle (string s, int n)
{
  size = n;
  ifstream f;
  f.open (s.c_str ());
  T x;				//int reading to from file
  int i;			//for loop counter
  int j;			//for loop counter
  int k;			//for loop counter
  for (i = 0; i < size; i++)
    {
      puz.push_back (vector < T > ());	//fill one vector with vectors
      for (j = 0; j < size; j++)
	{
	  f >> x;
	  puz[i].push_back (x);	//fill in the vectors with values from file
	}
    }
  f.close ();

//set possible entries
  for (i = 0; i < size; i++)
    {
      notsolved.push_back (vector < vector < T > >());
      for (j = 0; j < size; j++)
	{
	  notsolved[i].push_back (vector < T > ());
	  if (puz[i][j] != 0)
	    {
	      notsolved[i][j].push_back (puz[i][j]);
	    }
	  else
	    {
	      for (k = 1; k <= size; k++)
		{
		  if (check (i, j, k))
		    {
		      notsolved[i][j].push_back (k);
		    }
		}
	    }
	}
    }

}

//reset the possible entries
template < typename T > void Puzzle < T >::reset ()
{
  int i;
  int j;
  int k;
  for (i = 0; i < size; i++)
    {
      for (j = 0; j < size; j++)
	{
	  notsolved[i][j].clear ();
	  if (puz[i][j] != 0)
	    {
	      notsolved[i][j].push_back (puz[i][j]);
	    }
	  else
	    {
	      for (k = 1; k <= size; k++)
		{
		  if (check (i, j, k))
		    {
		      notsolved[i][j].push_back (k);
		    }
		}
	    }
	}
    }
}

//print function
template < typename T > void Puzzle < T >::print ()
{
  cout << endl;
  typename vector < vector < T > >::iterator row;
  typename vector < T >::iterator col;
  for (row = puz.begin (); row != puz.end (); row++)
    {
      for (col = row->begin (); col != row->end (); col++)
	{
	  cout << *col << " ";	//for all positions print out the value and a space
	}
      cout << endl;
    }
  cout << endl;
}

//check to make sure placement is valid
template < typename T > int Puzzle < T >::check (int x, int y, T t)
{
  int xstart;			//place in sector
  int ystart;			//place in sector
  int z;			//for checking in row and column
  int i;			//for loop variable
  int j;			//for loop variable

  for (z = 0; z < size; z++)
    {
      if (puz[x][z] == t || puz[z][y] == t)
	return 0;		//if same value in a row or column then not valid
    }
  if (size == 4)		//check to see which of the 4by4 sectors its in
    {
      if (x < 2)
	xstart = 0;
      else
	xstart = 2;
      if (y < 2)
	ystart = 0;
      else
	ystart = 2;
      if (t == puz[xstart][ystart] || t == puz[xstart + 1][ystart]
	  || t == puz[xstart][ystart + 1] || t == puz[xstart + 1][ystart + 1])
	return 0;		//if same value already exists in sector then not valid
    }

  if (size == 9)		//check to see which of the 9by9 sectors it's in 
    {
      if (x < 3)
	xstart = 0;
      if (x > 5)
	xstart = 6;
      if (x > 2 && x < 6)
	xstart = 3;

      if (y < 3)
	ystart = 0;
      if (y > 5)
	ystart = 6;
      if (y > 2 && y < 6)
	ystart = 3;

      for (i = xstart; i < xstart + 3; i++)
	{
	  for (j = ystart; j < ystart + 3; j++)
	    {
	      if (t == puz[i][j])
		return 0;	//if the value already exists in the sector then not a valid placement
	    }
	}
    }

  return 1;
}

//check to see if puzzle is complete
template < typename T > int Puzzle < T >::isComplete ()
{
  int x;
  int y;
  for (x = 0; x < size; x++)
    {
      for (y = 0; y < size; y++)
	{
	  if (puz[x][y] == 0)
	    return 0;		//if any of the spaces are 0 then the puzzle is not complete
	}
    }
  return 1;
}

//set space x,y equal to value t
template < typename T > void Puzzle < T >::set (int x, int y, T t)
{
  puz[x][y] = t;
}

//finds a hidden singles
template < typename T > int Puzzle < T >::hiddensingle (int i, int j)
{
  int count = 0;
  int istart;
  int jstart;
  int a;			//for loop variables
  int b;
  int c;
  int d;
  int e;
  int z;			//value we're looking for
  for (a = 0; a < notsolved[i][j].size (); a++)
    {
      z = notsolved[i][j][a];
      for (b = 0; b < size; b++)
	{
	  for (c = 0; c < notsolved[i][b].size (); c++)
	    {
	      if (z == notsolved[i][b][c])
		count++;
	    }
	}
      if (count == 1)		//if hidden single in row
	{
	  puz[i][j] = z;
	  return 1;
	}
      count = 0;
      for (b = 0; b < size; b++)
	{
	  for (c = 0; c < notsolved[b][j].size (); c++)
	    {
	      if (z == notsolved[b][j][c])
		count++;
	    }
	}
      if (count == 1)		//if hidden single in row
	{
	  puz[i][j] = z;
	  return 1;
	}
      count = 0;
//check in sub sector
      if (i < 3)
	istart = 0;
      if (i > 5)
	istart = 6;
      if (i > 2 && i < 6)
	istart = 3;

      if (j < 3)
	jstart = 0;
      if (j > 5)
	jstart = 6;
      if (j > 2 && j < 6)
	jstart = 3;

      for (d = istart; d < istart + 3; d++)
	{
	  for (e = jstart; e < jstart + 3; e++)
	    {
	      for (c = 0; c < notsolved[d][e].size (); c++)
		{
		  if (z == notsolved[d][e][c])
		    count++;
		}
	    }
	}
      if (count == 1)		//if hidden single in sub section
	{
	  puz[i][j] = z;
	  return 1;
	}
      count = 0;
    }
  return 0;			//no hidden singles
}

//solves puzzle
template < typename T > void Puzzle < T >::solve ()
{
  int madechange;
  int i;
  int j;
  int z = 0;
  while (z == 0)		//while the puzzle isn't complete
    {
      madechange = 0;
      for (i = 0; i < size; i++)
	{
	  for (j = 0; j < size; j++)
	    {
	      if (puz[i][j] == 0)
		{
		  if (notsolved[i][j].size () == 1)	//if only one valid option set to that option
		    {
		      puz[i][j] = notsolved[i][j][0];
		      reset ();
		      madechange++;	//made a change
		    }

		}
	    }
	}
      if (madechange == 0)
	{
	  for (i = 0; i < size; i++)
	    {
	      for (j = 0; j < size; j++)
		{
		  if (puz[i][j] == 0)
		    {
		      madechange = madechange + hiddensingle (i, j);
		      reset ();
		    }
		}
	    }
	}
      z = isComplete ();
      if (madechange == 0)	//if couldn't solve
	break;
    }
}


#endif
