//
//  simplex.h
//  DietMealPlanCalc
//
//  Created by Sangheon Lee on 12/21/18.
//  Copyright © 2018 Sangheon Lee. All rights reserved.
//

#ifndef simplex_h
#define simplex_h

#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>

class Simplex{
public:
    
    void setMacro(double inCal, double inPro, double inCarb, double inFat){
        matrix[1].back() = inPro;
        matrix[2].back() = inCarb;
        matrix[3].back() = inFat;
        matrix[4].back() = inFat / 3;
        matrix[5].back() = inFat / 3 * 2;
        protein = inPro;
        carb = inCarb;
        fat = inFat;
        calories = inCal;
    }
    
    bool isOptimal(){
        //checks whether if finding a solution for the matrix is possible
        /*for (size_t i = 1; i < matrix.size(); ++i) {
            if (matrix[i].back() < 0.0) {
                solution = false;
                return true;
            }
        }*/
        //checks the if there are any coefficients that are greater than 0
        //to see if the matrix needs to be further optimized or not
        for (size_t j = 0; j < matrix[0].size(); ++j){
            if (matrix[0][j] > 0.0) {
                return false;
            }
        }
        return true;
    }
    
    void rowReduce(size_t row, size_t col){
        double coEff = matrix[row][col];
        for(size_t i = 0; i < matrix[row].size(); ++i){
            matrix[row][i] /= coEff;
        }
        for(size_t i = 0; i < matrix.size(); ++i){
            if(i != row){
                coEff = matrix[i][col];
                for(size_t k = 0; k < matrix[row].size(); ++k){
                    matrix[i][k] -= coEff * matrix[row][k];
                }
            }
        }
    }
    
    void findPivot(){
        size_t col = 0;
        for(size_t i = 1; i < matrix[0].size(); ++i){
            if(matrix[0][i] > matrix[0][col]){
                col = i;
            }
        }
        size_t row = 1;
        double min = abs(matrix[row].back() / matrix[row][col]);
        for(size_t i = 2; i < matrix.size(); ++i){
            if(matrix[i][col] > 0.0){
                if(abs(matrix[i].back()/matrix[i][col]) < min){
                    row = i;
                }
            }

        }
        rowReduce(row, col);
    }
    
    void solve(){
        while(!isOptimal()){
            findPivot();
        }
    }
    
    void Print(){
        std::cout << "Total calories: ~" << -1 * matrix[0].back() << "\n";
        std::cout << "Protein intake: ~" << protein << "\n";
        std::cout << "Carb intake: ~" << carb << "\n";
        std::cout << "Fat intake: ~" << fat << "\n";
        for(size_t i = 1; i < matrix.size(); ++i){
            for(size_t k = 0; k < matrix[i].size()-matrix.size(); ++k){
                if(matrix[i][k] == 1.0 && matrix[i].back() >= 0.01){
                    std::cout << matrix[i].back() << " serving size of " << food[k] << "\n";
                    break;
                }
            }
        }
        
        
        //matrix data
        std::cout << "\n";
        for(size_t i = 0; i < matrix.size(); ++i){
            for(size_t k = 0; k < matrix[i].size(); ++k){
                std::cout << matrix[i][k] << ' ';
            }
            std::cout << "\n";
        }
    }
    
    
private:
    bool solution = true;
    //Simplex(std::vector<std::vector<double>>);
    std::vector<std::vector<double>> matrix = {
      //breast Brice  broc   avo   egg   sal  bana
        {120,  111,    34,   234,   78,   177, 105, 0,0,0,0,0,     0}, //cal
        {26,   2.6,    2.8,  2.9,     6,   17, 1.3, 1,0,0,0,0,   160}, //protein
        {0,    23,      7,    12,   0.6,    0, 27,  0,1,0,0,0,   120}, //carb
        {1,    0.9,    0.4,   21,     5,   11, 0.4, 0,0,1,0,0,    50}, //fat
        {1,    0.2,    0.1,  3.1,   1.6,  2.6, 0.1, 0,0,0,1,0, 16.67}, //sat fat
        {0,    0.6,    0.1, 16.7,   2.7,  6.5, 0.1, 0,0,0,0,1, 33.33}  //unsat fat
    };/*
    std::vector<std::vector<double>> matrix = {
        //breast Brice  broc   avo
        {120,  56,    34,   322, 0}, //cal
        {26,   1.25,  2.8,  4, 0}, //protein
        {0,    11.25, 7,    17, 0}, //carb
        {1,    0.45,  0.4,  29, 0}   //fat
    };*/
    double calories = 1640;
    double protein = 160;
    double carb = 120;
    double fat = 50;
    std::vector<std::string> macro = {"Protein", "Carb", "Saturated Fat", "Unsaturated Fat"};
    std::vector<std::string> food = {"Chicken Breast", "Brown Rice", "Brocoli", "Avocado", "Eggs", "Salmon", "Banana"};
    
    
};

#endif /* simplex_h */
