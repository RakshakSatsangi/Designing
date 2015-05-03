EXTE= -lssl -lcrypto
d=-DDEBUG

all: makea src/myDropBox/build-mainWindow-Desktop-Debug/Makefile src/myDropBox/build-mainWindow-Desktop-Debug/mainWindow
	cd src/myDropBox/build-mainWindow-Desktop-Debug; make first

server: makea
	cd src; ./makea $(PORTNO)

client: src/myDropBox/build-mainWindow-Desktop-Debug/Makefile
	cd src/myDropBox/build-mainWindow-Desktop-Debug; make first
	cd src/myDropBox/build-mainWindow-Desktop-Debug; ./mainWindow

clean: src/myDropBox/build-mainWindow-Desktop-Debug/Makefile
	cd src/myDropBox/build-mainWindow-Desktop-Debug; make clean
	rm -rf src/makea
	rm -rf src/coutdebug

debugg: coutdebug
	cd src;   ./coutdebug $(PORTNO)

makea: src/mainser.cpp
	cd src; g++ mainser.cpp -o makea $(EXTE)

coutdebug: src/mainser.cpp
	cd src; g++ $(d) -o coutdebug mainser.cpp $(EXTE)





		









