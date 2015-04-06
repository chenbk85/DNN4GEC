vpath %.cpp src/
vpath %.h include/

SRC_PATH=src
OUT_PATH=bin
HEAD_PATH=include

RELY=main.cpp DNN.cpp DNN.h tool.cpp bp.cpp train.cpp test.cpp 
FILES = main.cpp DNN.cpp tool.cpp bp.cpp train.cpp test.cpp
SOURCES = $(FILES:%.cpp=$(SRC_PATH)/%.cpp)


CC=g++
CFLAGS=-O3


run:${RELY}
	${CC} -o ${OUT_PATH}/$@ -I ${HEAD_PATH} ${CFLAGS} ${SOURCES}

clean:
	rm run
