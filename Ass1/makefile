EXTE= -lpthread -lGL -lGLU -lglut
d=-DDEBUG
LATEX=doc/latex
all: makea
execute: makea
	cd Executables;   ./makea $(NUM_THREADS)

maindebug: gdbdebug
	cd Executables;   gdb ./gdbdebug $(NUM_THREADS)

debugg: coutdebug
	cd Executables;   ./coutdebug $(NUM_THREADS)

3dim: three
	cd Executables;		./three

makea: main.o ball.o physics.o window.o gui.o
	g++ -o makea Objects/main.o Objects/ball.o Objects/physics.o Objects/window.o Objects/gui.o $(EXTE)
	mv makea Executables/makea

gdbdebug: maingdb.o ballgdb.o physicsgdb.o windowgdb.o guigdb.o
	g++ -g -o gdbdebug Objects/maingdb.o Objects/ballgdb.o Objects/physicsgdb.o Objects/windowgdb.o Objects/guigdb.o $(EXTE)
	mv gdbdebug Executables/gdbdebug

coutdebug: maincout.o ballcout.o physicscout.o windowcout.o guicout.o
	g++ $(d) -o coutdebug Objects/maincout.o Objects/ballcout.o Objects/physicscout.o Objects/windowcout.o Objects/guicout.o $(EXTE)
	mv coutdebug Executables/coutdebug

three: 	
	g++ src/3d/main.cpp -lpthread -lGL -lGLU -lglut -o three
	mv three Executables/three




main.o: src/main.cpp
	g++ $(EXTE) -c src/main.cpp
	mv main.o Objects/main.o

ball.o: src/ball.cpp 
	g++ $(EXTE) -c src/ball.cpp
	mv ball.o Objects/ball.o

physics.o: src/physics.cpp
	g++ $(EXTE) -c src/physics.cpp
	mv physics.o Objects/physics.o

window.o: src/window.cpp
	g++ $(EXTE) -c src/window.cpp
	mv window.o Objects/window.o

gui.o: src/gui.cpp
	g++ $(EXTE) -c src/gui.cpp
	mv gui.o Objects/gui.o

maingdb.o: src/main.cpp
	g++ -g $(EXTE) -c src/main.cpp
	mv main.o Objects/maingdb.o

ballgdb.o: src/ball.cpp 
	g++ -g $(EXTE) -c src/ball.cpp
	mv ball.o Objects/ballgdb.o

physicsgdb.o: src/physics.cpp
	g++ -g $(EXTE) -c src/physics.cpp
	mv physics.o Objects/physicsgdb.o

windowgdb.o: src/window.cpp
	g++ -g $(EXTE) -c src/window.cpp
	mv window.o Objects/windowgdb.o

guigdb.o: src/gui.cpp
	g++ -g $(EXTE) -c src/gui.cpp
	mv gui.o Objects/guigdb.o

maincout.o: src/main.cpp
	g++ $(d) $(EXTE) -c src/main.cpp
	mv main.o Objects/maincout.o

ballcout.o: src/ball.cpp 
	g++ $(d) $(EXTE) -c src/ball.cpp
	mv ball.o Objects/ballcout.o

physicscout.o: src/physics.cpp
	g++ $(d) $(EXTE) -c src/physics.cpp
	mv physics.o Objects/physicscout.o

windowcout.o: src/window.cpp
	g++ $(d) $(EXTE) -c src/window.cpp
	mv window.o Objects/windowcout.o

guicout.o: src/gui.cpp
	g++ $(d) $(EXTE) -c src/gui.cpp
	mv gui.o Objects/guicout.o

main3.o: src/3d/main.cpp
	g++ $(EXTE) -c src/3d/main.cpp
	mv main.o Objects/main3.o

ball3.o: src/3d/ball.cpp 
	g++ $(EXTE) -c src/3d/ball.cpp
	mv ball.o Objects/ball3.o

physics3.o: src/3d/physics.cpp
	g++ $(EXTE) -c src/3d/physics.cpp
	mv physics.o Objects/physics3.o

window3.o: src/3d/window.cpp
	g++ $(EXTE) -c src/3d/window.cpp
	mv window.o Objects/window3.o

gui3.o: src/3d/gui.cpp
	g++ $(EXTE) -c src/3d/gui.cpp
	mv gui.o Objects/gui3.o

cube3.o: src/3d/cube.cpp
	g++ $(EXTE) -c src/3d/cube.cpp
	mv cube.o Objects/cube3.o

clean:
	rm -rf Objects/*.o 
	rm -rf Executables/makea
	rm -rf Executables/gdbdebug
	rm -rf Executables/coutdebug
	rm -rf Executables/three

doc: docu design_doc.pdf readme.pdf changes.pdf
docu: 
	cd $(LATEX) && make -f Makefile
	mv $(LATEX)/refman.pdf PDFs/refman.pdf 

design_doc.pdf: doc/design_doc.tex
		cd doc;  pdflatex design_doc.tex
		mv doc/design_doc.pdf PDFs/design_doc.pdf

readme.pdf: doc/readme.tex
		cd doc;  pdflatex readme.tex
		mv doc/readme.pdf PDFs/readme.pdf

changes.pdf: doc/changes.tex
		cd doc;  pdflatex changes.tex
		mv doc/changes.pdf PDFs/changes.pdf









		









