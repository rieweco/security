CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/ssl/include -L${HOME}/usr/local/ssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/c/carc35/usr/local/ssl/lib
DEBUG = -g
TARGET	= crackIt
OBJS	= crackIt.o

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

crackIt.o:	crackIt.cpp crackIt.h
	$(CC) -c crackIt.cpp

clean:
	rm -f *.o $(TARGET)
