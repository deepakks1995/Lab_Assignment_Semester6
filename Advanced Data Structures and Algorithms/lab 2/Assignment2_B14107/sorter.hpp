/************************************************************************
 *
 * Name = Deepak Sharma
 *
 * Roll_No = B14107
 *
 **************************************************************************/

#ifndef SORTER_HPP
#define SORTER_HPP

#include "vector.hpp"
using namespace abc;

namespace sort
{
	template<class Item>
		class sorter
		{
			public:
				void insertion_sort(vector<Item>& a, int lo, int hi);
				void merge_sort(vector<Item>& a, int lo, int hi);
				void _merge(vector<Item>& a, int lo, int mid, int hi);
				void rank_sort(vector<Item>& a, int lo,int hi);
				void selection_sort(vector<Item>& a,int lo,int hi);
				void quick_sort(vector<Item>& a,int lo,int hi);
				int _partition(vector<Item>& a, int p, int r);
				void bubble_sort(vector<Item>& a,int lo,int hi);
				void _swap(Item& a, Item& b);
				void opt_bubble_sort(vector<Item>& a, int lo, int hi);
				void opt_rank_sort(vector<Item>& a, int lo, int hi);
		};

	template<class Item>
		void sorter<Item>::insertion_sort(vector<Item>& a, int lo, int hi)
		{
			if(lo<0 || hi>=a.size())
				std::cout<<"Error! Array Index out of Bounds!\n";
			else
			{
				int key;
				for(int i = lo+1; i <= hi ; i++)
				{
					key = a[i];
					int j = i-1;
					while( j >= lo && a[j] > key )
					{
						a[j+1] = a[j];
						j--;
					}
					a[j+1] = key;
				}
			}
		}

	template <class Item>
		void sorter<Item>::merge_sort(vector<Item>& a, int lo, int hi)
		{
			if(lo<0 || hi>=a.size())
				std::cout<<"Error! Array Index out of Bound!";
			else
			{
				if(lo < hi )
				{
					int mid = lo + (hi-lo)/2;

					merge_sort(a,lo,mid);
					merge_sort(a,mid+1,hi);
					_merge(a,lo,mid,hi);
				}
			}
		}

	template <class Item>
		void sorter<Item>::_merge(vector<Item>& a, int lo, int mid, int hi)
		{
			vector<Item> LHS(mid-lo+1,0);
			vector<Item> RHS(hi-mid,0);
			int i,j;

			for(i=0,j=lo; j<=mid; i++,j++)
				LHS[i] = a[j];
			for(i=0,j=mid+1; j<=hi; i++,j++)
				RHS[i] = a[j];
			int k=lo;
			i=0;
			j=0;
			while(i<mid-lo+1 && j<hi-mid)
			{
				if( LHS[i] <= RHS[j] )
					a[k] = LHS[i++];
				else
					a[k] = RHS[j++];
				k++;
			}
			while(i<mid-lo+1)
			{
				a[k] = LHS[i];
				++k;
				++i;
			}
			while(j<hi-mid)
			{
				a[k] = RHS[j];
				++k;
				++j;
			}
		}

	template<class Item>
		void sorter<Item>::rank_sort(vector<Item>& a, int lo, int hi)
		{
			if( lo<0 || hi >= a.size() )
				std::cout<<"Error! Array Index Out of Bounds!\n";
			else
			{
				int i,j;
				vector<int> rank(hi-lo+1,1);
				vector<Item> U(hi-lo+1,0);
				for(i = 1 ; i <= hi-lo ; i++)
				{
					for(int j = 0 ; j < i; j++ )
					{
						if( a[j+lo] <= a[i+lo] )
							rank[i]++;
						else
							rank[j]++;
					}
				}
				for(i = 0, j=lo ; j <= hi ; i++,j++)
					U[rank[i]-1] = a[j];
				for(i = 0, j=lo; j <=hi ; i++,j++)
					a[j] = U[i];
			}
		}

	template <class Item>
		void sorter<Item>::selection_sort(vector<Item>& a, int lo, int hi)
		{
			if( lo<0 || hi>=a.size() )
				std::cout<<"Error! Array Index out of Bound\n";
			else
			{
				bool sorted = false;
				int i,j,pos;
				i=hi;
				while( i>lo &&  sorted==false )
				{
					pos = lo;
					sorted = true;
					for( j=lo+1 ; j<=i; j++)
					{
						if( a[pos] <= a[j] )
							pos = j;
						else
							sorted =false;
					}
					_swap( a[pos], a[i] );
					i--;
				}
			}
		}

	template <class Item>
		void sorter<Item>::quick_sort(vector<Item>& a, int lo, int hi)
		{
			if(lo<0 || hi>=a.size())
				std::cout<<"Error! Array Index out of Bounds!\n";
			else
			{
				if(lo<hi)
				{
					int q = _partition(a,lo,hi);
					quick_sort(a,lo,q);
					quick_sort(a,q+1,hi);
				}
			}
		}

	template <class Item>
		int sorter<Item>::_partition(vector<Item>& a, int p, int r)
		{
			Item pivot = a[r];
			int i = p - 1;
			int j = r + 1;
			while(1)
			{
				do
					j--;
				while(a[j]>pivot);

				do
					i++;
				while(a[i]<pivot);
				if(j>i)
					_swap(a[i],a[j]);
				else if (j==i)
					return j-1;
				else return j;
			}
		}

	template <class Item>
		void sorter<Item>::bubble_sort(vector<Item>& a, int lo, int hi)
		{
			if( lo<0 || hi >= a.size() )
				std::cout<<"Error! Array Index out of Bound\n";
			else
			{
				for( int i = lo ; i<hi ; i++ )
					for( int j= i+1 ; j <= hi ; j++ )
						if( a[i] >= a[j] )
							_swap(a[i],a[j]);

			}
		}

	template <class Item>
		void sorter<Item>::_swap(Item& _a, Item& _b)    // function to swap two variables
		{
			int _tmp = _a;
			_a = _b;
			_b = _tmp;
		}

	template <class Item>
		void sorter<Item>::opt_bubble_sort(vector<Item>& a, int lo, int hi)
		{
			int i, j;
			bool swapped;
			for (i = lo; i < hi ; i++)
			{
				swapped = false;
				for (j = lo ; j < hi-i; j++)
				{
					if (a[j] > a[j+1])
					{
						_swap(a[j], a[j+1]);
						swapped = true;
					}
				}
				if (swapped == false)
					break;
			}
		}

	template<class Item>
		void sorter<Item>::opt_rank_sort(vector<Item>& a,int lo,int hi)
		{
			vector<int> rank(hi-lo+1,1);
			vector <Item> U(hi-lo+1,0);

			Item max;
			max=a[lo];
			for(int j=lo+1;j<=hi;j++)
			{
				if(a[j]>=max)
				{
					max=a[j];
					rank[j-lo]=j-lo+1;
				}
				else
				{
					for(int i=lo;i<=j-1;i++)
					{
						if(a[i]<=a[j])
							rank[j-lo]++;
						else
							rank[i-lo]++;
					}
				}
			}
			int i,j;
			for(i = 0, j=lo ; j <= hi ; i++,j++)
					U[rank[i]-1] = a[j];
				for(i = 0, j=lo; j <=hi ; i++,j++)
					a[j] = U[i];
		}
}
/*************************************************************
 * Implement your methods here.
 * You may add any number of methods in addition to the above ones.
 * However, the above methods must be implemented.
 * DO NOT name your methods or classes differently in any case.
 * Parameter details :
 * a : the vector to sort
 * lo : the lower index of the vector from where to sort
 * hi : the higher index of the vector till where to sort
 * e.g,
 * insertion_sort(a,2,10) will sort the vector a
 * from index 2, i.e, the third element,
 * till index 10, i.e, the eleventh element.
 *************************************************************/
#endif
