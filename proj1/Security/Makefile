CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/ssl/include -L${HOME}/usr/local/ssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/c/carc35/usr/local/ssl/lib
DEBUG = -g
TARGET  = security
OBJS	= security.o

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

security.o:	security.cpp security.h
	$(CC) -c security.cpp

clean:
	rm -f *.o $(TARGET)
