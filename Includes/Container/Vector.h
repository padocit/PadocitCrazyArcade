#pragma once

#pragma warning (disable : 4251)

#include <iostream>

template <typename T>
class Vector
{
public:
	Vector()
		: capacity(2)
	{
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	~Vector()
	{
		if (data != nullptr)
		{
			delete[] data;
		}
	}

	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			Resize(capacity * 2);
		}

		data[size] = value;
		size++;
	}

	void PushBack(T&& value)
	{
		if (size >= capacity)
		{
			Resize(capacity * 2);
		}

		data[size] = std::move(value);
		size++;
	}

	void Erase(int idx)
	{
		if (idx < 0 || idx >= size)
		{
			__debugbreak();
		}

		// shifting
		for (int i = idx; i < size - 1; ++i)
		{
			data[i] = std::move(data[i + 1]); // T might be heavy.
		}

		--size;
	}

	int Find(const T& value)
	{
		for (int i = 0; i < size; ++i)
		{
			if (data[i] == value)
			{
				return i;
			}
		}

		return -1; // failed
	}

	size_t Size() const
	{
		return size;
	}

	size_t Capacity() const
	{
		return capacity;
	}

	const T& operator[](size_t index) const
	{
		if (index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	// Á¤¼®X (iterator °´Ã¼X)
	T* begin() const
	{
		return data;
	}

	T* end() const
	{
		return data + size;
	}

private:
	void Resize(size_t newCapacity)
	{
		// 1. allocate a new block of memory.
		// 2. copy/move old elements into new block.
		// 3. delete.

		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		if (newCapacity < size)
		{
			size = newCapacity;
		}

		memcpy(newBlock, data, sizeof(T) * capacity); // data != nullptr

		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};