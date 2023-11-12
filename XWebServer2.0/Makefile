CXX ?= g++

DEBUG ?= 1

ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

Xserver: main.cpp  ./timer/timer.cpp ./http/http.cpp ./log/log.cpp ./pool/sqlconn_pool.cpp  ./server/server.cpp ./config/config.cpp
	$(CXX) -o Xserver  $^ $(CXXFLAGS) -pthread -lmysqlclient -w

clean:
	rm  -r server
