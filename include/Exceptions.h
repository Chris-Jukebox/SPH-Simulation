/*
* Copyright © 2015 Jeremy T. Hatcher All Rights Reserved
*/

#pragma once

#include <exception>
#include <string>

class GenericException
{
protected:
	std::string m_msg;
public:
	explicit GenericException(std::string& message)
		:m_msg(message)
	{}

	explicit GenericException(const char* message)
		:m_msg(message)
	{}

	virtual ~GenericException() throw()
	{}

	virtual const char* what() const throw() {
		return m_msg.c_str();
	}
};