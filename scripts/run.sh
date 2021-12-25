#!/bin/bash
g++ -c ../src/*.cpp -I/usr/local/SFML-2.5.1/include
mv *.o ../out/
g++ ../out/*.o -o ../sfml-app -L/usr/local/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=/usr/local/SFML-2.5.1/lib && ../sfml-app