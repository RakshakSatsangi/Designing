d=-DDEBUG

all:	cop-app
	export LD_LIBRARY_PATH=/usr/include/SFML/lib && ./Executables/cop-app $(PORT) $(HOST)

cop-app:  main.o player.o globals.o menu.o ball.o Goal.o
	g++ Objects/main.o Objects/player.o Objects/globals.o Objects/menu.o Objects/ball.o Objects/Goal.o -o cop-app -L /usr/include/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	mv cop-app Executables/cop-app

main.o:   src/main.cpp
	g++ -c src/main.cpp -I /usr/include/SFML/include
	mv main.o Objects/main.o


player.o:   src/player.cpp
	g++ -c src/player.cpp -I /usr/include/SFML/include
	mv player.o Objects/player.o

globals.o:   src/globals.cpp
	g++ -c src/globals.cpp -I /usr/include/SFML/include		
	mv globals.o Objects/globals.o

menu.o:   src/menu.cpp
	g++ -c src/menu.cpp -I /usr/include/SFML/include
	mv menu.o Objects/menu.o

ball.o:   src/ball.cpp
	g++ -c src/ball.cpp -I /usr/include/SFML/include	
	mv ball.o Objects/ball.o

Goal.o:   src/Goal.cpp
	g++ -c src/Goal.cpp -I /usr/include/SFML/include	
	mv Goal.o Objects/Goal.o




alldebug:	cop-appdebug
	export LD_LIBRARY_PATH=SFML-2.1/lib && ./Executables/cop-appdebug $(PORT) $(HOST)

cop-appdebug:  maindebug.o playerdebug.o globalsdebug.o menudebug.o balldebug.o Goaldebug.o
	g++ $(d) Objects/maindebug.o Objects/playerdebug.o Objects/globalsdebug.o Objects/menudebug.o Objects/balldebug.o Objects/Goaldebug.o -o cop-appdebug -L SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	mv cop-appdebug Executables/cop-appdebug

maindebug.o:   src/main.cpp
	g++ $(d) -c src/main.cpp -I /usr/include/SFML/include
	mv main.o Objects/maindebug.o


playerdebug.o:   src/player.cpp
	g++ $(d) -c src/player.cpp -I /usr/include/SFML/include
	mv player.o Objects/playerdebug.o

globalsdebug.o:   src/globals.cpp
	g++ $(d) -c src/globals.cpp -I /usr/include/SFML/include		
	mv globals.o Objects/globalsdebug.o

menudebug.o:   src/menu.cpp
	g++ $(d) -c src/menu.cpp -I /usr/include/SFML/include
	mv menu.o Objects/menudebug.o

balldebug.o:   src/ball.cpp
	g++ $(d) -c src/ball.cpp -I /usr/include/SFML/include	
	mv ball.o Objects/balldebug.o

Goaldebug.o:   src/Goal.cpp
	g++ $(d) -c src/Goal.cpp -I /usr/include/SFML/include	
	mv Goal.o Objects/Goaldebug.o




alldebug1:
	g++ -c cop.cpp -I SFML-2.1/include
	g++ cop.o -o cop-appdebug -L /usr/include/SFMLlib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	export LD_LIBRARY_PATH=/usr/include/SFML/lib && ./cop-appdebug 40000





all1:
	g++ -c cop.cpp -I SFML-2.1/include
	g++ cop.o -o cop-app -L /usr/include/SFMLlib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	export LD_LIBRARY_PATH=/usr/include/SFML/lib && ./cop-app 40000

