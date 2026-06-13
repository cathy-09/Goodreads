#pragma once
#include "ValidationException.h"
#include <string>

class DateException : public ValidationException
{
public:
	explicit DateException(const std::string& message);
};

