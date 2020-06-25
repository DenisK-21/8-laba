#include <iostream>
#include<thread>
#include<chrono>
#include <ctime>
#include<vector>
#include<mutex>
std::mutex mtx;
void Odd_even_sort(int* array, int* array_min, const int i_min, const int a, const int b)
{

	bool sort_flag = false;
	while (!sort_flag)
	{
		sort_flag = true;

		for (int i = a + 1; i <= b - 2; i = i + 2)
		{
			if (array[i] > array[i + 1])
			{
				std::swap(array[i], array[i + 1]);
				sort_flag = false;
			}
		}

		for (int i = a; i <= b - 2; i = i + 2)
		{
			if (array[i] > array[i + 1])
			{
				std::swap(array[i], array[i + 1]);
				sort_flag = false;
			}
		}

	}
	array_min[i_min] = array[a];
	mtx.lock();
	std::cout << "№ Thread  " << i_min << " and id " << std::this_thread::get_id() << std::endl;
	std::cout << "min number  " << array_min[i_min] << std::endl;
	std::cout << std::endl;
	mtx.unlock();

}

void Print(int* array, int& numder_array)
{

	for (size_t i = 0; i < numder_array; i++)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < numder_array; i++)
	{

		std::cout << array[i] << "\t";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}


int main()
{
	std::cout << "Hello! enter the size of the array and the number of threads" << std::endl;
	int numder_array = 0;
	int numder_threads = 0;
	std::cout << "enter the size of the array  ";
	std::cin >> numder_array;
	int* array = new int[numder_array]; // Кол-во элементов

	srand(time(0));
	for (size_t i = 0; i < numder_array; i++)
	{
		array[i] = rand() % 50;

	}
	if (numder_array < 20)
		Print(array, numder_array);
	std::cout << "enter the number of threads  ";
	std::cin >> numder_threads;
	int* array_min = new int[numder_threads];
	std::vector <std::thread> myThreads(numder_threads); //// Кол-во потоков
	int elements_in_one_thread = 0; // узнать сколько элементов будет обрабатываться в одном потоке первоначально, не считая последнего, если ост не равен 0
	if (numder_array % numder_threads != 0)
	{
		elements_in_one_thread = numder_array / numder_threads + 1;
	}
	else
	{
		elements_in_one_thread = numder_array / numder_threads;
	}

	for (size_t i = 0; i < numder_threads; i++)
	{
		if (i == numder_threads - 1)
			myThreads[i] = std::thread(Odd_even_sort, std::ref(array), std::ref(array_min), i, i * elements_in_one_thread, numder_array);
		else
			myThreads[i] = std::thread(Odd_even_sort, std::ref(array), std::ref(array_min), i, i * elements_in_one_thread, elements_in_one_thread * (i + 1));
	}


	for (size_t i = 0; i < numder_threads; i++)
	{
		myThreads[i].join();

	}

	//Print(array, numder_array);
	for (int i = 0; i < numder_threads; i++)
	{
		for (int j = 0; j < numder_threads - 1; j++)
		{
			if (array_min[j] > array_min[j + 1])
			{
				std::swap(array_min[j], array_min[j + 1]);
			}
		}
	}

	std::cout << "the minimum number of this array  " << array_min[0] << std::endl;
}
