#pragma once

#include <iostream>

using namespace std;

template <typename T>
class ABQ
{
private:
	unsigned int capacity;
	unsigned int size;
	T *data;
	T *tmp;
public:

	// Constructors
	/*******************************************************
	Parameters: Either none or a default array capacity stored into
		local capacity
	Definition: Capacity set to zero (unless specified otherwise)
		size set to zero
		data array allocated memory equal to capacity size
		destructor deallocating data array memory from heap
	Return: N/A

	********************************************************/
	ABQ()
	{
		capacity = 1;
		size = 0;
		data = new T[capacity];
	}

	ABQ(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		data = new T[capacity];
	}

	~ABQ()
	{
		delete[] data;
	}

	// Getters
	/*******************************************************
	Parameters:
	Definition:
	Return: current array size (may be different from capacity)

	********************************************************/
	unsigned int getSize()
	{
		return size;
	}

	/*******************************************************
	Parameters:
	Definition:
	Return: current array capacity (may be different from size)

	********************************************************/
	unsigned int getMaxCapacity()
	{
		return capacity;
	}

	/*******************************************************
	Parameters: data to be enqueued onto dynamically allocated
		data array
	Definition: stores new data onto the back of data array.
		Doubles capacity of array if full
		(new capacity = old capacity * 2)
		increases size by one
	Return:

	********************************************************/
	void enqueue(T d)
	{
		if (capacity == size)
		{
			// double capacity
			increaseCap(capacity);
		}

		this->data[size] = d;

		size++;
	}

	/*******************************************************
	Parameters: old capacity from enqueue()
	Definition: allocates and stores data from data[] onto
		tmp[].
		Deletes data array, then resizes to new capacity size
		(new capacity = old capacity * 2)
		restores data back to data[]
		deallocates tmp[]
	Return:

	********************************************************/
	void increaseCap(int capacity)
	{
		tmp = new T[size];

		// Temporarily store content from data into tmp
		for (unsigned int i = 0; i < size; i++)
		{
			tmp[i] = data[i];
		}

		delete[] data;

		// Resize capacity
		this->capacity = capacity * 2;
		data = new T[this->capacity];

		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = tmp[i];
		}

		delete[] tmp;
	}

	/*******************************************************
	Parameters:
	Definition: Throws an error if the data array is empty
	Return: front of queue

	********************************************************/
	T peek()
	{
		if (size == 0)
		{
			throw - 1;
		}

		return data[0];
	}

	/*******************************************************
	Parameters:
	Definition: Stores front of data array into tmp array.
		Deletes front of array.
		calls shiftQueue() (shifting data one place to "left"
		if the array is empty, throws an error
	Return: array data dequeued

	********************************************************/
	T dequeue()
	{
		if (size == 0)
		{
			throw - 1;
		}
		T tmpDeq = *data;
		shiftQueue();
		size--;

		if (((double)capacity / (double)size) > 2)
		{
			// shrink capacity to half size
			decreaseCap(capacity);
		}		

		return tmpDeq;
	}

	/*******************************************************
	Parameters:
	Definition: Stores data from data[] onto tmp[].
		deletes then restores data array.
		restores data one position to the left of data array
		front of data deleted
	Return:

	********************************************************/
	void shiftQueue()
	{
		tmp = new T[size];

		int j = 0;
		for (unsigned int i = 1; i < size; i++)
		{
			tmp[j] = data[i];
			j++;
		}

		delete[] data;
		data = new T[capacity];

		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = tmp[i];
		}

		delete[] tmp;
	}

	/*******************************************************
	Parameters: old capacity from dequeue()
	Definition: Allocates memory to tmp[] onto heap.
		stores data from data[] into tmp[]
		deallocates data[], then allocates with new
		capacity size (new cap = old cap * 2)
		restores data from tmp[] to data[]
		deallocates tmp[]
	Return:

	********************************************************/
	void decreaseCap(int capacity)
	{
		tmp = new T[size];

		// Temporarily store content from data into tmp
		for (unsigned int i = 0; i < size; i++)
		{
			tmp[i] = data[i];
		}

		delete[] data;

		// Resize capacity
		this->capacity = capacity / 2;
		data = new T[this->capacity];

		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = tmp[i];
		}

		delete[] tmp;
	}
};