#include <iostream>
#include <ctime>
using namespace std;

struct Dice_parameters
{
	int count_of_throws;
	int type_of_bone;
	int modif;
};

int dice (Dice_parameters * pointer_to_struct, int num_of_attempts)
{
		int random_number = 0;

		for (int i = 0; i <= num_of_attempts; i++)
		{
			for (int j = 0; j < pointer_to_struct[i].count_of_throws; j++)
			{
				random_number += 1 + rand() % pointer_to_struct[i].type_of_bone;
			}
			random_number += pointer_to_struct[i].modif;		
		}

		return random_number;
}


int main()
{
	srand (static_cast<int>(time(NULL)));

	//////////////////////////// 1d6+0
	//const int NUM_OF_ATTEMPTS = 1;
	//Dice_parameters test_dice [NUM_OF_ATTEMPTS];

	//test_dice[0].count_of_throws = 1;
	//test_dice[0].type_of_bone = 6;
	//test_dice[0].modif = 0;

	//for (int i = 0; i < 1000; i++)
	//{
	//	cout << dice(test_dice, 0) << endl;
	//}

	//////////////////////////// 2d6+0
	//const int NUM_OF_THROWS = 1;
	//Dice_parameters test_dice[NUM_OF_ATTEMPTS];

	//test_dice[0].count_of_throws = 2;
	//test_dice[0].type_of_bone = 6;
	//test_dice[0].modif = 0;

	//for (int i = 0; i < 1000; i++)
	//{
	//	cout << dice(test_dice, 0) << endl;
	//}

	////////////////////////// 3d6+0
	//const int NUM_OF_THROWS = 1;
	//Dice_parameters test_dice[NUM_OF_ATTEMPTS];

	//test_dice[0].count_of_throws = 3;
	//test_dice[0].type_of_bone = 6;
	//test_dice[0].modif = 0;

	//for (int i = 0; i < 1000; i++)
	//{
	//	cout << dice(test_dice, 0) << endl;
	//}
	
	//////////////////////////// 1d10+0
	//const int NUM_OF_THROWS = 1;
	//Dice_parameters test_dice[NUM_OF_ATTEMPTS];

	//test_dice[0].count_of_throws = 1;
	//test_dice[0].type_of_bone = 10;
	//test_dice[0].modif = 0;


	//for (int i = 0; i < 1000; i++)
	//{
	//	cout << dice(test_dice, 0) << endl;
	//}

	//////////////////////////// 2d10+0
	//const int NUM_OF_THROWS = 1;
	//Dice_parameters test_dice[NUM_OF_ATTEMPTS];

	//test_dice[0].count_of_throws = 2;
	//test_dice[0].type_of_bone = 10;
	//test_dice[0].modif = 0;


	//for (int i = 0; i < 1000; i++)
	//{
	//	cout << dice(test_dice, 0) << endl;
	//}
	
	//////////////////////////// 3d10+0
	const int NUM_OF_ATTEMPTS = 1;
	Dice_parameters test_dice[NUM_OF_ATTEMPTS];

	test_dice[0].count_of_throws = 3;
	test_dice[0].type_of_bone = 10;
	test_dice[0].modif = 0;

	for (int i = 0; i < 10; i++)
	{
		cout << dice(test_dice, 0) << endl;
	}

	return EXIT_SUCCESS;
}
