#include <variant>
#include <iostream>
#include <string>
#include <vector>

class student
{
	int rollno;
	float percentage;
public:
	student() { std::cout << "In student constructor\n"; };
	~student() { std::cout << "In student destructor\n"; }
};
class teacher
{
	std::string name;
	std::vector<std::string> subjects;
public:
	teacher() { std::cout << "In teacher constructor\n"; };
	~teacher(){ std::cout << "In teacher destructor\n"; }
};
class myClass
{
	int i;
	float f;
public:
	myClass(int i, float f) {};
};
int main()
{
	std::variant<int, float> defaultvar;
	std::cout << std::get<int>(defaultvar) << "\n";	//prints 0
	
	//std::variant<myClass, int, float> vartry;	//Doesn't compile because no default constructor for myClass
	std::variant<std::monostate,myClass, int, float> vartry;	//works!
	if (std::holds_alternative<int>(vartry) || std::holds_alternative<float>(vartry) || std::holds_alternative<myClass>(vartry))
	{
		std::cout << "vartry default initialized" << "\n";
	}
	else
	{
		auto x = std::get<std::monostate>(vartry);
		std::cout << typeid(x).name() << "\n";
	}
	
	std::variant<student,int, float> var1;
	var1 = 12.33f;

	std::variant<student, teacher> multiclassVariant;	//Calls student constructor
	student defaultStudent = std::get<0>(multiclassVariant);
	multiclassVariant = teacher();		//Calls student destructor and then teacher constructor

	int numOfAlternatives = std::variant_size_v<decltype(var1)>;	//3

	float f1 = std::get<float>(var1);	//f1=12.33
	float f2 = std::get<2>(var1);	// f2=12.33

	try {
		std::get<0>(var1);		//throws bad_variant_access
	}
	catch (const std::exception &ex)
	{
		std::cout << typeid(ex).name() << " " << ex.what()<<"\n";
	}

	try {
		int i = std::get<int>(var1);	//throws bad_variant_access
	}
	catch (const std::exception &ex)
	{
		std::cout << typeid(ex).name() << " " << ex.what()<<"\n";
	}

	int *i = std::get_if<int>(&var1);
	if(i)
		std::cout << *i << "\n";
	float *f3 = std::get_if<float>(&var1);
	if (f3)
		std::cout << *f3 << "\n";
	
	if (std::holds_alternative<float>(var1) == true) // succeeds
	{
		var1 = 100;
		if (std::holds_alternative<int>(var1) == true) //succeeds
		{
			var1 = 12.33f;
		}
	}

	if (var1.valueless_by_exception())
	{
		int x = 100;
	}
	std::variant<int, float> var2 = 20;
	std::visit([](auto const &e) {std::cout << e; }, var2);
	
	struct mutltiVisitor
	{
		void operator() (std::string &s)
		{
			std::cout << s << "\t" << s;
		}
		void operator ()(int i)
		{
			std::cout << i*i;
		}
		void operator ()(float f)
		{
			std::cout << f * f;
		}
	};

	std::variant < std::string, int, float> var3 = 24;
	std::visit(mutltiVisitor(), var3);
	return 0;
}
