#pragma once

#include <iostream>

using namespace std;

template <typename T>
class DynamicArray
{
private:
	int arrCapacity;
	T *tmpArray;
	T *data;
	static int numOfElements;
public:
	
	/*******************************************************
	Parameters: None
	Definition: initialize capacity to zero, set data to NULL
	Return: N/A

	********************************************************/
	DynamicArray()
	{
		arrCapacity = 0;
		data = nullptr;
	}

	/*******************************************************
	Parameters: array capacity
	Definition: store int, float, double into arrCapacity
		allocate memory onto heap with data pointer
	Return:
	********************************************************/
	DynamicArray(unsigned int c)
	{
		arrCapacity = c;
		data = new T[c];
	}

	/*******************************************************
		Parameters: data from previous obj
		Definition: copy everything from previous obj to
			current obj
		Return: N/A

	********************************************************/
	DynamicArray(const DynamicArray<T> &d)
	{
		this->arrCapacity = d.arrCapacity;
		this->numOfElements = d.numOfElements;
		data = new T[arrCapacity];
		for (int i = 0; i < d.arrCapacity; i++)
		{
			data[i] = d.data[i];
		}
	}

	/*******************************************************
	Parameters: index of array when [] operator used
	Definition: return data pointing to index provided
		Display error if index is out of bounds
	Return: N/A

	********************************************************/
	T &operator[](unsigned int index)
	{
		if ((index >= 0) && (index <= (unsigned)numOfElements))
		{
			return data[index];
		}

		else
		{
			//cout << "Error! Invalid index" << endl;
			throw runtime_error("Error! Invalid index");
		}

		return data[index];
	}

	/*******************************************************
		Parameters: previous object when = operator used
		Definition: set previous obj numElements and arrCapacity
			to current object numElements and arrCapacity
			Copy objects from previous obj to current
		Return: pointer to current obj

	********************************************************/
	DynamicArray<T> &operator=(const DynamicArray<T> &rhs)
	{
		this->numOfElements = rhs.numOfElements;
		this->arrCapacity = rhs.arrCapacity;
		
		data = new T[arrCapacity];

		for (int i = 0; i < rhs.arrCapacity; i++)
		{
			data[i] = rhs.data[i];
		}
		return *this;
	}

	/*******************************************************
	Parameters:
	Definition: deallocate data memory from heap
	Return:

	********************************************************/

	~DynamicArray()
	{
		if (data != nullptr)
		{
			delete[] data;
		}
		data = nullptr;
	}

	/*******************************************************
	Parameters:
	Definition:
	Return: data template

	********************************************************/
	const T* GetData() const
	{
		return data;
	}


	/*******************************************************
	Parameters: value to store into array
	Definition: Store values into dynamic array
		resizing and incrementing when necessary
	Return: void

	********************************************************/

	void Add(const T &data)
	{
		if (arrCapacity == 0)
		{
			numOfElements = arrCapacity;
		}

		if (arrCapacity == numOfElements)
		{
			Resize(arrCapacity + 1);
		}

		this->data[numOfElements] = data;
		numOfElements++;
		
	}

	/*******************************************************
	Parameters:
	Definition:
	Return: int total size number of elements of array

	********************************************************/

	unsigned int GetSize() const
	{
		return numOfElements;
	}

	/*******************************************************
	Parameters:
	Definition:
	Return: int total array capacity

	********************************************************/

	unsigned int GetCapacity() const
	{
		return arrCapacity;
	}

	/*******************************************************
	Parameters: An int for new size of array => data(int)
	Definition: Display older and newer capacity,
		store data into temporary array
		delete then resize array
		restore data from tmp array into data array
		assign arrCapacity to newSize
		assign numOfElements to newSize (if newSize < arrCapacity)
			or arrCapacity (if newSize > arrCapacity)
	Return: void

	********************************************************/
	void Resize(unsigned int newSize)
	{
		cout << "Resizing... old capacity: " << arrCapacity << " New capacity: " << newSize << endl;
		tmpArray = new T[arrCapacity + 1];

		for (int i = 0; i < arrCapacity; i++)
		{
			tmpArray[i] = data[i];
		}

		
		if (data != nullptr)
		{
			delete[] data;
		}
		data = new T[newSize];
		
		if (newSize < (unsigned)arrCapacity)
		{
			for (unsigned int i = 0; i < newSize; i++)
			{
				data[i] = tmpArray[i];
			}

			numOfElements = newSize;
		}

		else if (newSize > (unsigned)arrCapacity)
		{
			for (int i = 0; i < arrCapacity; i++)
			{
				data[i] = tmpArray[i];
			}

			numOfElements = arrCapacity;
		}

		else
		{
			cout << "Array already this size" << endl;
		}
		
		arrCapacity = newSize;

		delete[] tmpArray;

	}

	/*******************************************************
	Parameters: index for array
	Definition: if the request falls outside the bounds
		of the array, throw an exception
	Return: else, return data at index requested

	********************************************************/
	T &At(unsigned int index)
	{
		if ((index < 0) || (index > (unsigned)arrCapacity - 1))
		{
			throw runtime_error("Error! Invalid index");
		}
		return data[index];
	}

	/*******************************************************
	Parameters: index of current array
	Definition: remove data from index provided
		store data from curent index into a temporary index
		delete data pointer
		restore data with updated data and index
		(moving everything up an index when necessary)
	Return: void

	********************************************************/
	void Remove(unsigned int index)
	{
		if ((index >= 0) && (index <= (unsigned)arrCapacity) && ((unsigned)arrCapacity > 0))
		{
			int j = 0;

			tmpArray = new T[arrCapacity + 1];

			for (int i = 0; i < arrCapacity; i++)
			{
				if ((unsigned)i == index)				// What if last index?
				{
					i++;
				}
				tmpArray[j] = data[i];
				j++;
			}

			//arrCapacity--;
			numOfElements--;

			delete[] data;

			data = new T[arrCapacity + 1];

			for (int i = 0; i < arrCapacity; i++)
			{
				data[i] = tmpArray[i];
			}


			delete[] tmpArray;
		}
		else
		{
			throw runtime_error("Error! Invalid index");
			data = nullptr;
		}
	}
};

template <typename T> int DynamicArray<T>::numOfElements;
