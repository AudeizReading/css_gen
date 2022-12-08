CSS_GEN
=======

Petit programme permettant, à partir d'un fichier HTML à structure *simple*, de générer la base du fichier de travail CSS correspondant. Une balise `<link rel="filename"/>` est ajoutée au fichier HTML fourni en argument du programme.

Seulement une base de travail simplifiée est générée, c'est-à-dire, que seulement les tags *, et non leurs propriétés,* seront récupérés et insérés au format CSS dans le fichier de travail CSS. Les tags sont insérés par ordre alphabétique et de façon unique. Le développeur est libre d'ajouter par la suite les tags qu'il a besoin de gérer.

```css
tag1 {
}

tag2 {
}

tag3 {
}
...

tagN {
}
```

Le programme est accompagné d'un script `bash` générant un fichier HTML basique.

Installation
------------
Lors de la première utilisation, il faut générer l'exécutable. *Bien entendu, `.zshrc` est à remplacer par le nom du fichier de configuration du shell que vous utilisez. Essayez de vous positionner intelligemment dans votre système de fichiers pour, soit ne pas avoir à rajouter ce chemin à `PATH`, soit ne pas autoriser l'exécution dans un endroit critique de votre système de fichiers*:
```
git clone git@github.com:AudeizReading/css_gen.git css_gen
cd ./css_gen
make
p_wd=`pwd` && echo "export PATH=\"\${PATH}:${p_wd}\"" >> ~/.zshrc
source ~/.zshrc
```
Ainsi le programme sera accessible partout où vous en aurez besoin, pas besoin de rester dans ce répertoire pour travailler impérativement. Cela dit, rester dans le répertoire permet de:
- Travailler avec le modèle HTML généré.
-  Utiliser l'instruction `make test` pour obtenir un échantillon d'un fichier HTML et de son fichier CSS associé.

## Utilisation

`HTML_filename`: nom du fichier HTML que l'on va générer *(index.html, pouet.html...)*
`Titre_de_la_page`: titre de la page HTML, balises `<title></title>`. *Un seul mot, car le parsing de ce côté est fait en bash et n'est pas adapté aux titres en plusieurs mots. En outre, il s'agit du titre que l'on peut lire dans l'onglet d'un navigateur, un mot est amplement suffisant pour cette tâche.*
```shell
./html_squeletor_generator.sh HTML_filename "Titre_de_la_page"
```
`HTML_filename`: nom du fichier HTML *(index.html, pouet.html...)*. Il s'agit du même fichier HTML dont on s'est servi plus haut.
`CSS_filename`: nom du fichier CSS que l'on va générer *(style.css...)*
```shell
./css_gen HTML_filename CSS_filename
```
## Illustration

Aperçu des fichiers générés
```html
<!DOCTYPE html>

<html lang="fr-fr">

	<head>
 		<link rel="style.css"/>
   		<meta charset="utf-8"/>
    		<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    		<title>Test_Me</title>

	</head>

	<body>

		<nav>
    			<ul>
    				<li><a href="#">Accueil</a></li>
    			</ul>
    			<form>
				<input type="search" name="q" placeholder="Search"/>
				<input type="submit" value="Launch"/>
			</form>
    		</nav>

		<header>
    			<h1>Titre principal</h1>
    		</header>

		<main>

			<article>
    				<h2>En-tete d'article</h2>
    				<p>Paragraphe d'article</p>
    				<h3>Sous-titre d'article</h3>
    				<p>Paragraphe d'article</p>
    			</article>

			<aside>
    				<h2>En-tete aside</h2>
    				<ul>
    					<li><a href="#">Accueil</a></li>
    				</ul>
    				<p>Paragraphe aside</p>
    			</aside>

		</main>

		<footer>
    			<p>Paragraphe de footer</p>
    		</footer>
	</body>

</html>
```

Fichier CSS correspondant: seules les balises au sein de `<body>` sont intégrées à la feuille de style. 
```css
a {
}

article {
}

aside {
}

body {
}

footer {
}

form {
}

h1 {
}

h2 {
}

h3 {
}

header {
}

input {
}

li {
}

main {
}

nav {
}

p {
}

ul {
}
```
## Conclusion
Ce programme n'est pas adapté pour les imbrications un peu plus personnalisées. Il est vraiment censé générer les structures de bases d'un projet web statique. Il a été créé pendant un moment de lassitude à devoir regénérer, une nouvelle fois, ces fichiers, pour un nouveau projet. Par définition, il n'est pas parfait et toute PR utile à l'améliorer est la bienvenue