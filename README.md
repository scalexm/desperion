#Desperion

Desperion est un émulateur pour le MMORPG Dofus 2.0 écrit en C++, actuellement compatible avec la version:
2.13.4.76020.1

Desperion utilise de nombreuses fonctionnalités C++11. Il vous faudra donc utiliser une version de gcc ou de clang (ne pensez même pas à MSVC) relativement récente: gcc >= 4.7 ou clang >= 3.2.
Attention, le projet protocol_builder inclut l'utilisation d'inheriting constructors, qui nécessitent l'utilisation de gcc >= 4.8.1 ou clang >= 3.3.

* Desperion est constitué de six projets:
	* core: bibliothèque incluant les fonctionnalités partagées par tous les projets
	* d2fstream: bibliothèque permettant de lire les différents fichiers du client Dofus
	* protocol_builder: utilitaire pour traduire les fichiers ActionScript du protocole Dofus en fichiers C++
	* login_server: serveur de connexion de l'émulateur
	* game_server: serveur de jeu de l'émulateur

Desperion est en refonte, ce qui explique l'absence du serveur de jeu pour le moment.

* Contact:
	* Mail: martin.alex32@hotmail.fr
	* Skype: alexxxxxx195
