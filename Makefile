CC = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lpthread
SERVER_SRCS = Server.cpp User.cpp Config.cpp
CLIENT_SRCS = Client.cpp

all : server client

server:	$(SERVER_SRCS)
	$(CC) $(SERVER_SRCS) $(CXXFLAGS) $(LIBS) -o $@

client:	$(CLIENT_SRCS)
	$(CC) $(CLIENT_SRCS) $(CXXFLAGS) -o $@

clean:
	rm -f server client
