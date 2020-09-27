

#include <iostream>
#include<Windows.h>
#include<conio.h>
#include<io.h>
struct Date
{
	int day;
	int month;
	int year;
	Date() {}
	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	Date& operator=(Date& date)
	{
		this->day = date.day;
		this->month = date.month;
		this->year = date.year;
		return *this;
	}
	bool operator==(Date date)
	{
		return day == date.day && month == date.month && year == date.year;
	}
};
struct Time
{

	int minutes;
	int hours;
	Time() {}
	Time(int h, int m)
	{
		minutes = m;
		hours = h;
	}
	Time& operator=(Time time)
	{
		this->minutes = time.minutes;
		this->hours = time.hours;
		return *this;
	}
	bool operator==(Time time)
	{
		return minutes == time.minutes && hours == time.hours;
	}
	bool operator<(Time time)
	{
		if (hours < time.hours)
		{
			return true;
		}
		else if (hours > time.hours)
		{
			return false;
		}
		else
		{
			if (minutes < time.minutes)
			{
				return true;
			}
			else return false;
		}
	}
	bool operator>(Time time)
	{
		return !(*this < time);
	}
};
struct Train
{
	int numOfTrain;
	char station[20];

	int day;
	int month;

	int departureTimeMinutes;
	int departureTimeHours;

	int arrivalTimeMinutes;
	int arrivalTimeHours;

	char type[20];
	int freeSeats;

	Train() {}
	Train(int numOfTrain, const char Station[20], int day, int month, int departureTimeHours, int departureTimeMinutes, int arrivalTimeHours, int arrivalTimeMinutes, const char type[20], int freeSeats)
	{
		this->numOfTrain = numOfTrain;
		strcpy_s(this->station, Station);

		this->day = day;
		this->month = month;
		this->departureTimeMinutes = departureTimeMinutes;
		this->departureTimeHours = departureTimeHours;

		this->arrivalTimeMinutes = arrivalTimeMinutes;
		this->arrivalTimeHours = arrivalTimeHours;
		strcpy_s(this->type, type);
		this->freeSeats = freeSeats;
	}
	void Show()
	{
		printf("Номер поезда: %d\n", numOfTrain);
		printf("Станция: "); puts(station);
		printf("Дата отправления: ");
		if (day < 10)
		{
			if (month < 10)
				printf("0%d.0%d\n", day, month);
			else
				printf("0%d.%d\n", day, month);
		}
		else
		{
			if (month < 10)
				printf("%d.0%d\n", day, month);
			else
				printf("%d.%d\n", day, month);
		}


		printf("Время отправления: ");
		if (departureTimeHours < 10)
		{
			if (departureTimeMinutes < 10)
				printf("0%d:0%d\n", departureTimeHours, departureTimeMinutes);
			else
				printf("0%d:%d\n", departureTimeHours, departureTimeMinutes);
		}
		else
		{
			if (departureTimeMinutes < 10)
				printf("%d:0%d\n", departureTimeHours, departureTimeMinutes);
			else
				printf("%d:%d\n", departureTimeHours, departureTimeMinutes);
		}
		printf("Время прибытия: ");
		if (arrivalTimeHours < 10)
		{
			if (arrivalTimeMinutes < 10)
				printf("0%d:0%d\n", arrivalTimeHours, arrivalTimeMinutes);
			else
				printf("0%d:%d\n", arrivalTimeHours, arrivalTimeMinutes);
		}
		else
		{
			if (arrivalTimeMinutes < 10)
				printf("%d:0%d\n", arrivalTimeHours, arrivalTimeMinutes);
			else
				printf("%d:%d\n", arrivalTimeHours, arrivalTimeMinutes);
		}




		printf("Категория: "); puts(type);

		printf("Свободных мест: %d\n", freeSeats);
	}
};
struct Node
{
	Train train;
	Node* next;
	Node* prev;
	Node(Train train)
	{
		this->train = train;
	}

};
struct List
{
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

	Node* Get(int num)
	{
		Node* f = head;
		for (int i = 0; i < num; i++)
		{
			f = f->next;
		}
		return f;
	}
	void Assign(int id, Train tr)
	{
		Node* f = head;
		for (int i = 0; i < id; i++)
			f = f->next;
		f->train = tr;
	}
	void Sort()
	{
		for (int i = 0; i < count - 1; i++)
		{

			for (int j = count - 1; j > i; j--)
			{

				if (strcmp(Get(j)->train.station, Get(j - 1)->train.station) < 0)
				{
					Swap(j, j - 1);



				}

			}

		}
	}
	void SortTime()
	{
		for (int i = 0; i < count - 1; i++)
		{

			for (int j = count - 1; j > i; j--)
			{
				if (strcmp(Get(j)->train.station, Get(j - 1)->train.station) < 0)
				{
					if (Get(j)->train.departureTimeHours < Get(j - 1)->train.departureTimeHours)
					{
						Swap(j, j - 1);



					}
					else if (Get(j)->train.departureTimeHours == Get(j - 1)->train.departureTimeHours)
					{
						if (Get(j)->train.departureTimeMinutes < Get(j - 1)->train.departureTimeMinutes)
							Swap(j, j - 1);

					}
				}
			}

		}
	}
	void Swap(int id1, int id2)
	{
		Node* t = head;
		Node* n = head;
		for (int i = 0; i < id1; i++)
		{
			t = t->next;
		}
		for (int i = 0; i < id2; i++)
		{
			n = n->next;
		}
		Train tr = n->train;
		n->train = t->train;
		t->train = tr;
	}

	bool Remove(int num)
	{
		Node* t = head;
		int k = 0;
		bool success = false;
		while (k < count)
		{
			if (t->train.numOfTrain == num) { success = true; break; };
			k++;
			t = t->next;
		}
		if (success)
			if (k != 0 && k != count - 1)
			{

				t->next->prev = t->prev;
				t->prev->next = t->next;
				delete t;
				count--;
				return success;
			}
			else
			{
				if (k != 0)
					tail = tail->prev;
				else
					head = head->next;
				delete t;
				count--;
				return success;
			}
		return success;
	}
	void Add(Train train)
	{
		Node* node = new Node(train);
		if (!count)
		{
			head = node;
		}
		else
		{
			tail->next = node;
			node->prev = tail;

		}
		tail = node;
		count++;

	}
};
int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* stream;
	const char* fileName = "information.txt";
	fopen_s(&stream, fileName, "rb+");
	List* list = new List();
	Train* info[] = {
		new Train(1241, "Черкизовская",      21,10,16,2,17,20                              ,"Купе", 200) ,
		new Train(2254, "Сокольники",        21,10,18,40,19,0                             , "Общий", 60),
		new Train(2253, "Сокольники",        21,10,21,40,22,0                             , "Общий", 60),
		new Train(5533, "Красносельская",    21,10,22,1,22,40                              , "СВ", 93),
		new Train(4223, "Комсомольская",     21,10,14,30,22,40                              , "СВ", 43),
		new Train(4343, "Лубянка",           20,10,2,33,22,40                              , "СВ", 43),
		new Train(5875, "Лубянка" ,          21,10,4,50,22,40                             ,"Плацкарт", 113),
	};
	int length = _filelength(_fileno(stream)) / sizeof(Train);
	//printf("%d", length);
	/*for (int i = 0; i < 7; i++)
	{
		fseek(stream, sizeof(Train) * i, 0);
		fwrite(info[i], sizeof(Train), 1, stream);
	}*/
	for (int i = 0; i < length; i++)
	{
		fseek(stream, sizeof(Train) * i, 0);
		Train* tr = new Train();
		fread(tr, sizeof(Train), 1, stream);
		list->Add(*tr);


	}




	int key;
	bool end = false;
	while (!end)
	{

		printf("Выберите действие\n");

		printf("1 - Посмотреть поезда\n");
		printf("2 - Добавить поезд\n");
		printf("3 - Удалить поезд\n");
		printf("4 - Найти поезд\n");
		printf("5 - Сохранить и выйти\n");
		key = _getch();
		system("cls");
		switch (key)
		{
		case '1':
		{

			Node* ttt = list->head;
			list->Sort();
			list->SortTime();
			for (int i = 0; i < list->count; i++)
			{
				ttt->train.Show();
				printf("\n\n");
				ttt = ttt->next;;

			}
			system("pause");
		}
		break;
		case '2':
		{
			Train* train = new Train();
			printf("Укажите номер поезда: ");
			scanf_s("%d", &train->numOfTrain);
			printf("Укажите названи города: ");
			gets_s(train->station);
			gets_s(train->station);

			printf("Укажите дату:\n");
			printf("День: ");
			scanf_s("%d", &train->day);
			printf("Месяц: ");
			scanf_s("%d", &train->month);


			printf("Укажите время отправления:\n");
			printf("Часы: ");
			scanf_s("%d", &train->departureTimeHours);
			printf("Минуты: ");
			scanf_s("%d", &train->departureTimeMinutes);


			printf("Укажите время прибытия:\n");
			printf("Часы: ");
			scanf_s("%d", &train->arrivalTimeHours);
			printf("Минуты: ");
			scanf_s("%d", &train->arrivalTimeMinutes);

			printf("Укажите тип поезда(купе,общий,плацкарт,СВ): ");
			gets_s(train->type);
			gets_s(train->type);

			printf("Укажите количество мест: ");
			scanf_s("%d", &train->freeSeats);
			list->Add(*train);
		}


		break;
		case '3':
		{
			printf("Введите номер поезда: ");
			int number;
			scanf_s("%d", &number);

			if (!list->Remove(number))
			{
				printf("Поезда с таким номером не существует!\n");

			}
			else
				printf("Удалено!\n");
			system("pause");
		}
		break;
		case '4':
		{
			list->Get(4)->train.Show();
			system("pause");
		}
		break;
		case '5':
		{
			fclose(stream);
			fopen_s(&stream, fileName, "wb+");
			Node* t = list->head;
			for (int i = 0; i < list->count; i++)
			{
				fseek(stream, i * sizeof(Train), 0);

				fwrite(t, sizeof(Train), 1, stream);
				t = t->next;

			}

			printf("Записано %d", list->count);
			system("pause");
			end = true;

		}
		break;
		}
		system("cls");
	}
	fclose(stream);
}


