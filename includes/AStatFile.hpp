#pragma once

#include <iostream>
#include <string>

class AStatFile
{
    protected:
	std::string	_filename;
	unsigned int	_nb_lines;

    	AStatFile(const std::string& filename);
    	AStatFile(const AStatFile& src);
    	AStatFile& operator=(const AStatFile& src);

    public:
    	virtual ~AStatFile(void);
    	virtual std::string	getNameFile() const = 0;
    	virtual unsigned int	getNbLine() const = 0;
};

