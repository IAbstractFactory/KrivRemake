

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
	Date* departureDate;
	Time* departureTime;
	Time* arrivalTime;
	char type[20];
	int freeSeats;

	Train() {}
	Train(int numOfTrain, const char Station[20], Date* departureDate, Time* departureTime, Time* arrivalTime, const char type[20], int freeSeats)
	{
		this->numOfTrain = numOfTrain;
		strcpy_s(this->station, Station);

		this->departureDate = departureDate;
		this->departureTime = departureTime;
		this->arrivalTime = arrivalTime;
		strcpy_s(this->type, type);
		this->freeSeats = freeSeats;
	}
	void Show()
	{
		printf("Номер поезда: %d\n", numOfTrain);
		printf("Станция: "); puts(station);
		printf("Дата отправления: %d.%d.%d\n", departureDate->day, departureDate->month, departureDate->year);
		printf("Время отправления: %d:%d\n", departureTime->hours, departureTime->minutes);
		printf("Время прибытия: %d:%d\n", arrivalTime->hours, arrivalTime->minutes);

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

	Node* Get(int n)
	{
		if (n == 0)return head;
		else if (n == count - 1)return tail;
		else
		{
			Node* f = head;
			for (int i = 0; i < n; i++)
			{
				f = f->next;
			}
			return f;
		}
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
	/*Train* info[] = {
		new Train(1241, "Черкизовская", new Date(21, 10, 2020), new Time(17, 59), new Time(17, 59), "Купе", 200) ,
		new Train(2254, "Сокольники", new Date(14, 9, 2020), new Time(15, 30), new Time(0, 30), "Общий", 60),
		new Train(5533, "Красносельская", new Date(3, 12, 2020), new Time(20, 10), new Time(20, 10), "СВ", 93),
		new Train(4223, "Комсомольская", new Date(30, 1, 2020), new Time(22, 10), new Time(22, 10), "СВ", 43),
		new Train(4343, "Лубянка", new Date(30, 1, 2020), new Time(22, 10), new Time(22, 10), "СВ", 43),
		new Train(5875, "Лубянка", new Date(24, 9, 2020), new Time(18, 0), new Time(18, 50), "Плацкарт", 113),
	};*/

	printf("%d\n", _filelength(_fileno(stream)));
	printf("%d\n", sizeof(List));
	if (_filelength(_fileno(stream)))
	{
		fseek(stream, 0, 0);;
		fread(list, sizeof(List), 1, stream);
		list->head->train.Show();
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
		printf("5 -Сохранить и выйти\n");
		key = _getch();
		system("cls");
		switch (key)
		{
		case '1':
		{
			Node* ttt = list->head;

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
			Date* date = new Date();
			printf("Укажите дату:\n");
			printf("День: ");
			scanf_s("%d", &date->day);
			printf("Месяц: ");
			scanf_s("%d", &date->month);
			printf("Год: ");
			scanf_s("%d", &date->year);
			train->departureDate = date;
			Time* time1 = new Time();
			printf("Укажите время отправления:\n");
			printf("Минуты: ");
			scanf_s("%d", &time1->minutes);
			printf("Часы: ");
			scanf_s("%d", &time1->hours);
			train->departureTime = time1;
			Time* time2 = new Time();
			printf("Укажите время прибытия:\n");
			printf("Минуты: ");
			scanf_s("%d", &time2->minutes);
			printf("Часы: ");
			scanf_s("%d", &time2->hours);
			train->arrivalTime = time2;

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

		}
		break;
		case '5':
		{
			Node* t = list->head;
			fwrite(&list, sizeof(List), 1, stream);
			printf("Записано %d", sizeof(list));
			system("pause");
			end = true;

		}
		break;
		}
		system("cls");
	}
	fclose(stream);
}


