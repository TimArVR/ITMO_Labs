#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>

constexpr int first_nuw_of_citizens = 100;
constexpr int first_nuw_of_wheat = 2800;
constexpr int first_area_of_city = 1000;
constexpr int number_of_rounds = 10;

struct City
{
	int citizens = first_nuw_of_citizens;
	int wheat = first_nuw_of_wheat;
	int area = first_area_of_city;
	int citizens_survived = 0;
};

struct Current_Round_Data
{
	int current_round = 1;
	int number_of_dead = 0;
	int number_of_newbies_in_the_city = 0;
	bool is_plague = false;
	int total_wheat_taked = 0;
	float wheat_eated_by_rats = 0;

};

void Start_Round_Info(City& City, Current_Round_Data& Current_Round_Data, float& rand_for_rats, int& price_for_1_acre, int& quantity_of_wheat_from_1_acre)
{
	std::cout << "\n�������� ����� ��� ������ ���������!\n��� ����������, �������� �������� ���� � ���� " 
		<< Current_Round_Data.current_round << " ������ ����������� ���������\n";
	if (Current_Round_Data.number_of_dead != 0)
	{
		std::cout << Current_Round_Data.number_of_dead << " ������� ������ � ������, � \n";
	}
	if (Current_Round_Data.number_of_newbies_in_the_city != 0)
	{
		std::cout << Current_Round_Data.number_of_newbies_in_the_city 
			<< " ������� ������� � ��� ������� �����;\n";
	}
	if (Current_Round_Data.is_plague)
	{
		std::cout << "���� ���������� �������� ���������;\n";
	}
	else
	{
		std::cout << "���� �� ����;\n";
	}
	std::cout << "��������� ������ ������ ���������� " << City.citizens << " �������;\n";
	std::cout << "�� ������� " << Current_Round_Data.total_wheat_taked << " ������� �������, �� " 
		<< quantity_of_wheat_from_1_acre << " ������ � ����;\n";
	std::cout << "����� ��������� " << static_cast<int>(City.wheat * rand_for_rats) << " ������� �������, ������� " 
		<< City.wheat << " ������ � �������;\n";
	std::cout << "����� ������ �������� " << City.area << " �����;\n";
	std::cout << "1 ��� ����� ����� ������ " << price_for_1_acre << " �������.\n";

}

void Round_Calculating(City& City, Current_Round_Data& Current_Round_Data, int& price_for_1_acre, int& quantity_of_wheat_from_1_acre, float& rand_for_rats, int& area_to_plant_by_gamer, float& proportion_of_deads, int& probability_of_plague, int& area_to_bue_by_gamer, int& wheat_to_eat_by_gamer)
{
	quantity_of_wheat_from_1_acre = rand() % 6 + 1;
	rand_for_rats =static_cast<float> (0.01 * (rand() % 8));

	Current_Round_Data.total_wheat_taked = area_to_plant_by_gamer * quantity_of_wheat_from_1_acre;
	City.wheat = City.wheat + Current_Round_Data.total_wheat_taked;
	City.wheat = City.wheat - static_cast<int>(City.wheat * rand_for_rats);


	Current_Round_Data.number_of_newbies_in_the_city = Current_Round_Data.number_of_dead / 2 + (5 - quantity_of_wheat_from_1_acre) * City.wheat / 600 + 1;
	if (Current_Round_Data.number_of_newbies_in_the_city < 0)
	{
		Current_Round_Data.number_of_newbies_in_the_city = 0;
	}
	else if (Current_Round_Data.number_of_newbies_in_the_city > 50)
	{
		Current_Round_Data.number_of_newbies_in_the_city = 50;
	}
	City.citizens = City.citizens + Current_Round_Data.number_of_newbies_in_the_city;

	probability_of_plague = rand() % 100;
	if (probability_of_plague <= 14)
	{
		City.citizens = City.citizens / 2;
		Current_Round_Data.is_plague = true;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned int>(time(NULL)));

	City City;
	Current_Round_Data Current_Round_Data;

	int price_for_1_acre = 0;
	int quantity_of_wheat_from_1_acre = 0;
	int probability_of_plague = 0;
	float rand_for_rats = 0;
	float proportion_of_deads = 0;
	float avg_deads = 0;
	
	int area_to_bue_by_gamer = 0;
	int area_to_sell_by_gamer = 0;
	int wheat_to_eat_by_gamer = 0;
	int area_to_plant_by_gamer = 0;

	bool isProportionWorked = false;
	bool save_and_exit = false;
	bool flag_for_exitgame = true;
	bool flag_for_savegame=true;

	while (flag_for_savegame)
	{
		std::cout << "������ ��������� ����� ���������� ����? \n�� - �� ���������� ������ � ������������ ������\n��� - �������� ����� ����\n";
		std::string yes_no = "��";
		std::cin >> yes_no;
		if (yes_no == "���") 
		{
			flag_for_savegame = false;
			break;
		}
		else if (yes_no == "��") 
		{
			std::ifstream filein("savegame.txt");

			if (!filein.is_open()) 
			{
				std::cout << "������ ��������� � ���������� ������!";
				flag_for_savegame = false;

				break;
			}
			else 
			{
				filein >> City.area >> City.citizens >> City.citizens_survived
					>> City.wheat >> Current_Round_Data.current_round
					>> Current_Round_Data.is_plague >> Current_Round_Data.number_of_dead
					>> Current_Round_Data.number_of_newbies_in_the_city
					>> Current_Round_Data.total_wheat_taked >> Current_Round_Data.wheat_eated_by_rats
					>> price_for_1_acre >> quantity_of_wheat_from_1_acre
					>> avg_deads>> rand_for_rats;

				filein.close();

				++Current_Round_Data.current_round;
				std::cout<<"\nC���������� ���� ���������:\n";
				Start_Round_Info(City, Current_Round_Data, rand_for_rats, price_for_1_acre, quantity_of_wheat_from_1_acre);
				flag_for_savegame = false;

				break;
			}					
		}
		if (flag_for_savegame==false) 
		{
			break;
		}
	}

	if (Current_Round_Data.current_round == 1)
	{
		std::cout << "\n���� Hammurabi ��������!\n��� ��� 1 ��� ���������!\n� ������ ��������� 100 �������.\n� �������� ������ 2800 ������� �������.\n����� �������� 1000 ����� �����.\n\n\n";
	}

	for (Current_Round_Data.current_round; Current_Round_Data.current_round < number_of_rounds;)
	{
		Current_Round_Data.is_plague = false;

		std::cout << "\n��� ���������, ����������?\n";
		price_for_1_acre = rand() % 10 + 17;

		while (true)
		{
			std::cout << "������� ����� ����� ����������� ������? ";
			std::cin >> area_to_bue_by_gamer;

			if (area_to_bue_by_gamer < 0 || City.wheat < area_to_bue_by_gamer * price_for_1_acre)
			{
				std::cout << "�, ����������, ������ ���! � ��� ������ " << City.wheat << " ������� �������!\n";
			}
			else
			{
				City.area = City.area + area_to_bue_by_gamer;
				City.wheat = City.wheat - area_to_bue_by_gamer * price_for_1_acre;
				break;
			}
		}

		while (true)
		{
			std::cout << "������� ����� ����� ����������� �������? ";
			std::cin >> area_to_sell_by_gamer;
			if (area_to_sell_by_gamer < 0 || area_to_sell_by_gamer >City.area)
			{
				std::cout << "�, ����������, ������ ���! � ��� ������ " << City.area << " ����� �������!\n";
			}
			else
			{
				City.area = City.area - area_to_sell_by_gamer;
				City.wheat = City.wheat + area_to_sell_by_gamer * price_for_1_acre;
				break;
			}
		}

		while (true)
		{
			std::cout << "������� ������� ������� ����������� ������? ";
			std::cin >> wheat_to_eat_by_gamer;
			if (wheat_to_eat_by_gamer < 0 || wheat_to_eat_by_gamer>City.wheat)
			{
				std::cout << "�, ����������, ������ ���! � ��� �������� ������ " << City.wheat << " ������� �������!\n";
			}
			else
			{
				City.wheat = City.wheat - wheat_to_eat_by_gamer;

				if (wheat_to_eat_by_gamer / 20 >= City.citizens)
				{
					City.citizens_survived = City.citizens;
					Current_Round_Data.number_of_dead = 0;
				}
				else
				{
					City.citizens_survived = wheat_to_eat_by_gamer / 20;
					Current_Round_Data.number_of_dead = City.citizens - City.citizens_survived;

				}

				break;
			}
		}
		proportion_of_deads = static_cast < float>(1.0 * Current_Round_Data.number_of_dead / City.citizens);

		if (proportion_of_deads > 0.45)
		{
			std::cout << "\n\n����� ����!\n�� �������������� ���������, � ��� �� ������ ������ ����� 45% �������. �� ���������! \n";
			
			return EXIT_SUCCESS;
		}

		City.citizens = City.citizens_survived;

		while (true)
		{
			std::cout << "������� ����� ����� ����������� �������? ";
			std::cin >> area_to_plant_by_gamer;

			if (area_to_plant_by_gamer < 0 || area_to_plant_by_gamer>City.area)
			{
				std::cout << "�, ����������, ������ ���! � ��� ������ " << City.area << " ����� �����!\n";
			}
			else if (area_to_plant_by_gamer > City.citizens * 10)
			{
				std::cout << "�, ����������, ������ ���! � ��� �� ������ �������. � ��� ����� " << City.citizens << ", ����� ������� �����!\n";
			}
			else if (City.wheat < area_to_plant_by_gamer * 0.5)
			{
				std::cout << "�, ����������, ������ ���! � ��� ������ " << City.wheat << " ������� �������, ����� ������� �����!\n";
			}
			else
			{
				City.wheat = City.wheat - static_cast<int>(area_to_plant_by_gamer * 0.5);

				break;
			}
		}

		Round_Calculating(City, Current_Round_Data, price_for_1_acre, quantity_of_wheat_from_1_acre, rand_for_rats, area_to_plant_by_gamer, proportion_of_deads, probability_of_plague, area_to_bue_by_gamer, wheat_to_eat_by_gamer);
				
		avg_deads = avg_deads + proportion_of_deads;

		std::cout << "\n";
		
		std::ofstream fileout ("savegame.txt");
		
		if (fileout.is_open())
		{
			fileout << City.area << "\n" << City.citizens << "\n" << City.citizens_survived
				<< "\n" << City.wheat << "\n" << Current_Round_Data.current_round
				<< "\n" << Current_Round_Data.is_plague << "\n" << Current_Round_Data.number_of_dead
				<< "\n" << Current_Round_Data.number_of_newbies_in_the_city << "\n"
				<< Current_Round_Data.total_wheat_taked << "\n" << Current_Round_Data.wheat_eated_by_rats
				<< "\n" << price_for_1_acre << "\n" << quantity_of_wheat_from_1_acre
				<< "\n" << avg_deads << "\n"<< rand_for_rats<<"\n";

			fileout.close();
		}
		else
		{
			std::cout << "������ ������ � ����!";
		}
		
		++Current_Round_Data.current_round;

		Start_Round_Info(City, Current_Round_Data, rand_for_rats, price_for_1_acre, quantity_of_wheat_from_1_acre);
		
		while (flag_for_exitgame)
		{
			std::cout << "\n�� ������ ����� �� ����?\n�� - �� ������� �� ����, ��� ���� ������� �������� ����� ��������\n��� - ������� � ��������� �����\n";
			std::string yes_no_2 = "���";
			std::cin >> yes_no_2;
			if (yes_no_2 == "��")
			{
				save_and_exit = true;
				flag_for_exitgame = false;
				break;
			}
			else if (yes_no_2 == "���")
			{
				break;
			}
			else 
			{
				std::cout << "\n������� ���������� �������� \"��\" ��� \"���\"\n";
			}
		}
		if (!flag_for_exitgame)
		{
			break;
		}

	}

	while (!save_and_exit)
	{	
		if (!isProportionWorked)
		{
			float p = avg_deads / (number_of_rounds-1);//-1 because we do not have any deads in first year
			float l = static_cast<float>(1.0 * City.area / City.citizens);
			if (p > 0.33 && l < 7)
			{
				std::cout << "\n��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������. ������ �� ��������� ������� ������ ������������� � ��������!\n";
				break;
			}
			else if (p > 0.10 && l < 9)
			{
				std::cout << "\n�� ������� �������� �����, ������� ������ � ����� ��������. ����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������!\n";
				break;
			}
			else if (p > 0.03 && l < 10)
			{
				std::cout << "\n�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����!\n";
				break;
			}
			else
			{
				std::cout << "\n����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����!\n";
				break;
			}
	}
	}
	
	return EXIT_SUCCESS;
}