//
//  main.cpp
//  DietMealPlanCalc
//
//  Created by Sangheon Lee on 12/21/18.
//  Copyright © 2018 Sangheon Lee. All rights reserved.
//

#include <iostream>
#include <getopt.h>
#include <iomanip>
#include "simplex.h"
#include <vector>
using namespace std;
int main(int argc, const char * argv[]) {
    cout << setprecision(2); //Always show 2 decimal places
    cout << fixed; //Disable scientific notation for large numbers
    Simplex temp;
    cout << "Enter in weight: ";
    double weight;
    cin >> weight;
    cout << "\n" << "What kind of diet?\n" << "1) Bulk\n2) Lean Bulk\n3) Keto\n";
    int choice;
    cin >> choice;
    cout << "\n" << "How often do you work out?\n" << "1) 2-3 times a week\n" <<
    "2) 4-5 times a week\n3) 6-7 times a week\n";
    int activity;
    cin >> activity;
    double protein;
    double carb;
    double fat;
    switch (choice) {
        case 1: {
            protein = weight * 0.8;
            fat = weight * 0.5;
            switch (activity) {
                case 1: {
                    weight *= 16;
                    break;
                }
                case 2: {
                    weight *= 18;
                    break;
                }
                case 3: {
                    weight *= 20;
                    break;
                }
                default:
                    cout << "error";
                    exit(10);
                    break;
            }
            carb = (weight - protein * 4 - fat * 9) / 4;
            break;
        }
        case 2: {
            protein = weight * 1.2;
            switch (activity) {
                case 1: {
                    weight *= 13;
                    break;
                }
                case 2: {
                    weight *= 14;
                    break;
                }
                case 3: {
                    weight *= 15;
                    break;
                }
                default:
                    cout << "error";
                    exit(10);
                    break;
            }
            weight += 200;
            fat = weight * .25 / 9;
            carb = (weight - protein * 4 - fat * 9) / 4;
            break;
        }
        case 3: {
            switch (activity) {
                case 1: {
                    weight *= 13;
                    break;
                }
                case 2: {
                    weight *= 14;
                    break;
                }
                case 3: {
                    weight *= 15;
                    break;
                }
                default:
                    cout << "error";
                    exit(10);
                    break;
            }
            protein = weight * .25 / 4;
            fat = weight * .65 / 9;
            carb = weight * .1 / 4;
            break;
        }
        default:
            cout << "error";
            exit(10);
            break;
    }
    temp.setMacro(weight, protein, carb, fat);
    temp.solve();
    temp.Print();
    return 0;
}
