#pragma once
#include <iostream>
#include <algorithm>

template<typename T> class Array final
{
private:
	T* ptr_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;

public:
	Array()
	{
		capacity_ = 16; //default capacity is 16
		ptr_ = (T*)malloc(capacity_ * sizeof(T));
	}

	Array (int capacity)
	{
		if (capacity <= 0)
		{
			capacity_ = 16;
		}
		else
		{
			capacity_ = capacity;
		}

		ptr_ = (T*)malloc(capacity_ * sizeof(T));

	}

	Array (Array&& other) //Moving constructor
	{
		ptr_ = other.ptr_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	// Copy constructor
	Array(const Array& other)
	{
		size_ = other.size_;
		capacity_ = other.capacity_;

		ptr_ = (T*)malloc(other.capacity_ * sizeof(T));
		for (int i = 0; i < other.size_; i++)
		{			
			new (ptr_ + i) T(other.ptr_[i]); //special "Placement new" to call the copying constructor

		}
	}

	// Overloading the "= operator" using the Copy-Swap idiom
	void Swap(Array& other)
	{
		std::swap(ptr_, other.ptr_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}

	Array& operator = (Array other)
	{
		Swap(other);
		return *this;
	}

	// Moving "= operator" (capture r-value ref)
	Array& operator = (Array&& other)
	{
		for (int i = 0; i < size_; i++)
		{
			ptr_[i].~T();
		}

		std::free(ptr_);
		ptr_ = other.ptr_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	int Insert(const T& value) // "push back" in reality
	{
		//std::cout << "Insert without index: Pushback called" << std::endl;

		if ((size_ + 1) > capacity_) //increase 2x the volume if it is not enough
		{
			capacity_ *= 2;
			T* tempptr_ = (T*)malloc((capacity_) * sizeof(T));

			for (int i = 0; i < size_; i++)
			{
				new (tempptr_ + i) T(std::move(ptr_[i]));
			}
			for (int i = 0; i < size_; i++)
			{
				ptr_[i].~T();
			}

			std::free(ptr_);
			ptr_ = tempptr_;
		}

		new(ptr_ + size_)T(std::move(value)); //insert a new value AT THE END
		++size_;

		return (size_ - 1);
	}

	int Insert(int index, const T& value) // insert into the specified position
	{
		if (index < 0 || index > size_)
		{
			std::cout << "Re-enter the correct index value" << std::endl;
			return -1;
		}


		if ((size_ + 1) > capacity_) //increase 2x the volume if it is not enough
		{
			capacity_ *= 2;
			T* tempptr_ = (T*)malloc((capacity_) * sizeof(T));

			for (int i = 0; i < index; i++) // copy the first part
			{
				new (tempptr_ + i) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			for (int i = index; i < size_; i++) // copy the second part
			{
				new(tempptr_ + i + 1) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			std::free(ptr_);
			ptr_ = tempptr_;
		}
		else
		{
			for (int i = size_; i > index; --i) // shift the right part to the right
			{
				new (ptr_ + i) T(std::move(ptr_[i-1])); 
				ptr_[i-1].~T();
			}
		}

		new (ptr_ + index) T(std::move(value)); // place the new element

		++size_;

		return index;
	}

	void Remove(int index)
	{
		if (index < 0 || index>(size_ - 1))
		{
			return;
		}

		ptr_[index].~T(); //clean the cell that the index is pointing to

		for (int i = index; i < size_ - 1; ++i) //shift the right part from the left
		{
			new (ptr_ + i) T(std::move(ptr_[i+1])); 
			ptr_[i+1].~T();
		}
		
		--size_;
	}

	int Size() const
	{
		return size_;
	}

	int Capacity() const
	{
		return capacity_;
	}

	const T& operator[] (int index) const
	{
		return ptr_[index]; //constant, returns the i element
	}

	T& operator[](int index)
	{
		return ptr_[index]; //returns the i element
	}

	~Array()
	{
		for (int i = 0; i < size_; i++)
		{
			ptr_[i].~T(); //call destructor for each element so as not to lose anything
		}	

		std::free(ptr_);
	}

	class Iterator final
	{
	private:
		Array* array_;
		int direction_;
		int index_;

	public:
		friend Array;

		T& Get() const
		{
			return (*array_)[index_];
		}

		void Set(const T& value)
		{
			(*array_)[index_] = value;
		}

		void Next()
		{
			index_ = index_ + direction_;
		}

		bool HasNext() const //HasCurrent in reality
		{
			return (index_ + direction_ >= 0) && (index_ + direction_ <= array_->size_);
		}
	};

	class ConstIterator final
	{
	private:
		const Array* array_;
		int direction_;
		int index_;

	public:
		friend Array;

		const T& Get() const
		{
			return (*array_)[index_];
		}

		void Next()
		{
			index_ = index_ + direction_;
		}

		bool HasNext() const //HasCurrent in reality
		{
			return (index_ + direction_ >= 0) && (index_ + direction_ <= array_->size_);
		}

	};

	Iterator iterator()
	{
		Iterator it;
		it.direction_ = 1;
		it.index_ = 0;
		it.array_ = this;

		return it;
	}

	Iterator ReverseIterator()
	{
		Iterator it;
		it.direction_ = -1;
		it.index_ = size_- 1;
		it.array_ = this;

		return it;
	}

	ConstIterator iterator() const
	{
		Iterator it;
		it.direction_ = 1;
		it.index_ = 0;
		it.array_ = this;

		return it;
	}

	typename ConstIterator ReverseIterator() const
	{
		Iterator it;
		it.direction_ = -1;
		it.index_ = size_ - 1;
		it.array_ = this;

		return it;
	}
};