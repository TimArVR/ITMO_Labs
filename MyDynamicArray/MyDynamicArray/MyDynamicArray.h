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
		capacity_ = 16; //������� �� ��������� ��������� 16
		ptr_ = (T*)malloc(capacity_ * sizeof(T));
	}

	Array (int capacity)
	{
		if (capacity <= 0)
		{
			capacity_ = 16; //defolt��� ����� ��� �������� ��� 0 ����� ��������
		}
		else
		{
			capacity_ = capacity;
		}

		ptr_ = (T*)malloc(capacity_ * sizeof(T));

	}

	Array (Array&& other) //������������ �����������
	{
		ptr_ = other.ptr_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	// ����������� �����������
	Array(const Array& other)
	{
		size_ = other.size_;
		capacity_ = other.capacity_;

		ptr_ = (T*)malloc(other.capacity_ * sizeof(T));
		for (int i = 0; i < other.size_; i++)
		{			
			new (ptr_ + i) T(other.ptr_[i]); // ����������� new ����� �������� ���������� �����������

		}
	}

	// ���������� ��������� ������������ � ������� ������ Copy-Swap
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

	// ������������ �������� ������������ (������ r-value ref)
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

	int Insert(const T& value) // ���������� push back
	{
		//std::cout << "Insert without index: Pushback called" << std::endl;

		if ((size_ + 1) > capacity_) //�������� ����� ���� ��� �� ������� � 2 ����
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

		new(ptr_ + size_)T(std::move(value)); //������� ����� �������� � �����
		++size_;

		return (size_ - 1);
	}

	int Insert(int index, const T& value) // ������� � ��������� �������
	{
		if (index < 0 || index > size_)
		{
			std::cout << "������� ���������� �������� �������" << std::endl;
			return -1;
		}

		//if (index == size_) // ���������� �����
		//{
		//	Insert(value); // ���������� ������� � ����� 
		//	return index;
		//}

		if ((size_ + 1) > capacity_) //�������� ����� ���� ��� �� ������� � 2 ����
		{
			capacity_ *= 2;
			T* tempptr_ = (T*)malloc((capacity_) * sizeof(T));

			for (int i = 0; i < index; i++) // �������� ������ �����
			{
				new (tempptr_ + i) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			for (int i = index; i < size_; i++) // �������� ������ �����
			{
				new(tempptr_ + i + 1) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			std::free(ptr_);
			ptr_ = tempptr_;
		}
		else
		{
			for (int i = size_; i > index; --i) // �������� ������ ������ �����
			{
				new (ptr_ + i) T(std::move(ptr_[i-1])); 
				ptr_[i-1].~T();
			}
		}

		new (ptr_ + index) T(std::move(value)); // ������� ����� �������

		++size_;

		return index;
	}

	void Remove(int index)
	{
		if (index < 0 || index>(size_ - 1))
		{
			return;
		}

		ptr_[index].~T(); //�������� ������ �� ��� ���� ������

		for (int i = index; i < size_ - 1; ++i) // �������� ����� ������ �����
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
		return ptr_[index]; //���������� ���������� i �������
	}

	T& operator[](int index)
	{
		return ptr_[index]; //���������� i �������
	}


	//���������� �������� ������������ �� ������ Copy-Swap, ����������� "�������" ����������

	//Array & operator = (const Array& other)
	//{
	//    cout << "��������� ���������� ��������� ������������ " << this << endl;
	//    size = other.size;
	//    if (this != &other || this->ptr!=nullptr)//��������� �� ������������ a=a; � �� ���� ��� ��������� ��� ������
	//    {
	//        free(ptr);
	//    }
	//    else 
	//    {
	//        cout << "������ ��� ������ � ���������� ������������" << endl;
	//       // return *this; ��� �������� ����� �� ���� return
	//    }
	//    ptr = (int*)malloc(other.size * sizeof(int));
	//    for (int i = 0; i < other.size; i++)
	//    {
	//        if (ptr)
	//        {
	//            /*ptr[i] = other.ptr[i];*/ //��������� �� �������, �.�. ����� ������ �� ��������
	//            new (ptr + i)T(other.ptr[i]);
	//        }
	//        else
	//        {
	//            cout << "������: ������� ������������� ������� ��������� " << endl;
	//        }
	//    }        
	//    return *this;
	//}

	~Array()
	{
		for (int i = 0; i < size_; i++)
		{
			ptr_[i].~T(); //������� ���������� ��� ������� ��������, ����� ������ �� ��������
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

		bool HasNext() const //���������� HasCurrent
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

		bool HasNext() const //���������� HasCurrent
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