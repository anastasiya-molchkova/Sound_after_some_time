/* Написать программу-таймер, которая, по истечении заданного промежутка времени (который вводит пользователь), 
выдаёт звуковой сигнал. */

#include <iostream>
#include <clocale>  // для кириллицы
#include <chrono>   // для std::chrono

using std::cout; using std::cin; using std::endl;

// класс с функцией счётчика времени из 129 урока
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> m_beg;  // начало временного интервала
public:
	Timer() : m_beg(clock_t::now())   // при создании объекта класса начало временного интервала определяем как "сейчас"
	{
	}
	void reset() // метод "перезагрузки", когда опять засекаем время
	{
		m_beg = clock_t::now();
	}
	double elapsed() const // метод считает пройденное время от начала временного интервала
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

// получаем от пользователя натуральное число
unsigned get_number()
{
	int answer;
	cin >> answer;
	while (cin.fail() || (answer < 0))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Вы ввели нечто некорректное, введите целое положительное число: ";
		cin >> answer;
	}
	return static_cast<unsigned>(answer);
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // для вывода сообщений на кириллице

	while (true)
	{
		cout << "Введите временной интервал (в секундах): ";
		unsigned time_in_seconds = get_number();
		Timer t; // засекаем время, создавая объект класса Timer
		// ничего не делаем, пока не прошло нужное время:
		do {} while (t.elapsed() < time_in_seconds);
	    cout << "\a" << "Время вышло!" << endl << endl;
		// "\а" - и есть стандартный звучок
	}
	return 0;
}