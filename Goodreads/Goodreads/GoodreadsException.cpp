#include "GoodreadsException.h"

GoodreadsException::GoodreadsException(const std::string& message) : std::runtime_error(message) 
{
	
}