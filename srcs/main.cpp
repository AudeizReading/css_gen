#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include <HTMLFile.hpp>

#define ERROR(x) std::cerr << std::boolalpha << "\033[31;1min " << __FILE__ << ":" << __func__ << ":"<< __LINE__ << ": " << #x << "\n" << x << "\n\033[0m";


/* Simplist Parser for HTML files for generating min css files corresponding */
int	main(int argc, char** argv)
{
    if (argc == 3)
    { 
	try {
	    HTMLFile	    hf(argv[1]);
	    std::ofstream   css(argv[2], std::ofstream::trunc|std::ofstream::out);

	    if (!css.is_open())
	    {
		ERROR(std::strcat(argv[2], " could not be open"));
		return 3;
	    }/**/
	    hf.makeCSSTags(css);
	    hf.addLinkCSS(argv[2]);

	    css.close();
	}
	catch(std::runtime_error& e)
	{
	    std::cerr << e.what() << "\n";
	    return 2;
	}
    }
    else 
    {
	std::cerr << "./" << argv[0] << " html_file css_file\nParse an html file for extracting the minimal css structural file\n";
	return 1;
    }
    return 0;
}
