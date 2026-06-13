#pragma once
#include "GoodreadsException.h"
#include <stdexcept>
#include <string>

class FileException : public GoodreadsException
{
public:
	explicit FileException(const std::string& message);
};

