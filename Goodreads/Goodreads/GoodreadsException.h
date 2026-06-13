#pragma once
#include <stdexcept>
#include <string>

class GoodreadsException : public std::runtime_error
{
public:
	explicit GoodreadsException(const std::string& message);
};

