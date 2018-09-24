#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include "mountain_d.h"
using namespace std;

int minElevation(const vector<vector<int>>& mapVector){
    int min = mapVector.at(0).at(0);
    for ( const vector<int> &v : mapVector)
    {
         for ( int x : v ) if (min > x) min = x;
    }
    return min;
}

int maxElevation(const vector<vector<int>>& mapVector){
    int max = mapVector.at(0).at(0);
    for ( const vector<int> &v : mapVector)
    {
        for ( int x : v ) if (max < x) max = x;

    }
    return max;
}

void outputPPM(const vector<vector<int>>& red, const vector<vector<int>>& green, const vector<vector<int>>& blue, int rows, int columns, string fname){
    ofstream outputFile(fname);

    outputFile << "P3" << endl << columns << " " << rows << endl << 255 <<  endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
                outputFile << red.at(i).at(j) << " " << green.at(i).at(j) << " " << blue.at(i).at(j) << " ";
                if (j==columns-1){
                    outputFile << endl;
                }
        }
    }
}
vector<vector<int>> greyCalc(const vector<vector<int>>& mapVector,int rows, int columns, int min, int max){
    vector<vector<int>> greyMapVector(rows,vector<int> (columns));
    for (int i=0; i < rows; i++){
        for(int j=0; j < columns; j++){
            if(mapVector.at(i).at(j) == max) greyMapVector.at(i).at(j)  = 255;
            else if (mapVector.at(i).at(j) == min) greyMapVector.at(i).at(j)  = 0;
            else {
                double greyCalc = ((static_cast<double>(mapVector.at(i).at(j))-(min))/(max-min))*255 ;
                greyMapVector.at(i).at(j) = greyCalc;
            }
        }
    }
    return greyMapVector;
}

vector<vector<int>> data2Array(ifstream &fileData, int rows, int columns){
    int data;
    int i = 0;
    int j = 0;
    vector<vector<int>> dataVector(rows,vector<int> (columns));

    //stores data based on given rows x columns
    while(fileData >> data && i !=rows) {
        dataVector.at(i).at(j) = data;
        j++;
        if (j == columns && i < rows) {
            i++;
            j = 0;
        }
    }
    return dataVector;
}

int colorPath(const vector<vector<int>>& mapVector, vector<vector<int>>& rVector, vector<vector<int>>& gVector, vector<vector<int>>& bVector, int redVal, int greenVal, int blueVal, int startingRow){

    //coloring starting pixel since its base
    rVector.at(startingRow).at(0) = redVal;
    gVector.at(startingRow).at(0) = greenVal;
    bVector.at(startingRow).at(0) = blueVal;

    int i = 0,j = 0, fw = 0, fwDwn = 0, fwUp = 0, pathLength = 0;
    int rows = mapVector.size();
    int columns = mapVector[0].size();

    i = startingRow;

    //store value from data into vector
    for(j=0; j < columns-1; j++){
        if(i == 0){
            fw = abs(mapVector.at(i).at(j) - mapVector.at(i).at(j+1));
            fwDwn = abs(mapVector.at(i).at(j) - mapVector.at(i+1).at(j+1));
            fwUp = max(fw,fwDwn)+1;
        }
        else if (i == rows-1){
            fw = abs(mapVector.at(i).at(j) - mapVector.at(i).at(j+1));
            fwUp = abs(mapVector.at(i).at(j) - mapVector.at(i-1).at(j+1));
            fwDwn = max(fw,fwUp)+1;
        }
        else{
            fw = abs(mapVector.at(i).at(j) - mapVector.at(i).at(j+1));
            fwDwn = abs(mapVector.at(i).at(j) - mapVector.at(i+1).at(j+1));
            fwUp = abs(mapVector.at(i).at(j) - mapVector.at(i-1).at(j+1));
        }
      //case 1 & checking if bottom row
        if (fwDwn < fw && fwDwn <= fwUp && i != rows-1){
            rVector.at(i+1).at(j+1) = redVal;
            gVector.at(i+1).at(j+1) = greenVal;
            bVector.at(i+1).at(j+1) = blueVal;
            i++;
            pathLength += fwDwn;
        }
      //case 2
      //case 3 & checking if top row
      else if (fwUp < fw && fwUp < fwDwn && i != 0){
          rVector.at(i-1).at(j+1) = redVal;
          gVector.at(i-1).at(j+1) = greenVal;
          bVector.at(i-1).at(j+1) = blueVal;
          i--;
          pathLength += fwUp;
      }
        else if ((fw <= fwDwn && fw <= fwUp) || i == 0 || i == rows-1){
            rVector.at(i).at(j+1)= redVal;
            gVector.at(i).at(j+1) = greenVal;
            bVector.at(i).at(j+1) = blueVal;
            pathLength += fw;
        }
    }
    return pathLength;
}
