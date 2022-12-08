#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include <stdexcept>
#include <string.h>

#include <AStatFile.hpp>

#define ERROR(x) std::cerr << std::boolalpha << "\033[31;1min " << __FILE__ << ":" << __func__ << ":"<< __LINE__ << ": " << #x << "\n" << x << "\n\033[0m";

class HTMLFile: public AStatFile
{
    public:
    	typedef	    std::map<std::string, std::string>			map_tag;
    	typedef	    std::map<std::string, std::string>::const_iterator  iterator;

    protected:
	std::string	_head;
	std::string	_body;
	std::string	_full_content;
    	map_tag		_tags;

	void			_setHeadTag(const std::string& line);
	void			_setBodyTag(const std::string& line);
    public:
    	HTMLFile(const std::string& filename);
	HTMLFile(const HTMLFile& src);
	HTMLFile& operator=(const HTMLFile& src);
	virtual ~HTMLFile(void);

	virtual std::string	getNameFile() const;
	virtual unsigned int	getNbLine() const;
	virtual std::string	getHeadTag() const;
	virtual std::string	getBodyTag() const;
	virtual std::string	getFullContent() const;
	virtual map_tag		getTags() const;
	virtual void		printTags() const;
	virtual void		addLinkCSS(const std::string& css_filename) const;
	virtual std::ostream&	makeCSSTags(std::ostream& o);
};
