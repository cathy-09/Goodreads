#pragma once
#include "ValidationException.h"
#include <string>

class RatingException : public ValidationException
{
public:
	explicit RatingException(const std::string& message);
};

