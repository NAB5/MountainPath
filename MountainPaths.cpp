#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "mountain_d.h"
using namespace std;


int main() {
//=======================================================================
    //declare variables
    string filename;
    int rows, columns;
    ifstream elevationMap;
    vector<vector<int>> mapVector;
//=======================================================================
    //user input and check for valid inputxss
        cout << "Enter rows: ";
        cin >> rows;
        if (!rows || rows < 0) return 1;
        // if (cin.bad()) {
        //     return 1;
        // }
        // else if (cin.fail()) {
        //     cout << "Error: Please enter an integer value " << endl;
        //     cin.clear();
        //     cin.ignore();
        //     return 1;
        // }
        cout << "Enter columns: ";
        cin >> columns;
        if (!columns || columns < 0) return 1;
        // if (cin.bad()) {
        //     return 1;
        // }
        // else if (cin.fail()) {
        //     cout << "Error: Please enter an integer value " << endl;
        //     cin.clear();
        //     cin.ignore();
        //     return 1;
        // }
        cout << "Enter Filename: ";
        cin >> filename;
        elevationMap.open(filename);
        if ( !elevationMap.is_open() ){
            cout << "Error: Opening File" << endl;
            return 1;
        }
//======================================================================
    //reading and storing values from file into 2d array

    mapVector = data2Array(elevationMap, rows, columns);

//======================================================================
    //finding min and max

    //min
    int min = minElevation(mapVector);

    //max
    int max = maxElevation(mapVector);

//=======================================================================
    //creating greyscale vectors
    vector<vector<int>> greyMapVector = greyCalc(mapVector, rows, columns, min, max);
//=======================================================================
    //creating parallel rgb vectors
    vector<vector<int>> redVector = greyMapVector;
    vector<vector<int>> greenVector = greyMapVector;
    vector<vector<int>> blueVector = greyMapVector;
//=======================================================================
    //coloring path

    //storing first pathLength
    int shortestPath = colorPath(mapVector, redVector, greenVector, blueVector, 252,25, 63, 0);

    int shortestRow = 0;
    int pathLength = 0;
    //coloring path red and storing path length
    for (int i = 0; i < rows; i++){
      pathLength = colorPath(mapVector, redVector, greenVector, blueVector, 252,25, 63, i);
      //if row has shorter path than previous the row is saved
      if (pathLength < shortestPath){
          shortestPath = pathLength;
          shortestRow = i;
      }
  }
 //======================================================================
  //color shortest path green
  int temp = colorPath(mapVector, redVector, greenVector, blueVector, 31,253, 13, shortestRow);
//=======================================================================
    //outputting and creating ppm file
    string fname = filename + ".ppm";
    outputPPM(redVector, greenVector, blueVector, rows, columns,fname);
//=======================================================================*/
}
