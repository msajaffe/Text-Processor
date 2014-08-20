CXX=g++
XXFLAGS=-Wall -MMD
EXEC=a4q4
OBJECTS=a4q4.o textprocess.o echo.o decorator.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm ${OBJECTS}${EXEC}