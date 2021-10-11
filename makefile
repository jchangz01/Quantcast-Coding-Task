# building
all: most_active_cookie.cpp 
	g++ -std=c++11 -o most_active_cookie most_active_cookie.cpp

# cleaning
clean:
	rm most_active_cookie