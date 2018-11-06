Le code fourni permet d'acquérir des chaînes de caractères d'un fichier et de les afficher à l'écran.  

Le répertoire est organisé ainsi : 
.
├── builds
├── code_test
│   └── ut_list.c
├── doc
├── Doxyfile
├── include
│   ├── dicoG1.h
│   ├── fsmG1.h
│   ├── fsm.h
│   ├── global.h
│   ├── gram1.h
│   ├── hach.h
│   ├── lex.h
│   ├── list.h
│   ├── notify.h
│   ├── secData.h
│   ├── secText.h
│   ├── symb.h
│   └── symbolManager.h
├── Livrable1_SICOM_Vincent_Loibl_Lucien_Salmon.pdf
├── Makefile
├── README.txt
├── src
│   ├── dicoG1.c
│   ├── fsm.c
│   ├── fsmG1.c
│   ├── gram1.c
│   ├── hach.c
│   ├── lex.c
│   ├── list.c
│   ├── main.c
│   ├── secData.c
│   └── secText.c
└── tests
    ├── miam_sujet.s
    ├── simpledico.dico
    ├── simple_test.txt
    ├── test1.c
    └── testG1data.txt

6 directories, 33 files

- tests : contient les fichiers pour tester le programme 
- src : qui contient le code C de votre interpréteur.      
- include : qui contient toutes les définitions de types et prototypes de votre programme. Lisez attentivement les headers avant de commencer à coder et de les modifier.
- doc : contient la documentation et le répertoire ou stocker les rapports de livrable.
- README.txt : ce document
- Makefile pour compiler soit en mode debug (afficher les traces du programme) soit en mode release (produit final)
- Doxyfile : fichier de configuration du générateur automatique de documentation doxygen


--- plusieurs tests sont disponibles:
-un test de la structure de file circulaire
$ make testlist
$ ./ut_list.exe
-le test de la machine à etat et de l'analyse lexicale et grammaire
$ make debug
$ make run
make run permet de lancer l'analyse pour le fichier testG1data.txt et simpledico.dico


--- pour compiler le code en mode debug (il créé l'exécutable 'as-mips' qui affiche les traces)
$ make debug 



--- pour l'executer 
$ ./as-mips FICHIER.S


--- pour compiler le code en mode release (il créé l'exécutable 'as-mips' qui n'affiche pas les traces. En tant que développeur, vous utiliserez très rarement cette commande)
$ make release 


--- Génération de l'archive 

Tapez "make archive". Vous aurez produit un fichier se terminant par "tgz". C'est l'archive 
que vous nous enverrez par email. 



--- Documentation du code

Si vous voulez documenter votre code, regardez la syntaxe appropriée pour 
les tags Doxygen : 

http://www.stack.nl/~dimitri/doxygen/docblocks.html

Une fois votre code commente, tapez "make documentation" (nous vous fournissons
un Doxyfile qui ira bien pour ce que vous avez a faire). 

Note : il faut avoir installé le package doxygen. Sous Ubuntu / Debian, tapez : 
sudo apt-get install doxygen
