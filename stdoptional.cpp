
#include <optional>
#include <iostream>

int main()
{
	std::optional<int> opt1 = std::nullopt;
	std::optional<std::string> optStr = std::make_optional<std::string>("str");
	std::optional<int> opt = 2;
	if (opt.has_value())
	{
		int val = *opt;
		int val2 = opt.value();
		*opt = 5;
		
		std::optional < std::string > opt2 = "string";
		opt2->size();
		
		opt = std::nullopt;
		try
		{
			int noVal = opt.value();
		}
		catch (const std::bad_optional_access &ex)
		{
			std::cout << ex.what() << "\n";
		}
	}

	std::optional<int *> optPtr = new int[10];
	(*optPtr)[0] = 100;
	(*optPtr)[2] = 200;

	auto optint = std::make_optional<int>(100);
	if (optint.has_value()) 	//returns true
	{
		std::cout << "optint has value \n";
	}


	return opt.value_or(3);
}
