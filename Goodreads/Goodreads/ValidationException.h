#pragma once
#include "GoodreadsException.h"
#include <stdexcept>
#include <string>

class ValidationException : public GoodreadsException
{
public:
	explicit ValidationException(const std::string& message);
};

