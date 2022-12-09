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
		capacity_ = 16; //Емкость по умолчанию установим 16
		ptr_ = (T*)malloc(capacity_ * sizeof(T));
	}

	Array (int capacity)
	{
		if (capacity <= 0)
		{
			capacity_ = 16; //defoltный объем при неверном или 0 вводе капасити
		}
		else
		{
			capacity_ = capacity;
		}

		ptr_ = (T*)malloc(capacity_ * sizeof(T));

	}

	Array (Array&& other) //перемещающий конструктор
	{
		ptr_ = other.ptr_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	// Конструктор копирования
	Array(const Array& other)
	{
		size_ = other.size_;
		capacity_ = other.capacity_;

		ptr_ = (T*)malloc(other.capacity_ * sizeof(T));
		for (int i = 0; i < other.size_; i++)
		{			
			new (ptr_ + i) T(other.ptr_[i]); // размещающий new чтобы вызывать копирующий конструктор

		}
	}

	// Перегрузка оператора присваивания с помощью идиомы Copy-Swap
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

	// Перемещающий оператор присваивания (захват r-value ref)
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

	int Insert(const T& value) // фактически push back
	{
		//std::cout << "Insert without index: Pushback called" << std::endl;

		if ((size_ + 1) > capacity_) //увеличим объем если его не хватает в 2 раза
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

		new(ptr_ + size_)T(std::move(value)); //вставим новое значение в конец
		++size_;

		return (size_ - 1);
	}

	int Insert(int index, const T& value) // вставка в указанную позицию
	{
		if (index < 0 || index > size_)
		{
			std::cout << "Введите корректное значение индекса" << std::endl;
			return -1;
		}

		//if (index == size_) // избыточный вызов
		//{
		//	Insert(value); // фактически вставим в конец 
		//	return index;
		//}

		if ((size_ + 1) > capacity_) //увеличим объем если его не хватает в 2 раза
		{
			capacity_ *= 2;
			T* tempptr_ = (T*)malloc((capacity_) * sizeof(T));

			for (int i = 0; i < index; i++) // копируем первую часть
			{
				new (tempptr_ + i) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			for (int i = index; i < size_; i++) // копируем вторую часть
			{
				new(tempptr_ + i + 1) T(std::move(ptr_[i]));
				ptr_[i].~T();
			}
			std::free(ptr_);
			ptr_ = tempptr_;
		}
		else
		{
			for (int i = size_; i > index; --i) // сдвигаем вправо правую часть
			{
				new (ptr_ + i) T(std::move(ptr_[i-1])); 
				ptr_[i-1].~T();
			}
		}

		new (ptr_ + index) T(std::move(value)); // вставим новый элемент

		++size_;

		return index;
	}

	void Remove(int index)
	{
		if (index < 0 || index>(size_ - 1))
		{
			return;
		}

		ptr_[index].~T(); //почистим ячейку на кот указ индекс

		for (int i = index; i < size_ - 1; ++i) // сдвигаем слева правую часть
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
		return ptr_[index]; //константый возвращает i элемент
	}

	T& operator[](int index)
	{
		return ptr_[index]; //возвращает i элемент
	}


	//Переделали оператор присваивания на идиому Copy-Swap, закомментим "наивную" реализацию

	//Array & operator = (const Array& other)
	//{
	//    cout << "Вызвалась перегрузка оператора присваивания " << this << endl;
	//    size = other.size;
	//    if (this != &other || this->ptr!=nullptr)//защитимся от присваивания a=a; и от того что указатель без адреса
	//    {
	//        free(ptr);
	//    }
	//    else 
	//    {
	//        cout << "Ошибка при раобте с оператором присваивания" << endl;
	//       // return *this; тут подумать нужен ли этот return
	//    }
	//    ptr = (int*)malloc(other.size * sizeof(int));
	//    for (int i = 0; i < other.size; i++)
	//    {
	//        if (ptr)
	//        {
	//            /*ptr[i] = other.ptr[i];*/ //перепишем по другому, т.к. новый массив не размещен
	//            new (ptr + i)T(other.ptr[i]);
	//        }
	//        else
	//        {
	//            cout << "Ошибка: попытка разыменования пустого указателя " << endl;
	//        }
	//    }        
	//    return *this;
	//}

	~Array()
	{
		for (int i = 0; i < size_; i++)
		{
			ptr_[i].~T(); //вызовем деструктор для каждого элемента, чтобы ничего не потерять
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

		bool HasNext() const //фактически HasCurrent
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

		bool HasNext() const //фактически HasCurrent
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