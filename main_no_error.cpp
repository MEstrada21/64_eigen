#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

//function that reads and parse a comma delimited file into a vector of vectors of strings and doubles
MatrixXd parseUniverse(string path)
{
    ifstream infile(path);
    if (!infile.is_open())
    {
        cerr << "Error: File not found" << endl;
        exit(1);
    }
    string delimiter = ",";

    vector<vector<double>> universe;

    


    int rowIndex = 0;
    int columnCount = 0;
    // row jank
    for (string line; getline(infile, line);)
    {
        // cout << line << endl;
          int columnIndex = 0;
          bool firstColumn = true;
          

          int position = 0;
          vector<double> parsedData;
          // columns of current row
          while (line.find(delimiter) != string::npos)
            {
              position = line.find(delimiter);
              if (firstColumn)
                {
                  firstColumn = false;
                  line.erase(0, position + delimiter.length());
                  continue;
                }
              //if column price is blank, increment to next column
              if (line.substr(0, position) == "")
                {
                  line.erase(0, position + delimiter.length());
                  continue;
             }

              string token = line.substr(0, position);
              if (token.compare("null") == 0)
                {
                  vector<double> lastRow = universe.at(rowIndex - 1);
                  double lastValue = lastRow.at(columnIndex);
                  parsedData.push_back(lastValue);
                }
              else
                {

                  parsedData.push_back(stod(token));
                }
              line.erase(0, position + delimiter.length());
              columnIndex++;
            }

          if (line.compare("null") == 0)
            {
              if (rowIndex > 0) {
                vector<double> lastRow = universe.at(rowIndex - 1);
                double lastValue = lastRow.at(columnIndex);
                parsedData.push_back(lastValue);
              } else {
                cout << "Error: Value of Column in first row is NULL" << endl;
                exit(1);
              }
            }
          else
            {
              parsedData.push_back(stod(line));
            }
            if (universe.size() != 0) {
              if (parsedData.size() != universe.at(0).size()) {
                cout<< "Error: Difference in number of columns" << endl;
                exit(1);
              }
            }
          universe.push_back(parsedData);
          rowIndex++;
    }
    //  cout << universe.at(i).at(j) << " 
    MatrixXd neo(universe.size(), universe.at(0).size());
    for (int i = 0; i < universe.size(); i ++) {
        for (int j = 0; j < universe.at(i).size(); j++) {
            neo(i, j) = universe.at(i).at(j);
        }
    }
    // cout << neo << endl;
    return neo;
}

MatrixXd parseCorrelation(string path){
    ifstream infile(path);
    string delimiter = ",";

    

    vector<vector<double>> correlation;

    bool isFirst = true;


    int rowIndex = 0;
    int columnCount = 0;


    for (string line; getline(infile, line);)
    {
        // cout << line << endl;
          int columnIndex = 0;
          bool firstColumn = true;
          

          int position = 0;
          vector<double> parsedData;
          // columns of current row
          while (line.find(delimiter) != string::npos)
            {
              position = line.find(delimiter);
              
                
              //if column price is blank, increment to next column
              if (line.substr(0, position) == "")
                {
                  line.erase(0, position + delimiter.length());
                  continue;
             }

              string token = line.substr(0, position);
              if (token.compare("null") == 0)
                {
                  vector<double> lastRow = correlation.at(rowIndex - 1);
                  double lastValue = lastRow.at(columnIndex);
                  parsedData.push_back(lastValue);
                }
              else
                {

                  parsedData.push_back(stod(token));
                }
              line.erase(0, position + delimiter.length());
              columnIndex++;
            }

          if (line.compare("null") == 0)
            {
              if (rowIndex > 0) {
                vector<double> lastRow = correlation.at(rowIndex - 1);
                double lastValue = lastRow.at(columnIndex);
                parsedData.push_back(lastValue);
              } else {
                cout << "Error: Value of Column in first row is NULL" << endl;
                exit(1);
              }
            }
          else
            {
              parsedData.push_back(stod(line));
            }
            if (correlation.size() != 0) {
              if (parsedData.size() != correlation.at(0).size()) {
                cout<< "Error: Difference in number of columns" << endl;
                exit(1);
              }
            }
          correlation.push_back(parsedData);
          rowIndex++;
    }
    MatrixXd correlationMatrix(correlation.size(),correlation.at(0).size());
    for(int i = 0; i<correlation.size(); i++){
        for(int j =0; j< correlation.at(i).size(); j++ ){
            correlationMatrix(i,j) = correlation.at(i).at(j);
        }
    }
    // cout << correlationMatrix << endl;
    return correlationMatrix;
}

MatrixXd convertCorrelationToCovariance(MatrixXd* correlationMatrix, MatrixXd* universe) {

    // correlationMatrix(x, y) *= (universe(x, 1) * universe(y, 1));
 
    MatrixXd covars(correlationMatrix->cols() + 2, correlationMatrix->rows() + 2);
    for (int i = 0; i < correlationMatrix->rows(); i ++) {
        for (int j = 0; j < correlationMatrix->cols(); j++) {
            covars(i, j) = (*correlationMatrix)(i, j) * (*universe)(i, 1) * (*universe)(j, 1);
        }
        covars(i, correlationMatrix->cols()) = 1;
        covars(i, correlationMatrix->cols() + 1) = (*universe)(i, 0);
    }

    for (int j = 0; j < correlationMatrix->cols(); j++) {
        covars(correlationMatrix->rows(), j) = 1;
        covars(correlationMatrix->rows() + 1, j) = (*universe)(j, 0);
    }

    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            covars(correlationMatrix->cols() + i, correlationMatrix->rows() + j) = 0;
            covars(correlationMatrix->cols() + j, correlationMatrix->rows() + i) = 0;
        }
    }
    // cout << covars << endl;
    return covars;
}

int main(int argc, const char *argv[])
{ //no command line argument error handling

    cout << "Hello World" << endl;
    if (argc != 3)
    {
        cout << "Error: Incorrect number of arguments." << endl;
        return 1;
    }
    // ifstream infile(argv[1]);
    // if (!infile.is_open())
    // {
    //     cout << "Error: File not found" << endl;
    //     exit(1);
    // }
    if (argv[1] == NULL)
    {
        cout << "Error: No file name provided." << endl;
        return 1;
    }
    //file does not exist error handling
    MatrixXd universe = parseUniverse(argv[1]);
    MatrixXd correlationMatrix = parseCorrelation(argv[2]);

    MatrixXd covars = convertCorrelationToCovariance(&correlationMatrix, &universe);
    for (int i = 1; i <= 26; i++) {
      cout << "------" << endl;
      VectorXd b = VectorXd::Zero(covars.cols());
      b(covars.cols() - 2) = 1.0;
      b(covars.cols() - 1)= i * 0.01;

      cout << i << endl;
      // break;
      VectorXd w = (covars.transpose() * covars).ldlt().solve(covars.transpose() * b);
      cout << "--- weights" << endl;
      cout << w << endl;
      VectorXd expectedReturn = covars * w;
      MatrixXd portfolioVariance = covars * w * w.transpose();
      cout << "---expected return" << endl;
      cout << expectedReturn << endl;
      cout << "---port var" << endl;
      cout << portfolioVariance << endl;
      cout << "---port volitility" << endl;
      cout << portfolioVariance.cwiseSqrt() << endl;
    }
    // what do I do here?
    // what goes here?
}