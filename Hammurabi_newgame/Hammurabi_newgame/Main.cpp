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
	std::cout << "\nНАСТУПИЛ НОВЫЙ ГОД ТВОЕГО ПРАВЛЕНИЯ!\nМой повелитель, соизволь поведать тебе в году " 
		<< Current_Round_Data.current_round << " твоего высочайшего правления\n";
	if (Current_Round_Data.number_of_dead != 0)
	{
		std::cout << Current_Round_Data.number_of_dead << " человек умерли с голоду, и \n";
	}
	if (Current_Round_Data.number_of_newbies_in_the_city != 0)
	{
		std::cout << Current_Round_Data.number_of_newbies_in_the_city 
			<< " человек прибыли в наш великий город;\n";
	}
	if (Current_Round_Data.is_plague)
	{
		std::cout << "Чума уничтожила половину населения;\n";
	}
	else
	{
		std::cout << "Чумы не было;\n";
	}
	std::cout << "Население города сейчас составляет " << City.citizens << " человек;\n";
	std::cout << "Мы собрали " << Current_Round_Data.total_wheat_taked << " бушелей пшеницы, по " 
		<< quantity_of_wheat_from_1_acre << " бушеля с акра;\n";
	std::cout << "Крысы истребили " << static_cast<int>(City.wheat * rand_for_rats) << " бушелей пшеницы, оставив " 
		<< City.wheat << " бушеля в амбарах;\n";
	std::cout << "Город сейчас занимает " << City.area << " акров;\n";
	std::cout << "1 акр земли стоит сейчас " << price_for_1_acre << " бушелей.\n";

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
		std::cout << "Хотите загрузить ранее сохранённую игру? \nда - вы продолжите играть с сохраненного раунда\nнет - начнется новая игра\n";
		std::string yes_no = "да";
		std::cin >> yes_no;
		if (yes_no == "нет") 
		{
			flag_for_savegame = false;
			break;
		}
		else if (yes_no == "да") 
		{
			std::ifstream filein("savegame.txt");

			if (!filein.is_open()) 
			{
				std::cout << "Ошибка обращения к сохранённым данным!";
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
				std::cout<<"\nCохраненная игра загружена:\n";
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
		std::cout << "\nИгра Hammurabi началась!\nЭто ваш 1 год правления!\nВ городе проживает 100 человек.\nВ закромах города 2800 бушелей пшеницы.\nГород занимает 1000 акров земли.\n\n\n";
	}

	for (Current_Round_Data.current_round; Current_Round_Data.current_round < number_of_rounds;)
	{
		Current_Round_Data.is_plague = false;

		std::cout << "\nЧто пожелаешь, повелитель?\n";
		price_for_1_acre = rand() % 10 + 17;

		while (true)
		{
			std::cout << "Сколько акров земли повелеваешь купить? ";
			std::cin >> area_to_bue_by_gamer;

			if (area_to_bue_by_gamer < 0 || City.wheat < area_to_bue_by_gamer * price_for_1_acre)
			{
				std::cout << "О, повелитель, пощади нас! У нас только " << City.wheat << " бушелей пшеницы!\n";
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
			std::cout << "Сколько акров земли повелеваешь продать? ";
			std::cin >> area_to_sell_by_gamer;
			if (area_to_sell_by_gamer < 0 || area_to_sell_by_gamer >City.area)
			{
				std::cout << "О, повелитель, пощади нас! У нас только " << City.area << " акров имеется!\n";
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
			std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
			std::cin >> wheat_to_eat_by_gamer;
			if (wheat_to_eat_by_gamer < 0 || wheat_to_eat_by_gamer>City.wheat)
			{
				std::cout << "О, повелитель, пощади нас! У нас осталось только " << City.wheat << " бушелей пшеницы!\n";
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
			std::cout << "\n\nКонец игры!\nВы некомпетентный правитель, у вас от голода умерло более 45% граждан. Вы проиграли! \n";
			
			return EXIT_SUCCESS;
		}

		City.citizens = City.citizens_survived;

		while (true)
		{
			std::cout << "Сколько акров земли повелеваешь засеять? ";
			std::cin >> area_to_plant_by_gamer;

			if (area_to_plant_by_gamer < 0 || area_to_plant_by_gamer>City.area)
			{
				std::cout << "О, повелитель, пощади нас! У нас только " << City.area << " акров земли!\n";
			}
			else if (area_to_plant_by_gamer > City.citizens * 10)
			{
				std::cout << "О, повелитель, пощади нас! У нас не хватит жителей. У нас всего " << City.citizens << ", чтобы засеять земли!\n";
			}
			else if (City.wheat < area_to_plant_by_gamer * 0.5)
			{
				std::cout << "О, повелитель, пощади нас! У нас только " << City.wheat << " бушелей пшеницы, чтобы засеять земли!\n";
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
			std::cout << "Ошибка записи в файл!";
		}
		
		++Current_Round_Data.current_round;

		Start_Round_Info(City, Current_Round_Data, rand_for_rats, price_for_1_acre, quantity_of_wheat_from_1_acre);
		
		while (flag_for_exitgame)
		{
			std::cout << "\nВы хотите выйти из игры?\nда - вы выйдете из игры, при этом текущий прогресс будет сохранен\nнет - перейти в следующий раунд\n";
			std::string yes_no_2 = "нет";
			std::cin >> yes_no_2;
			if (yes_no_2 == "да")
			{
				save_and_exit = true;
				flag_for_exitgame = false;
				break;
			}
			else if (yes_no_2 == "нет")
			{
				break;
			}
			else 
			{
				std::cout << "\nВведите корректное значение \"да\" или \"нет\"\n";
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
				std::cout << "\nИз-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании!\n";
				break;
			}
			else if (p > 0.10 && l < 9)
			{
				std::cout << "\nВы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем!\n";
				break;
			}
			else if (p > 0.03 && l < 10)
			{
				std::cout << "\nВы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова!\n";
				break;
			}
			else
			{
				std::cout << "\nФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше!\n";
				break;
			}
	}
	}
	
	return EXIT_SUCCESS;
}