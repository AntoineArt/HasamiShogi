/*
	contains a language
*/
typedef struct TEXTS {
	char* mainMenu[10];
	char* rules[20];
	char* options[10];
	char* inGame[10];
} Texts;

Texts frText = {
mainMenu : {"Nouvelle partie", "Continuer","Parametres","Regles","Quitter"},
options : {"Francais","Anglais", "Plein ecran", "Son", "Pack de textures", "Precedent"},
inGame : {"Suivant", "Precedent"}
};

Texts enText = {
mainMenu : {"New game", "Continue", "Parameters", "Rules", "Quit"},
options : {"French", "English", "Fullscreen", "Sound", "Texture pack", "Previous"},
inGame : {"Next", "Previous"}
};
