
 //---------------------------------------------------------------------------------
 //  Description:  Example controller program for Nao robot.
 //                This demonstrates how to use NaoRobotAPI
 //---------------------------------------------------------------------------------

#include "NaoRobotAPI.h"
#include <iostream>

NaoRobotAPI* nao;

void print() {

	//Read sonar range values
	double sonarLeft, sonarRight;
	nao->getSonarRange(sonarLeft, sonarRight);

	//Read foot bumper values
	bool leftFoot_left, leftFoot_right, rightFoot_left, rightFoot_right;
	nao->getFootBumpers(leftFoot_left, leftFoot_right, rightFoot_left, rightFoot_right);

	cout << "--------------------SENSOR VALUES-------------------------------------" << endl;
	cout << "POSE         : (X) " << nao->getX() << " meters, " 
		<<"(Y) " << nao->getY() << " meters, " 
		<<"(Th) " << nao->getTh() << " degrees" << endl << endl;
	cout << "SONAR RANGES : (LEFT) "<<sonarLeft
		<<" meters, (RIGHT) "<<sonarRight<<" meters" << endl << endl;
	cout << "FOOT FORCE   : " << nao->getFootForce() << " kg.f" << endl;
	cout << "----------------------------------------------------------------------" << endl;
}


// main function
int main() {
	//Create a robot object
    nao = new NaoRobotAPI();

	//Make connection to Nao
    nao->connect();

	//Move forward for a few steps and print the sensor values
    nao->moveRobot(FORWARD);
    Sleep(10000);
	nao->stopRobot();
	print();

	//Move backward for a few steps and print the sensor values
	nao->moveRobot(BACKWARD);
	Sleep(10000);
	nao->stopRobot();
	print();

	//Move left for a few steps and print the sensor values
	nao->moveRobot(LEFT);
	Sleep(10000);
	nao->stopRobot();
	print();

	//Move right for a few steps and print the sensor values
	nao->moveRobot(RIGHT);
	Sleep(10000);
	nao->stopRobot();
	print();

	//Turn left and print the sensor values
	nao->turnRobot(LEFT);
	Sleep(10000);
	nao->stopRobot();
	print();

	//Turn right and print the sensor values
	nao->turnRobot(RIGHT);
	Sleep(10000);
	nao->stopRobot();
	print();

	// close connection to the robot
    nao->disconnect();

	//Delete the robot object
    delete nao;
    return 0;
}
