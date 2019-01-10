#include <iostream>
#define numsims 200000
using namespace std;


int main()
{
	int x; // Flapdoodle's x-axis position on the island
	int y; // Flapdoodle's y-axis position on the island
	int direction, numsteps, lastvisit;
	int ThirstDeath = 0;
	int DrowningDeath = 0;
	int CannibalsDeath = 0;
	int HungerDeath = 0;
	int Success = 0;
	int S2Success = 0; // Steps to success
	for (int i = 0; i < numsims; i++) {
		// reset simulation variables and Flapdoodle's position
		x = 0;
		y = 0;
		numsteps = 0;
		lastvisit = 0;
		bool dead = false;
		while (dead == false) {

			direction = rand() % 4 + 1; // gives random int 1 thru 4
			switch (direction) {
			case 1: // North
				y++; break;
			case 2: // East
				x++; break;
			case 3: // South
				y--; break;
			case 4: // West
				x--; break;
			default:
				break;
			}
			numsteps++;

			// The lack of 'else' statements with each 'if' is deliberate,
			// to catch the possibility of two fates occuring at once.

			if (x > 10 || y > 10 || x < -10 || y < -10) { // fell off the island into the ocean
				DrowningDeath++; // expect ~40%
				dead = true;
			}
			if (x == 2 && y == -4) { // cannibals! nom nom
				CannibalsDeath++;
				dead = true;
			}
			if (x == -3 && y == -3) { // spring visited! Alleviate thirst
				lastvisit = numsteps;
			}
			if (numsteps - lastvisit == 100) { // 100 steps without water
				ThirstDeath++;
				dead = true;
			}
			if (numsteps >= 300) { // 300 steps without reaching airport
				dead = true;
				HungerDeath++;
			}
			if (x == 6 && y == 7) { // airport reached! fly away
				Success++;
				dead = true;
				// Though humanly illogical, this is how the loop stops
				// Perhaps Flapdoodle crashed his plane again after leaving the airport
				S2Success = S2Success + numsteps;
			}
		}
	}
	cout << "Probability of each of Fearless Flapdoodle's possible fates: " << endl << endl;
	cout << "Death by drowning in ocean : " << (double)DrowningDeath / numsims << endl;
	cout << "Eaten by cannibals : " << (double)CannibalsDeath / numsims << endl;
	cout << "Death of thirst : " << (double)ThirstDeath / numsims << endl;
	cout << "Starving to death : " << (double)HungerDeath / numsims << endl;
	cout << "Number of fates: " << DrowningDeath + CannibalsDeath + ThirstDeath + HungerDeath + Success << endl;
	cout << endl;
	cout << "The probability of Flapdoodle making it off the island is " << (double)Success / numsims;
	cout << endl;
	cout << "On average, a successful walk will require " << (double)S2Success / Success << " steps";

	system("pause");
	return 0;
}
