
#include <cmath>
#include <iostream>
#include "CGG_Main.h"
#include <math.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <glm.hpp>

#define windowWidth 1000
#define windowHeight 1000
void InitialiseWindow();
void StraightLine();
void Circle();
void CircleFilled();
void Square();
void SquareFilled();
void Triangle();
void Cube();
void BezierCurve();
void MandelbrotFunct();
void SepinskiTriangle();
void UserGuide();

double MapToImaginary(int _y, int _windowHeight, double _minImagin, double _maxImagin);
int MainMandelbrotFunct(double _cR, double _cI, int _maxIterations);
double MapToReal(int _x, int _windowWidth, double _minReal, double _maxReal);
float Interp(float _v0, float _v1, float _t);
void StarField();

struct pixel
{
	int x, y; 
	int r, g, b;
};

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	bool menuLoop, mainLoop;
	do
	{
		mainLoop = true;
		do
		{
			system("CLS");
			menuLoop = true;
			char menuChoice;
			std::cout << "Menu\n";
			std::cout << "1 - Draw a line between two points\n";
			std::cout << "2 - Draw 2D shapes\n";
			std::cout << "3 - Draw Bezier curves\n";
			std::cout << "4 - Draw a cube\n";
			std::cout << "5 - Draw a fractal\n";
			std::cout << "6 - Exit\n";
			std::cout << "7 - User guide\n";
			menuChoice = _getch();

			switch (menuChoice)
			{
				case '1':
				{
					StraightLine();
					break;
				}
				case '2':
				{
					Circle();
					CircleFilled();
					Square();
					SquareFilled();
					Triangle();
					break;
				}
				case '3':
				{
					BezierCurve();
					break;
				}
				case '4':
				{
					Cube();
					break;
				}
				case '5':
				{
					MandelbrotFunct();
					SepinskiTriangle();
					break;
				}
				case '6':
				{
					menuLoop = false;
					mainLoop = false;
					break;
				}
				case '7':
				{
					UserGuide();
					break;
				}
				default:
				{
					menuLoop = true;
					std::cout << menuChoice << " is not a valid option\nPlease selecter another\n";
					system("PAUSE");
					break;
				}
			}
		} while (menuLoop == true);
	}while (mainLoop == true);
	return 0;
}
void InitialiseWindow()
{
	//Opens the window to the set size
	if (!CGG::Init(windowWidth, windowHeight))
	{
		return;
	}
	//Sets the background to black
	CGG::SetBackground(0, 0, 0);
}
void StraightLine()
{	//Initialise variables
	float originX, originY, endX, endY;
	double t = 0;
	bool straightLineLoop = false;
	//Creation of a vector that will store the line
	std::vector<pixel> vecLinear;
		do
		{
			system("CLS");
			straightLineLoop = true;
			std::cout << "Please input coordinates of a starting point and an end point of the line\n";
			std::cout <<"Between 0 - 1000\n";
			std::cout << "Input the x coordinate of the starting point\n";
			std::cin >> originX;
			std::cout << "Input the y coordinate of the starting point\n";
			std::cin >> originY;
			std::cout << "Input the x coordinate of the ending point\n";
			std::cin >> endX;
			std::cout << "Input the y coordinate of the ending point\n";
			std::cin >> endY;
			//Checks if input is valid and if not return to the top of the loop and ask the user to input coordinates again
			if (originX > 1000 || originY > 1000 || endX > 1000 || endY > 1000 )
			{
				straightLineLoop = true;
				std::cout << "please enter values between 0 - 1000\n";
				system("PAUSE");
			}
			//If the conditions are met continue
			else
			{
				InitialiseWindow();
				//Adds the coordinates of each pixel in the line to the vector and then pushes it back to the start
				do
				{
					t += 0.001;
					pixel tempPix = { Interp(originX, endX, t), Interp(originY, endY, t), 255, 0, 100 };
					vecLinear.push_back(tempPix);
				} while (t <= 1);
				//Prints out the line pixel by pixel until the length of the vector has been reached
				for (int i = 0; i < vecLinear.size(); i++)
				{
					CGG::DrawPixel(vecLinear.at(i).x, vecLinear.at(i).y, vecLinear.at(i).r, vecLinear.at(i).g, vecLinear.at(i).b);
					CGG::ProcessFrame();
				}
				break;
			}
		} while (straightLineLoop == true);
		system("PAUSE");
		CGG::Cleanup();
}
void Circle()
{
		InitialiseWindow();
		//Size of the circle
		int radius = 100;
		//Starting angle of the circle
		float angle = 0;
		//Position vector of the circle
		glm::vec2 centreCircle = { 500, 500 };
		//The amount that will be added to the angle as it rotates around the centre
		float addAngle = 0.001;
		//Prints out the circle
		for (int t = 0; angle <= 360; t++)
		{
			//Starts from the centre x and y coordinate then adds the radius times the angle in the x and y plane thus rotating around the point
			double x = centreCircle.x + radius*cos(angle);
			double y = centreCircle.y + radius*sin(angle);
			//Prints out the pixel and interpolates between the given values thus changing colour
			CGG::DrawPixel(x, y, Interp(255, 0, t), Interp(255, 0, t), Interp(0, 255, t));
			//The angle is increased by 0.001 each time
			angle += addAngle;
			//The loop will continue untill one full rotation has been completed
		}
		CGG::ProcessFrame();
		system("PAUSE");
		CGG::Cleanup();
}
void CircleFilled()
{
	InitialiseWindow();
	//Radius of the circle
	int radius = 100;
	//Staring angle of the circle
	float angle = 0;
	//Position vector of the circle
	glm::vec2 centreCircle = { 500, 500 };
	//the amount the angle will be increased by each time
	float addAngle = 0.01;
		do
		{   
			float t = 0;
				do 
				{	//Increases both t variables by 1 as the loop increases
					t++;
					double x = centreCircle.x + (t*0.01*radius*cos(angle));
					double y = centreCircle.y + (t*0.01*radius*sin(angle));
					CGG::DrawPixel(x, y, Interp(0, 255, t), Interp(255, 0, t), Interp(0, 255, t));
					//Draws a straight line out from the centre to the radius
				} while (t<radius);
			angle += addAngle;
			//Draws the lines 360 degrees round the circle until its filled
		} while (angle <= 360);
	CGG::ProcessFrame();
	system("PAUSE");
	CGG::Cleanup();
}
void Square()
{
	InitialiseWindow();
	//Sets the coordinates for the 4 vertices of the square
	glm::vec2 point1 = { 400, 600 };
	glm::vec2 point2 = { 400, 400 };
	glm::vec2 point3 = { 600, 400 };
	glm::vec2 point4 = { 600, 600 };
	//Creates four vectors to store the straight lines in
	std::vector<pixel> vecLinear, vecLinear2, vecLinear3, vecLinear4;
	float t = 0;
	//Goes through the loop and fills the vectors with pixels between each coordinate
	do
	{
		t += 0.001;

		pixel tempPix = { Interp(point1.x, point2.x, t), Interp(point1.y, point2.y, t), 150, 0, 100 };
		vecLinear.push_back(tempPix);

		pixel tempPix2 = { Interp(point2.x, point3.x, t), Interp(point2.y, point3.y, t), 255, 0, 100 };
		vecLinear2.push_back(tempPix2);

		pixel tempPix3 = { Interp(point3.x, point4.x, t), Interp(point3.y,point4.y, t), 200, 0, 100 };
		vecLinear3.push_back(tempPix3);

		pixel tempPix4 = { Interp(point4.x, point1.x, t), Interp(point4.y,point1.y, t), 100, 0, 100 };
		vecLinear4.push_back(tempPix4);

	} while (t <= 1);
	//Goes through the vectors and prints out the lines untill the length of the lines have been reached
	for (int i = 0; i < vecLinear.size(); i++)
	{
		CGG::DrawPixel(vecLinear.at(i).x, vecLinear.at(i).y, vecLinear.at(i).r, vecLinear.at(i).g, vecLinear.at(i).b);
		CGG::DrawPixel(vecLinear2.at(i).x, vecLinear2.at(i).y, vecLinear2.at(i).r, vecLinear2.at(i).g, vecLinear2.at(i).b);
		CGG::DrawPixel(vecLinear3.at(i).x, vecLinear3.at(i).y, vecLinear3.at(i).r, vecLinear3.at(i).g, vecLinear3.at(i).b);
		CGG::DrawPixel(vecLinear4.at(i).x, vecLinear4.at(i).y, vecLinear4.at(i).r, vecLinear4.at(i).g, vecLinear4.at(i).b);
		CGG::ProcessFrame();
	}	
	
	system("PAUSE");
	CGG::Cleanup();
}
void SquareFilled()
{
	InitialiseWindow();
	//Creation of an array that will hold random numbers
	int randomColour[3];
	//Randomisation of a number between 0 and 255 and stores it in the array
	for (int i = 0; i < 3; i++)
	{
		randomColour[i] = rand() % 255;
	}
	//Prints out a filled square 
	for (int x = 400; x < 600; x++)
	{
		for (int i = 400; i <= 600; i++)
		{
			CGG::DrawPixel(x , i, randomColour[0], randomColour[1], randomColour[2]);
		}
		CGG::ProcessFrame();
	}
	system("PAUSE");
	CGG::Cleanup();
}
void Triangle()
{
	InitialiseWindow();
	//Sets the 3 points of the triangle
	glm::vec2 point1 = { 400, 600 };
	glm::vec2 point2 = { 500, 400 };
	glm::vec2 point3 = { 600, 600 };
	//Creation of 3 vectors to store the 3 lines between the points
	std::vector<pixel> vecLinear, vecLinear2, vecLinear3;
	float t = 0;
	//Goes through each pixel and adds the coordinates to the desired vector
	do
	{
		t += 0.001;

		pixel tempPix = { Interp(point1.x, point2.x, t), Interp(point1.y, point2.y, t), 255, 0, 100 };
		vecLinear.push_back(tempPix);

		pixel tempPix2 = { Interp(point2.x, point3.x, t), Interp(point2.y, point3.y, t), 255, 0, 100 };
		vecLinear2.push_back(tempPix2);

		pixel tempPix3 = { Interp(point3.x, point1.x, t), Interp(point3.y,point1.y, t), 255, 0, 100 };
		vecLinear3.push_back(tempPix3);

	} while (t <= 1);
	//Prints out the lines pixel by pixel until the length of the vector has been reached
	for (int i = 0; i < vecLinear.size(); i++)
	{
		CGG::DrawPixel(vecLinear.at(i).x, vecLinear.at(i).y, vecLinear.at(i).r, vecLinear.at(i).g, vecLinear.at(i).b);
		CGG::DrawPixel(vecLinear2.at(i).x, vecLinear2.at(i).y, vecLinear2.at(i).r, vecLinear2.at(i).g, vecLinear2.at(i).b);
		CGG::DrawPixel(vecLinear3.at(i).x, vecLinear3.at(i).y, vecLinear3.at(i).r, vecLinear2.at(i).g, vecLinear3.at(i).b);
CGG::ProcessFrame();
	}	
	system("PAUSE");
	CGG::Cleanup();
}
void BezierCurve()
{
	InitialiseWindow();
	
		//Initalises two arrays
		int randomNumberX[3];
		int randomNumberY[3];

		//Randomises a number 3 times and stores in array for both x and y planes
		for (int i = 0; i < 3; i++)
		{
			randomNumberX[i] = rand() % 500;
		}
		for (int v = 0; v < 3; v++)
		{
			randomNumberY[v] = rand() % 1000;
		}

		//Declaration of variables / randomising input parameters
		glm::vec2 originQuad = { 0, windowHeight / 2 };
		glm::vec2 pointOneQuad = { randomNumberX[0],randomNumberY[0] };
		glm::vec2 pointFinalQuad = { 500, windowHeight / 2 };
		glm::vec2 originCubi = { 500, windowHeight / 2 };
		glm::vec2 pointOneCubi = { 500 + randomNumberX[1], randomNumberY[1] };
		glm::vec2 pointTwoCubi = { 500 + randomNumberX[2], randomNumberY[2] };
		glm::vec2 pointFinalCubi = { 1000,windowHeight / 2 };                
		double t = 0, curveQuadX, curveQuadY, curveCubiX, curveCubiY;
		
		//Creates two vectors to store the quadratic and cubic bezier curves;
		std::vector<pixel> tempVecQuad, tempVecCubi;

		do
		{
			t += 0.001;
			//Quadratic curve Equation
			curveQuadX = pow(1 - t, 2)* originQuad.x + 2 * (1 - t)*t * pointOneQuad.x + (pow(t, 2) *pointFinalQuad.x);
			curveQuadY = pow(1 - t, 2)* originQuad.y + 2 * (1 - t)*t * pointOneQuad.y + (pow(t, 2) *pointFinalQuad.y);

			//Creates a variable which stores information for the coordinates and the colour of each pixel
			pixel tempPix = { curveQuadX, curveQuadY,Interp(0,255,t) , Interp(255,0 ,t), Interp(0,255,t) };

			//Adds this data to the vector and pushes it back to the start
			tempVecQuad.push_back(tempPix);

			//Cubic curve Equation
			curveCubiX = pow((1 - t), 3)*originCubi.x + 3 * pow((1 - t), 2)*t*pointOneCubi.x + 3 * (1 - t)*pow(t, 2)*pointTwoCubi.x + pow(t, 3)*pointFinalCubi.x;
			curveCubiY = pow((1 - t), 3)*originCubi.y + 3 * pow((1 - t), 2)*t*pointOneCubi.y + 3 * (1 - t)*pow(t, 2)*pointTwoCubi.y + pow(t, 3)*pointFinalCubi.y;
			pixel tempPix2 = { curveCubiX, curveCubiY, Interp(0,255,t),Interp(255, 0, t),0 };
			tempVecCubi.push_back(tempPix2);

		} while (t <= 1);

		//Goes through the vector printing out each pixel until the vector size has been reached
		for (int i = 0; i < tempVecQuad.size(); i++)
		{
			CGG::DrawPixel(tempVecQuad.at(i).x, tempVecQuad.at(i).y, tempVecQuad.at(i).r, tempVecQuad.at(i).g, tempVecQuad.at(i).b);
			CGG::DrawPixel(tempVecCubi.at(i).x, tempVecCubi.at(i).y, tempVecCubi.at(i).r, tempVecCubi.at(i).g, tempVecCubi.at(i).b);
			CGG::ProcessFrame();
		}
		system("PAUSE");
		CGG::Cleanup();
}
void Cube()
{

	InitialiseWindow();
	//Prints out a filled square 
	int v = 0;
	for (int x = 400; x < 600; x++)
	{
		for (int i = 400; i <= 600; i++)
		{	
			CGG::DrawPixel(x, i, 255, 0, 0);
		}
		CGG::ProcessFrame();
	}
	//Prints out a parallelogram
	for (int x = 600; x < 650; x++)
	{
		v++;
		for (int i = 400; i <= 600; i++)
		{
			CGG::DrawPixel(x, i - v, 0, 255, 0);
		}

		CGG::ProcessFrame();
	}
	//Prints out a parallelogram
	for (int x = 350; x < 400; x++)
	{
		v++;
		for (int i = 500; i <= 700; i++)
		{
			CGG::DrawPixel(i -v , x, 0, 0, 255);
		}

		CGG::ProcessFrame();
	}
	system("PAUSE");
	CGG::Cleanup();
}
void MandelbrotFunct()
{
	InitialiseWindow();
	//Max value of n
	int maxN = 255;
	//Sets the boundaries for the fractal
	double minReal = -1.5, maxReal = 0.7, minImagin = -1.0, maxImagin = 1.0;
	//Prints out every pixel
	for (int y = 0; y < windowHeight; y++)
	{
		//Prints out the pixels in the x direction
		for (int x = 0; x < windowWidth; x++)
		{
			//Maps the number to real plane
			double cR = MapToReal(x, windowWidth, minReal, maxReal) - 0.3;
			//Maps the number to the imaginary plane
			double cI = MapToImaginary(y, windowHeight, minImagin, maxImagin);
			int n = MainMandelbrotFunct(cR, cI, maxN);
			CGG::DrawPixel(x, y, (n * 256), ((n*n) % 256), ((n*n) % 256));
		}
	}
	CGG::ProcessFrame();
	system("PAUSE");
	CGG::Cleanup();
}
void SepinskiTriangle()
{
	InitialiseWindow();

	//Three coordinates of the Big triangle
	glm::vec2 point1 = { 100, 800 };
	glm::vec2 point2 = { 500, 100 };
	glm::vec2 point3 = { 900,800 };
	//Start point within the triangle
	glm::vec2 trianglePointStart = { 500, 450 };
	glm::vec2  randomPixel = { 0,0 };

	int random = rand() % 3;
	//Creation of two arrays of the x and y coordinates of the three points of the big triangle
	int randomTrianglePointX[3] = { point1.x, point2.x, point3.x };
	int randomTrianglePointY[3] = { point1.y, point2.y, point3.y };
	//Creation of a vector that will hold each pixel plotted
	std::vector<pixel> randomPixelVec;
	//Randomly chooses one of the three points of the big triangle and finds the mid-point between the start point and the random point of the big triangle
	glm::vec2 firstRandom = { abs(randomTrianglePointX[random] + trianglePointStart.x)/2, abs(randomTrianglePointY[random] + trianglePointStart.y)/2 };
	double t = 0;
	for (int i = 0; i < 100000; i++)
	{
		t += 0.001;
		random = rand() % 3;
		//Randomly chooses one of the three points of the big triangle and finds the mid-point between the random other point and adds it to the vector
		randomPixel = { abs(randomTrianglePointX[random] + randomPixel.x) / 2, abs(randomTrianglePointY[random] + randomPixel.y) / 2 };
		//Adds this point to the vector
		pixel tempPix = { randomPixel.x, randomPixel.y, Interp(255, 0, t),Interp(0, 255, t),Interp(255, 0, t) };
		randomPixelVec.push_back(tempPix);
	}
	//Prints out the array until the length of the vector has been reached
	for (int i = 0; i < randomPixelVec.size(); i++)
	{
		CGG::DrawPixel(randomPixelVec.at(i).x, randomPixelVec.at(i).y, randomPixelVec.at(i).r, randomPixelVec.at(i).g, randomPixelVec.at(i).b);
		
	}
CGG::ProcessFrame();
system("PAUSE");
CGG::Cleanup();
}
void UserGuide()
{
	system("CLS");
	std::cout << "Press a number between 1 and 7 for options\n";
	std::cout << "1 - Will allow the user to select two points in 2D space and draw a line between them\n";
	std::cout << "2 - Will allow the user to see 2D printed shapes\n";
	std::cout << "3 - Will allow the user to see randomised quadratic and cubic bezier curves\n";
	std::cout << "4 - Will allow the user to see a 3D printed Cube\n";
	std::cout << "5 - Will allow the user to see a mandelbrot fractal and sepinskis triangle\n";
	std::cout << "6 - Will exit the program\n";
	system("PAUSE");
	system("CLS");

	std::cout << "When navigating the menu\n\n";
	std::cout << "After a number has been selected and the animation has finished\n(if it has an animation) press enter to continue\n";
	system("PAUSE");
}
int MainMandelbrotFunct(double _cR, double _cI, int _maxIterations)
{
	int i = 0;
	double zR = 0.0, zI = 0.0;
	while (i < _maxIterations && pow(zR,2) + pow(zI,2) < 4.0)
	{
		double temp = pow(zR,2) - pow(zI,2) +_cR;
		zI = 2.0 * zR * zI + _cI;
		zR = temp;
		i++;
	}
	return i;
}
double MapToImaginary(int _y, int _windowHeight, double _minImagin, double _maxImagin)
{
	_minImagin = -1.0, _maxImagin = 1.0;
	double range = _maxImagin - _minImagin;
	return _y*(range / _windowHeight) + _minImagin;
}
double MapToReal(int _x, int _windowWidth, double _minReal, double _maxReal)
{
	_minReal = -1.5, _maxReal = 0.7;
	double range = _maxReal - _minReal;
	return _x*(range / _windowWidth) + _minReal;
}
float Interp(float _v0, float _v1, float _t) // https://en.wikipedia.org/wiki/Linear_interpolation
{
	return _v0 + _t * (_v1 - _v0);
}
void StarField()
{
	InitialiseWindow();
	int time = 0;
	int randomCoordinates[2];
	std::vector<pixel> vecLinear;
	int q = 0;
	do
	{
		q++;
		do
		{
			for (int i = 0; i <= 2; i++)
			{
				randomCoordinates[i] = rand() % 1000;
			}
			time++;
			glm::vec2 centrePoint = { windowWidth / 2, windowHeight / 2 };
			glm::vec2 randomPoint = { randomCoordinates[0],randomCoordinates[1] };
			float t = 0;
			//Draw a line between the centre circle and the very edge of the display
			float linearBezX, linearBezY;

			do
			{
				t += 0.01;
				//Linear bezier equation
				linearBezX = (1 - t)*centrePoint.x + t*randomPoint.x;
				linearBezY = (1 - t)*centrePoint.y + t*randomPoint.y;
				pixel tempPix = { linearBezX, linearBezY, 255, 100, 100 };
				vecLinear.push_back(tempPix);
			} while (t <= 1);

			for (int i = 0; i < vecLinear.size(); i++)
			{
				CGG::DrawPixel(vecLinear.at(i).x, vecLinear.at(i).y, vecLinear.at(i).r, vecLinear.at(i).g, vecLinear.at(i).b);
				CGG::ProcessFrame(); CGG::SetBackground(0, 0, 0);
			};

		
		} while (time < 5);
	} while (q < 100);
		
	system("PAUSE");
	CGG::Cleanup();
}