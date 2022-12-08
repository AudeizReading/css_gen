#include <HTMLFile.hpp>

HTMLFile::HTMLFile(const std::string& filename) : AStatFile(filename), _head(), _body(), _full_content(), _tags() 
{
    std::ifstream	is(this->_filename, std::ios::in);
    if (!is.is_open())
    {
    	throw std::runtime_error("HTMLFile could not be open\nFATAL ERROR\n");
    }


    std::string	line;

    std::cout.precision(5);

    while (std::getline(is, line, '\n'))
    {
	if (is.fail())
	{
	    throw std::runtime_error("HTMLFile encounters troubles while reading\nFATAL ERROR\n");
	}

	this->_setHeadTag(line);
	this->_setBodyTag(line);
	this->_full_content.append(line);
	this->_full_content.append("\n");

	++this->_nb_lines;
    }
    is.close();
}

HTMLFile::~HTMLFile(void) {}

std::string		HTMLFile::getNameFile()	    const { return this->_filename; }
unsigned int		HTMLFile::getNbLine()	    const { return this->_nb_lines; }
std::string		HTMLFile::getHeadTag()	    const { return this->_head; }
std::string		HTMLFile::getBodyTag()	    const { return this->_body; }
std::string		HTMLFile::getFullContent()  const { return this->_full_content; }
HTMLFile::map_tag	HTMLFile::getTags()	    const { return this->_tags; }

void			HTMLFile::_setHeadTag(const std::string& line)
{ 
    size_t	pos_head = 0;
    static bool	found_head = false;

    if (((pos_head = line.find("<head>")) != std::string::npos) && found_head == false)
    {
	found_head = true;
    }
    if (found_head)
    {
	this->_head.append(line);
	this->_head.append("\n");
    }
    if (((pos_head = line.find("</head>")) != std::string::npos) && found_head == true)
    {
	found_head = false;
    }
}

void			HTMLFile::_setBodyTag(const std::string& line)
{ 
    size_t	pos_body = 0;
    static bool	found_body = false;

    if (((pos_body = line.find("<body>")) != std::string::npos) && found_body == false)
    {
	found_body = true;
    }
    if (found_body)
    {
	this->_body.append(line);
	this->_body.append("\n");

	size_t		    pos_tag = 0;
	std::string	    line_tag(line);

	while ((pos_tag = line_tag.find("<")) != std::string::npos)
	{
	    pos_tag++;

	    size_t	end_tag = line_tag.find_first_of(">");
	    if (end_tag == std::string::npos)
	    {
		ERROR("html failure, missing closing bracket");
		return;
	    }

	    // si on tombe sur un slash, la taille du tag est reduite de 1
	    size_t	pos_slash = 0;
	    if ((pos_slash = line_tag.find_first_of("/")) != std::string::npos)
	    {
		if (end_tag == (pos_slash + 1))
		    end_tag--;
		if (pos_slash == 0 || pos_tag == pos_slash)
		{
		    pos_tag++;
		}
	    }

	    size_t	len_nametag = line_tag.find_first_of(" ");
	    if (len_nametag == std::string::npos || len_nametag == 0 || pos_tag > len_nametag)
	    {
		len_nametag = end_tag - pos_tag;
	    }
	    else
	    {
		len_nametag -= pos_tag;
	    }
	    // permet de boucler sur la line si plusieurs tags sur une meme ligne
	    std::string    tag = line_tag.substr(pos_tag, len_nametag);
	    if (pos_tag != pos_slash) // Si on a affaire a la balise ouvrante et non fermante
	    {
		/*
		 *  par faineantise je laisse line_tag en value, mais en
		 *  tout logique ca devrait etre rempli par les attributs
		 *  du tag html (et non toute la ligne comme c'est fait)
		 *  pour le fichier css, le demarrer, avoir un
		 *  exemplaire de chaq tag suffit
		 *  au developpeur d'enrichir son fichier css
		 */ 
		std::pair<std::string, std::string>    p_tags(tag, line_tag);
		this->_tags.insert(p_tags);
	    }

	    line_tag = line_tag.substr(pos_tag + end_tag - pos_tag + 1, line_tag.size() - pos_tag);

	} 
    }
    if (((pos_body = line.find("</body>")) != std::string::npos) && found_body == true)
    {
	found_body = false;
    }
}

void			HTMLFile::printTags() const
{
    if (!this->_tags.empty())
    {
	iterator    it_beg = this->_tags.begin();
	iterator    it_end = this->_tags.end();

	for (; it_beg != it_end; ++it_beg)
	{
	    std:: cout << "\n=================\n";
	    std::cout << "it_beg->first:\t"<< it_beg->first << "\nit_beg->second:\t" << it_beg->second << "\n";
	}
    }
    else 
    {
	std:: cout << "\nThere is no tag inside the body part\n";
    }
}

void			HTMLFile::addLinkCSS(const std::string& css_filename) const
{
    size_t  pos_head = 0;
    if (!this->_tags.empty() && (pos_head = this->_full_content.find("<head>")) != std::string::npos)
    {
	std::string	fc(this->_full_content);
	std::string	meta("\t\t<link rel=\"");
	meta.append(css_filename);
	meta.append("\"/>\n");

	fc.insert(pos_head + 8, meta);
	std::ofstream	os_html(this->getNameFile(), std::ios::trunc|std::ios::out);

	if (!os_html.is_open())
	{
	    throw std::runtime_error("HTMLFile could not be open\nFATAL ERROR\n");
	}
	os_html << fc;
	os_html.close();
    }
}

std::ostream&		HTMLFile::makeCSSTags(std::ostream& o)
{
    if (!this->_tags.empty())
    {
	iterator    it_beg = this->_tags.begin();
	iterator    it_end = this->_tags.end();

	for (; it_beg != it_end; ++it_beg)
	{
	    o << it_beg->first << " {\n}\n\n";
	}
    }
    return o;
}
