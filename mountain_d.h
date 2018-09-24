#ifndef MOUNTAIN_D_H
#define MOUNTAIN_D_H
#include <vector>
#include <fstream>

int minElevation(const std::vector<std::vector<int>>&);
int maxElevation(const std::vector<std::vector<int>>&);
void outputPPM(const std::vector<std::vector<int>>& red, const std::vector<std::vector<int>>& green, const std::vector<std::vector<int>>& blue, int rows, int columns, std::string fname);
std::vector<std::vector<int>> greyCalc(const std::vector<std::vector<int>>& mapVector, int rows, int columns, int min, int max);
std::vector<std::vector<int>> data2Array(std::ifstream &fileData, int rows, int columns);
int colorPath(const std::vector<std::vector<int>>& elevationMap, std::vector<std::vector<int>>& rVector, std::vector<std::vector<int>>& gVector, std::vector<std::vector<int>>& bVector, int redVal, int greenVal, int blueVal, int startingRow);


#endif
