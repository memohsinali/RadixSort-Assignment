#include<iostream>
#include<string.h>
using namespace std;

template<class T>
class Queue
{
private:
	class node
	{
	public:
		T data;
		node* next;
	};
	node* front;
	node* rear;
	int total;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
		total = 0;
	}

	class iterator
	{
		friend class Queue;
		node* curr;
	public:
		iterator(node* n)
		{
			curr = n;
		}

		iterator()
		{
			curr = NULL;
		}

		iterator(iterator& obj)
		{
			curr = obj.curr;
		}

		iterator& operator++()
		{
			curr = curr->next;
			return *this;
		}

		T& operator*()
		{
			return curr->data;
		}

		bool operator !=(const iterator& itr) 
		{
			if (curr != itr.curr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


	};

	iterator begin()
	{
		iterator itr(front);
		return itr;
	}

	iterator end()
	{
		iterator itr(rear);
		return itr;
	}


	//functions

	void enqueue(T val)
	{
		node* insert = new node();
		if (insert == NULL)
		{
			cout << "Queue is full\n";
		}
		else
		{
			if (front == NULL)
			{
				insert->data = val;
				front = insert;
				rear = insert;
				total++;
			}
			else
			{
				insert->data = val;
				rear->next = insert;
				rear = insert;
			    total++;
			}
		}
	}


	void dequeue()
	{
		if (isEmpty())
		{
			return;
		}
		else
		{
			total--;
			node* del;
			del = front;
			front = front->next;
			delete del;
			del = NULL;
		}
	}

	void print()
	{
		iterator itr ;
		itr = begin();
		for (;itr != NULL;++itr)
		{
			cout << *itr<< "--";
		}
		cout << endl;
	}

	T getFrontdata()
	{
		return front->data;
	}

	node* getFront()
	{
		return front;
	}
	

	bool isEmpty()
	{
		if (front==NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void clear()
	{
		node* temp = front;
		while (temp != NULL)
		{
			node* del = temp;
			temp = temp->next;
			delete del;
			del = NULL;
		}
	}

	int size()
	{
		return total;
	}

	~Queue()
	{
		/*delete[]ptr<Queue>;
		ptr < Queue >= NULL;*/
	}


};


void Queue<string>::enqueue(string val)
{
	node* insert = new node();
	if (insert == NULL)
	{
		cout << "Queue is full\n";
	}
	else
	{
		if (front == NULL)
		{
			insert->data = val;
			front = insert;
			rear = insert;
			total++;
			rear->next = NULL;
		}
		else
		{
			insert->data = val;
			rear->next = insert;
			rear = insert;
			total++;
			rear->next = NULL;
		}
	}
}

int maximum(Queue<int> original)
{
	int max = 0;
	Queue<int> ::iterator itr;
	itr = original.begin();
	max = *itr;
	++itr;
	for (;itr != NULL;++itr)
	{
		if (max < *itr)
		{
			max = *itr;
		}
	}
	cout << max<< endl;
	return max;
}

void  redixSort(Queue<int> &original, int digit)
{
	//Queue<int> q1;
	Queue<int>* ptr = new Queue<int>[10];

	Queue<int>::iterator itr;
	Queue<int>::iterator track;
	Queue<int>::iterator temp1;
	int count = 1;
	int value;
	int temp;
	int l = 0;
	int max = maximum(original);   //keep track max value in queu and then fidn max no of digits in a key
	while (max != 0)
	{
		max = max / 10;
		l++;
	}
	digit = l;
	for(int i=0;i<digit;i++)
	{
		itr = original.begin();
		for (;itr!= NULL;++itr)
		{
			int l;
			value =  (( *itr/count)% 10);
			ptr[value].enqueue(*itr);
		}

		while (!original.isEmpty())
		{
			original.dequeue();
		}
		
		for (int k = 0;k < 10;k++)
		{
			int l;
			if(!ptr[k].isEmpty())
			{
				while (!ptr[k].isEmpty())
				{
					original.enqueue(ptr[k].getFrontdata());  // sorting the original queue
					ptr[k].dequeue();
				}
			}
		}
		count = count * 10;
	}
}



void  redixSort(Queue<string>& original, int digit)
{
	Queue<string>* ptr = new Queue<string>[128];

	Queue<string>::iterator itr;
	Queue<string>::iterator track;
	Queue<string>::iterator temp1;
	int value;
	char temp;
	int l = digit;
	for (int i = 0;i < digit;i++)
	{
		l--;
		itr = original.begin();
		for (;itr != NULL;++itr)
		{
			string s1 = *itr;
			temp = s1[l];
			ptr[temp].enqueue(s1);
		}
		
		while (!original.isEmpty())
		{
			original.dequeue();
		}

		for (int k = 0;k < 128;k++)
		{
			if (!ptr[k].isEmpty())
			{
				while (!ptr[k].isEmpty())
				{
					original.enqueue(ptr[k].getFrontdata());
					ptr[k].dequeue();
				}
			}
		}
	}
}


void lessGOint()
{
	Queue <int> originalint;
	int key;
	int digit;
	cout << "Enter total number of keys :\n";
	cin >> key;
	cout << "Enter the number of digits in each key\n";
	cin >> digit;
	int track = 0;
	while (track != key)
	{
		int k;
		cout << "Enter the key:\n";
		cin >> k;
		originalint.enqueue(k);
		track++;
	}
	originalint.print();

	redixSort(originalint,digit);
	cout << endl;
	originalint.print();


}

void lessGOstr()
{
	Queue <string> originalstr;
	int key;
	int digit;
	cout << "Enter total number of keys :\n";
	cin >> key;
	cout << "Enter the number of characters in each key\n";
	cin >> digit;
	int track = 0;
	while (track != key)
	{
		string k;
		cout << "Enter the key:\n";
		cin >> k;
		originalstr.enqueue(k);
		track++;
	}
	originalstr.print();
	redixSort(originalstr,digit);
	originalstr.print();
}

int main()
{
	int check;
	cout << "Enter 1 for integer \n Enter 2 for string\n";
	cin >> check;
	if (check == 1)
	{
		lessGOint();
	}
	else if (check == 2)
	{
		lessGOstr();
	}
	else
	{
		cout << "Terminate . User not valid\n";
	}

	return 0;
}