template<class T>
class Base
{
public:
	Base():
		data(0)
		{}
private:
	T data;
};

template<class T>
class Derived: public Base<T>
{
public:
	Derived():Base<T>()
	{}
	void fun(){}
};

int main()
{
	Derived<int> obj;
	return 0;
}
