#!/bin/bash

FILENAME=${1-index.html}
CSS=${3}
JS=${4}

function usage
{
    echo "./html_squeletor_generator.sh [filename [title [css_filename [js_filename]]]]";
}

function make_head
{
    echo -e "\t<head>
    \t\t<meta charset=\"utf-8\"/>
    \t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"/>
    \t\t<title>${1-Welcome}</title>\n" >> ${FILENAME}
    if [[ -n ${CSS} && -f ${CSS} ]]; then
	echo -e "\t\t<link rel=\"${CSS}\"/>\n" >> ${FILENAME}
    fi
    echo -e "\t</head>\n" >> ${FILENAME}
}

function make_footer
{
    echo -e "\t\t<footer>
    \t\t\t<p>Paragraphe de footer</p>
    \t\t</footer>" >> ${FILENAME}
}

function make_nav
{
    echo -e "\t\t<nav>
    \t\t\t<ul>
    \t\t\t\t<li><a href=\"#\">Accueil</a></li>
    \t\t\t</ul>
    \t\t\t<form>\n\t\t\t\t<input type=\"search\" name=\"q\" placeholder=\"Search\"/>\n\t\t\t\t<input type=\"submit\" value=\"Launch\"/>\n\t\t\t</form>
    \t\t</nav>\n" >> ${FILENAME}
}

function make_article
{
    echo -e "\t\t\t<article>
    \t\t\t\t<h2>En-tete d'article</h2>
    \t\t\t\t<p>Paragraphe d'article</p>
    \t\t\t\t<h3>Sous-titre d'article</h3>
    \t\t\t\t<p>Paragraphe d'article</p>
    \t\t\t</article>\n" >> ${FILENAME}
}

function make_aside
{
    echo -e "\t\t\t<aside>
    \t\t\t\t<h2>En-tete aside</h2>
    \t\t\t\t<ul>
    \t\t\t\t\t<li><a href=\"#\">Accueil</a></li>
    \t\t\t\t</ul>
    \t\t\t\t<p>Paragraphe aside</p>
    \t\t\t</aside>\n" >> ${FILENAME}
}

function make_header
{
    echo -e "\t\t<header>
    \t\t\t<h1>Titre principal</h1>
    \t\t</header>\n" >> ${FILENAME}
}

function make_body
{
    echo -e "\t<body>\n" >> ${FILENAME}
    make_nav
    make_header
    echo -e "\t\t<main>\n" >> ${FILENAME}
    make_article
    make_aside
    echo -e "\t\t</main>\n" >> ${FILENAME}
    make_footer
    if [[ -n ${JS} && -f ${JS} ]]; then
	echo -e "\t\t<script src=\"${JS}\"></script>\n" >> ${FILENAME}
    fi
    echo -e "\t</body>\n" >> ${FILENAME}
}

function make_html_squeletor
{
    echo -e "<!DOCTYPE html>\n" >> ${FILENAME}
    echo -e "<html lang=\"fr-fr\">\n" >> ${FILENAME}
    make_head ${1}
    make_body 
    echo -e "</html>\n" >> ${FILENAME}
}

if [[ $# -lt 2 || $# -gt 4 ]]; then
    usage
fi

if [[ -f ${FILENAME} ]]; then
    while [[ -z ${answer_erase} ]] || ! [[ ${answer_erase} =~ "n" || ${answer_erase} =~ "y" ]]
    do
	read -n1 -p "\n${FILENAME} already exists. Do you want to erase it?[y/n]: " answer_erase
    done
    if [[ ${answer_erase} =~ "y" ]]; then
	rm -rf ${FILENAME}
    fi
fi
make_html_squeletor ${2}
