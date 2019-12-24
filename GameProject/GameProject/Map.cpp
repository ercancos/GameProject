﻿#include "Map.h"

SpaceShip vu;

Map::Map() {  //Set map's row and coluom
	row = 120;
	col = 30;
}

void Map::print() {
	int mlocx, mlocy, fuel, armor, coin;
	int x = 70;  //Set SpaceShip' x coordinate
	int y = 15;  //Set SpaceShip' y coordinate

	//For creating random number of Asteroids.
	int num0, num1, num2, i_c;
	num0 = rand() % 20;
	num1 = rand() % 30;
	num2 = rand() % 40;
	//..

	setWalls(); // print Map's walls

	//Creating part for Asteroids.
	Asteroit *A[90];
	for (i_c = 0; i_c < num0; i_c++) {
		A[i_c] = new Large_ast();
		A[i_c]->calculater();
		A[i_c]->print();
	}//End of first for loop.
	for (i_c = num0; i_c < (num0 + num1); i_c++) {
		A[i_c] = new Medium_ast();
		A[i_c]->calculater();
		A[i_c]->print();
	}//End of second for loop.
	for (i_c = num1; i_c < (num0 + num1 + num2); i_c++) {
		A[i_c] = new Small_ast();
		A[i_c]->calculater();
		A[i_c]->print();
	}//End of third for loop.
	//..


	fuel = vu.getFuel();
	armor = vu.getArmor();
	coin = vu.getCoin();
	rlutil::locate(45, 30); cout << "Fuel : " << fuel; // show the first fuel amount
	rlutil::locate(60, 30); cout << "Armor : " << armor; // show the first armor amount
	rlutil::locate(75, 30); cout << "Coin : " << coin; // show the first armor amount

	//Spaceship Move.
	Turret g;
	Mortar mor;
	Menu menu;
	int collision, j, hit = -1, rad, i, morx, mory;

	gotoxy(x, y); rlutil::setColor(2);  cout << '^' << endl; // Show player
	while (true) {
		if (kbhit()) {
			int k = rlutil::getkey(); // Input character
			gotoxy(x, y); cout << " "; // Delete player


			if (k == rlutil::KEY_LEFT) {
				--x; gotoxy(x, y); rlutil::setColor(2);  cout << '<'; rlutil::setColor(7); fuel--;  rlutil::locate(45, 30); cout << "Fuel : " << fuel << " "; j = k;
				rlutil::locate(60, 30); cout << "Armor:" << armor << " ";
				for (i_c = 0; i_c <(num0 + num1 + num2); i_c++) {
					collision = hitAsteroid(*A[i_c], x, y);
					if (collision == -1) {
						armor -= 10;
						vu.setArmor(armor);
						cout << endl << "mu birader";
						rlutil::locate(60, 30); cout << "Armor:" << armor << " ";
					}
				}
				hit = hitWall(x, y);
				if (hit != -1)
					x = hit;
			}
			else if (k == rlutil::KEY_RIGHT) {
				++x; rad = 0; gotoxy(x, y); rlutil::setColor(2);  cout << '>'; rlutil::setColor(7); fuel--; rlutil::locate(45, 30); cout << "Fuel : " << fuel << " "; j = k;
				rlutil::locate(60, 30); cout << "Armor:" << armor << " ";
				hit = hitWall(x, y);
				if (hit != -1)
					x = hit;
			}  // Turn Right
			else if (k == rlutil::KEY_UP) {
				--y;  gotoxy(x, y); rlutil::setColor(2);  cout << '^'; rlutil::setColor(7); fuel--; rlutil::locate(45, 30); cout << "Fuel : " << fuel << " "; j = k;
				rlutil::locate(60, 30); cout << "Armor:" << armor << " ";
				hit = hitWall(x, y);
				if (hit != -1)
					y = hit;
			}
			else if (k == rlutil::KEY_DOWN) {
				++y; gotoxy(x, y);
				rlutil::setColor(2);
				cout << 'v';
				rlutil::setColor(7);
				fuel--;
				rlutil::locate(45, 30);
				cout << "Fuel : " << fuel << " "; j = k;
				rlutil::locate(60, 30); cout << "Armor:" << armor << " ";  //show the armor amount
				hit = hitWall(x, y);
				if (hit != -1)
					y = hit;

			}
			else 	if (k == rlutil::KEY_SPACE) { // Space to fire
				g.fire(j, x, y);
			}
			else     if (k == rlutil::KEY_ENTER) { // activate mortar
				rlutil::locate(70, 30);
				cout << "Enter the locations: ";
				cin >> morx >> mory;
				rlutil::locate(70, 30);
				cout << "                                  ";
				mor.setLoc(morx, mory);
				mor.fire(j, morx, mory);
			}
			else if (k == rlutil::KEY_ESCAPE) { rlutil::locate(76, 30); cout << "Thanks for playing!!"; menu.menu(); } // End of the game


			if (fuel == 0) { // check fuel out or not.
				for (i = 0; i < 4; i++) {          // Radiation warning
					rlutil::locate(80, 30); rlutil::setColor(4); cout << "!! OUT OF FUEL !!"; rlutil::setColor(7);
					rlutil::msleep(500);
					rlutil::locate(70, 30); cout << "                                               ";
					rlutil::msleep(500);
				}
				cout << endl;
				break;
			}

		} // end of kbhit if

	} // end of while 




}

void Map::setWalls() {
	int i;
	int *walls;

	for (i = 0; i < 117; i++) {
		rlutil::locate(0, i);
		cout << "#";
	}
	for (i = 1; i < 29; i++) {
		rlutil::locate(i, 0);
		cout << "#";
		cout << endl;
	}
	for (i = 1; i < 29; i++) {
		rlutil::locate(118, i);
		cout << "#";
	}
	for (i = 1; i < 119; i++) {
		rlutil::locate(i, 29);
		cout << "# ";
	}

	rlutil::locate(1, 30); cout << "Made by Ercan COS & Tolga KALAYCIOGLU";
}


int Map::hitWall(int x, int y) {
	int i, armor;

	if (y == 1) {
		// If Space ship hit the wall decrease armor
		armor = vu.getArmor();
		armor = armor - 10;
		vu.setArmor(armor);
		//..

		rlutil::setColor(7); rlutil::locate(x, y); cout << "#";
		rlutil::locate(x, y + 1);  rlutil::setColor(2); cout << "v";
		y++;
		for (i = 0; i < 4; i++) {          // Radiation warning
			rlutil::locate(70, 30); rlutil::setColor(4); cout << " IT is radiation area turn back to SAFE AREA!!!"; rlutil::resetColor();
			rlutil::msleep(500);
			rlutil::locate(70, 30); cout << "                                               ";
			rlutil::msleep(500);

		}
		return(y);
	}




	else if (y == 29) {
		// If Space ship hit the wall decrease armor
		armor = vu.getArmor();
		armor = armor - 10;
		vu.setArmor(armor);
		//..

		rlutil::setColor(7); rlutil::locate(x, y); cout << "#";
		rlutil::locate(x, y - 1); rlutil::setColor(2); cout << "^";
		y--;
		for (i = 0; i < 4; i++) {     // Radiation warning
			rlutil::locate(70, 30); rlutil::setColor(4); cout << " IT is radiation area turn back to SAFE AREA!!!"; rlutil::resetColor();
			rlutil::msleep(500);
			rlutil::locate(70, 30); cout << "                                               ";
			rlutil::msleep(500);

		}
		return(y);
	}

	else if (x == 1) {
		// If Space ship hit the wall decrease armor
		armor = vu.getArmor();
		armor = armor - 10;
		vu.setArmor(armor);
		//..

		rlutil::setColor(7); rlutil::locate(x, y); cout << "#";
		rlutil::setColor(2); rlutil::locate(x + 1, y); cout << ">";
		x++;
		for (i = 0; i < 4; i++) {            // Radiation warning
			rlutil::locate(70, 30); rlutil::setColor(4); cout << " IT is radiation area turn back to SAFE AREA!!!"; rlutil::resetColor();
			rlutil::msleep(500);
			rlutil::locate(70, 30); cout << "                                               ";
			rlutil::msleep(500);

		}
		return(x);
	}


	else if (x == 118) {
		// If Space ship hit the wall decrease armor
		armor = vu.getArmor();
		armor = armor - 10;
		vu.setArmor(armor);
		//..

		rlutil::setColor(7); rlutil::locate(x, y); cout << "#";
		rlutil::setColor(2); rlutil::locate(x - 1, y); cout << "<";
		x--;
		for (i = 0; i < 4; i++) {              // Radiation warning
			rlutil::locate(70, 30); rlutil::setColor(4); cout << " IT is radiation area turn back to SAFE AREA!!!"; rlutil::resetColor();
			rlutil::msleep(500);
			rlutil::locate(70, 30); cout << "                                               ";
			rlutil::msleep(500);

		}
		return(x);
	}
	else
		return(-1);

}



int Map::hitAsteroid(Asteroit& a, int x, int y) {
	int *arr;
	arr = a.getCoordinates();
	if (arr[0] == x && arr[1] == y) {
		cout << endl << "ali";
		return -1;
	}
	else
		return 0;
}