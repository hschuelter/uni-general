CC = g++
RS = r_search.cpp utils.cpp
SA = s_anneal.cpp utils.cpp
FLAGS = -std=c++11 # -Wall 

all:
	$(CC) $(SA) -o sa.out $(FLAGS)
	$(CC) $(RS) -o rs.out $(FLAGS)

	./scripts/runnable.sh


chart:
	./scripts/charts.sh

compile:
	$(CC) $(SA) -o sa.out $(FLAGS)
	$(CC) $(RS) -o rs.out $(FLAGS)


clean:
	rm *.out
	# rm -rf __pycache__
