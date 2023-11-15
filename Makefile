LIBS := -lsfml-window -lsfml-system -lsfml-graphics -lGL -lGLEW -lassimp
FILES := ./Renderer.cpp ./Mesh.cpp ./Shader.cpp ./Camera.cpp ./Object.cpp ./Model.cpp ./Input.cpp
OBJECTS := Renderer.o Mesh.o Shader.o Camera.o Object.o Model.o Input.o

compile:./Renderer.cpp
	g++ -c $(FILES) 
	g++ $(OBJECTS) -o app $(LIBS) 

run:
	./app

clean:
	rm .*\.o app