#pragma once

#include <iostream>

using namespace std;

template <typename T>
class ABS
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

	ABS()
	{
		capacity = 1;
		size = 0;
		data = new T[capacity];
	}

	ABS(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		data = new T[capacity];
	}

	~ABS()
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
	Parameters: data to be pushed onto dynamically allocated
		data array
	Definition: stores new data onto the back of data array.
		Doubles capacity of array if full
		(new capacity = old capacity * 2)
		increases size by one
	Return:

	********************************************************/
	void push(T d)
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
	Parameters: old capacity from push()
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
	Return: back of stack

	********************************************************/
	T peek()
	{
		if (size == 0)
		{
			throw - 1;
		}

		return data[size - 1];
	}

	/*******************************************************
	Parameters:
	Definition: Stores back of data array into tmp array.
		Deletes back of array.
		if the array is empty, throws an error
	Return: array data dequeued

	********************************************************/
	T pop()
	{
		if (size == 0)
		{
			throw - 1;
		}

		size--;
		T tmpPop = data[size];


		if (((double)capacity / (double)size) > 2)
		{
			// shrink capacity to half size
			decreaseCap(capacity);
		}		

		return tmpPop;
	}

	/*******************************************************
	Parameters: old capacity from pop()
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