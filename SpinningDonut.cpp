/**
    @title CS112 Assignment # 3
    @file A3_2021189_2021438.cpp
    @author Hammad Anwer 2021189, Muhammad Rehan 2021438

    @version 0.1
    @date 2022-03-27    
    @copyright Copyright (c) 2022
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <Windows.h>

using namespace std;

#define PI 3.14
#define K1 20
#define K2 5
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 30
#define theta_step 0.08
#define phi_step 0.02


class Donut
{
private:
    int x1, y1,
        Luminance;
    float x, y, z,
        R1, R2,
        X_tilt, Z_tilt,
        circx, circy,
        cX, cZ, 
        cph, cth,
        sth, sph,
        sX, sZ,
        ooz,
        rawLumVal;
    char donut_display[SCREEN_HEIGHT][SCREEN_WIDTH];
    int zmem[SCREEN_HEIGHT][SCREEN_WIDTH];
    string Lum;

public:
    Donut();
    void cleanArray();
    void projection();
    void settingVal(float j);
    void setXYZVal();
    void setX1Y1();
    void fillArray();
    void lumCalc();
    void printArray();
};


/**
 * @brief Driver code to create an instance of a class Donut and continously project a
 *        spinning donut.
 */

int main()
{
    Donut d1;
    system("cls");
    while (1)
    {
        d1.projection();
       
    }
}

/**
 * @brief A function that brings the console pointer to the top left so that
 * new data can be overwritten in the console
 * 
 */

void clear_screen()
{
  COORD coord = {0};  // Stores the console coordinates      
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE ); // An object that could control the console functions
  SetConsoleCursorPosition ( h, coord ); // Move the console cursor to specified coordinate
}


/**
 * @brief Constructor for a new Donut:: when a Donut object is created
 * 
 */
Donut::Donut()
{
    x = 0, y = 0, z = 0;
    R1 = 1, R2 = 2;
    X_tilt = 0, Z_tilt = 0;
    cth = cos(0), sth = sin(0);
    cph = cos(0), sph = sin(0);
    cX = cos(X_tilt), cZ = cos(Z_tilt);
    sX = sin(X_tilt), sZ = sin(Z_tilt);
    circx = R2 + R1 * cth, circy = R1 * sth;
    x1 = 0, y1 = 0;
    Lum = ".,-~:;=!*#$@";
}

/**
 * @brief (Re)Initialize the output array and the zmem for next display of Donut
 * 
 */

void Donut::cleanArray()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            donut_display[i][j] = ' ';
            zmem[i][j] = 0;
        }
    }
}


/**
 * @brief All the calculation is done here and then the printArray function is called
 * 
 */

void Donut::projection()
{
    cleanArray();

    for (float theta = 0; theta <= 2 * PI; theta += theta_step) // Makes the circle
    {
        cth = cos(theta), sth = sin(theta);

        for (float phi = 0; phi <= 2 * PI; phi += phi_step) // rotates around y axis
        {
            settingVal(phi); // Set the values for the trig ratios
            setXYZVal(); // Set the values for Coordinates of donut in a 3D space
            ooz = 1 / z; // One over z
            setX1Y1(); // Set the projection coordinates in a 2D plane
            lumCalc(); // Calculate the luminance Value for the coordinate found
            fillArray(); // Configure the output array with the projection coordinates found
        }
    }

    printArray(); // Display the donut
    clear_screen(); // Overwrite whatever display was on the console screen
    X_tilt += 0.1; // Controls tilt in x-axis
    Z_tilt += 0.1; // Controls tilt in z-axis
}


/**
 * @brief Set the values for the trig ratios along with the circle equations
 * 
 * @param phi the angle from which the donut will rotate around the y-axis
 */

void Donut::settingVal(float phi)
{
    circx = R2 + R1 * cth; // x-coords of the circle in 2D
    circy = R1 * sth;      // y-coords of the circle in 2D

    cX = cos(X_tilt), sX = sin(X_tilt); 
    cZ = cos(Z_tilt), sZ = sin(Z_tilt);
    cph = cos(phi), sph = sin(phi);
}

/**
 * @brief Set the x, y, z in 3D space
 * 
 */

void Donut::setXYZVal()
{
    x = circx * (cZ * cph + sX * sZ * sph) - circy * cX * sZ;
    y = circx * (sZ * cph - sX * cZ * sph) + circy * cX * cZ;
    z = K2 + cX * circx * sph + circy * sX;
  
}

/**
 * @brief Set projection coordinates of 3D donuts in a 2D plane
 * 
 */

void Donut::setX1Y1()
{
    y1 = (SCREEN_WIDTH/2.0  - K1 * ooz * y) ;
    x1 = (SCREEN_HEIGHT /2.0 + K1 * ooz * x);
}


/**
 * @brief Calculate the Luminance for donut using the trig ratios calculated
 *
 */


void Donut::lumCalc()
{
    rawLumVal = cph * cth * sZ - cX * cth * sph - sX * sth + cZ * (cX * sth - cth * sX * sph);
    Luminance = 8 * rawLumVal;
}

/**
 * @brief Fill the output array with the projection coordinates found
 * 
 */

void Donut::fillArray()
{

    // If the point is in front of the light i.e the user's vision
    if (Luminance >= 0)
    {
        if (ooz > zmem[x1][y1]) // if the point is not already in the z-plane 
        {
            zmem[x1][y1] = ooz;
            donut_display[x1][y1] = Lum[Luminance];
        }
    }
    
}

/**
 * @brief Simple output of the filled array to display the donut
 * 
 */

void Donut::printArray()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            cout << donut_display[i][j];
        }
        cout << endl;
    }
}


