cmake_minimum_required(VERSION 3.7)
project(Projet_C)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/App
        src/App.c
        src/App.h
        src/App.h.gch
        src/asman.ttf
        src/BackgroundMenu.bmp
        src/BlackPiece.bmp
        src/BlackSquare.bmp
        src/Board2.c
        src/Board2.h
        src/Board2.h.gch
        src/Game.c
        src/Game.h
        src/Game.h.gch
        src/IA.c
        src/IA.h
        src/Makefile
        src/RedPiece.bmp
        src/Rules.c
        src/Rules.h
        src/Rules.h.gch
        src/Rules.txt
        src/ShogiBoard.bmp
        src/WhiteSquare.bmp
        src/Yellow.bmp)

add_executable(Projet_C ${SOURCE_FILES})