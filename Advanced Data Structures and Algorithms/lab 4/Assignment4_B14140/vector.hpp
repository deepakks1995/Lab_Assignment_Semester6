
#include <iostream>
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace abc {					// namespace declaration
	template<class Item>
		class vector {			
			private:				// member declaration
				int _capacity;
				int _size;
				Item *data;
			public:					// function declaration
				vector();

				vector(const int& isize);

				vector(const int& isize, const Item& ival);

				vector(const vector& obj);

				~vector();

				inline Item& operator[](const int& i);

				void push_back(const Item& item);

				bool empty();

				int size();

				void fill(const Item& item);

				void resize(const int& size);

				class vector_Iterator		
				{
					private:
						Item *buffer;
					public:
						vector_Iterator()
						{
						}

						vector_Iterator(Item * location)
						{
							buffer=location;
						}

						bool operator !=(vector_Iterator  itr)
						{
							if(this->buffer != itr.buffer)
								return true;
							else
								return false;
						}
						void operator =(vector_Iterator a)
						{
							buffer=a.buffer;
						}

						bool operator ==(vector_Iterator& itr)
						{
							if(this->buffer==itr.buffer)
								return true;
							else
								return false;
						}

						void operator ++()
						{
							buffer++;
						}

						const vector_Iterator operator ++(int postfix)
						{
							vector_Iterator itr = *this;
							this->buffer++;
							return itr;
						}

						void operator --()
						{
							buffer--;
						}

						const vector_Iterator operator --(int postfix)
						{
							vector_Iterator itr = *this;
							this->buffer--;
							return itr;
						}

						Item operator*()
						{
							return *buffer;
						}
				};


				vector_Iterator begin()
				{
					return vector_Iterator(data);
				}

				vector_Iterator end()
				{
					return vector_Iterator(data + _size+1);
				}

				vector_Iterator rbegin()
				{
					return vector_Iterator(data + _size);
				}

				vector_Iterator rend()
				{
					return vector_Iterator(data-1);
				}
		};

	template<class Item>
		vector<Item>::vector()
		{
			_capacity=2;
			_size=-1;
			data=new Item[_capacity];
		}

	template<class Item>
		vector<Item>::vector(const int& isize)
		{
			_capacity=isize;
			_size=isize-1;
			data = new Item[_capacity];
			for(int i=0;i<=_capacity;i++)
				data[i]=0;
		}

	template<class Item>
		vector<Item>::vector(const int& isize,const Item& ival)
		{
			_size=isize-1;
			_capacity=isize;
			data = new Item[_capacity];
			for(int i=0;i<=_size;i++)
				data[i]=ival;
		}
	template<class Item>
		vector<Item>::vector(const vector& obj)
		{
			_capacity = obj._capacity;
			data = new Item[_capacity];
			_size = obj._size;
			for(int i = 0;i<obj._size;i++)
				data[i] = obj.data[i];
		}

	template<class Item>
		vector<Item>::~vector()
		{
			delete[ ] data;
		}

	template<class Item>
		inline Item& vector<Item>::operator [] (const int& i)
		{
			if(i>_size || i<0)
				std::cout<<"Array Index out of Bounds\n";
			else
				return data[i];
		}

	template<class Item>
		void vector<Item>::push_back(const Item& item)
		{
			if(_size==_capacity-1)
			{
				_capacity*=2;
				Item *new_data = new Item[_capacity];
				for(int i=0;i<=_size;i++)
					new_data[i]=data[i];
				delete [] data;
				data =new_data;
			}
			data[++_size]=item;
		}

	template<class Item>
		void vector<Item>::resize(const int& size)
		{
				int i;
				_capacity = size;
				Item *new_data = new Item[_capacity];
				delete [] data;
				data = new_data;
				_size = -1;
		}

	template<class Item>
		bool vector<Item>::empty()
		{
			if(_size==-1)
				return true;
			else
				return false;
		}

	template<class Item>
		int vector<Item>::size()
		{
			return _size+1;
		}

	template<class Item>
		void vector<Item>::fill(const Item& item)
		{
			for(int i=0;i<=_size;i++)
				data[i]=item;
		}


}

#endif
