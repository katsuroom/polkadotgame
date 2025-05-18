LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
FLAGS = -Wl,--subsystem,windows -O3

RES = bin/resource.rc.data

all:
	g++ -Iinclude src/*.cpp -Llib $(LIBS) -o ./main.exe

release: bin/resource.rc.data
	g++ -Iinclude $(FLAGS) src/*.cpp $(RES) -Llib $(LIBS) -o ./polkadotgame.exe

%.rc.data:
	mkdir -p bin
	windres src/resource.rc -o $(RES)

clean:
	rm -r bin