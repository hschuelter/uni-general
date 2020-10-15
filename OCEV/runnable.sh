make
clear; clear

# echo "" > "./Results/all-final-2.txt"

# echo "Maze:"
# echo "---------- Maze: ----------" >> "./Results/all-final-2.txt"
# file="./Charts/maze"
# ./a.out -v 100 -p 50 -c 1 -S 0 -X 2 -M 1 -F 3 -l 0 -u 3 -g 5000 -r 100 -k 4 -K 1.00 -d 4 -x 1.00 -m 0.02 -E 1 -b 1.2 -e 2.0 -a 0.8 -A 0.5 -R 0.6 -f $file >> "./Results/all-final-2.txt"
# python3 ./Charts/charts.py -f "$file.txt"
# python3 ./Charts/diversity_charts.py -f "$file"

# ==============================================

# echo "Keane's Bump Test:"
# echo "" >> "./Results/all-final-2.txt"
# echo "---------- Keane's Bump Test: ----------" >> "./Results/all-final-2.txt"
# file="./Charts/keane-bump-roleta"
# ./a.out -v 50 -p 50 -c 3 -S 0 -X 4 -M 3 -F 4 -l 0 -u 10 -g 100000 -r 100 -k 4 -K 1.00 -d 4 -x 0.95 -m 0.02 -E 1 -b 1.2 -e 2.0 -a 0.8 -A 0.5 -R 0.6 -f $file >> "./Results/all-final-2.txt"
# python3 ./Charts/charts.py -f "$file.txt"
# python3 ./Charts/diversity_charts.py -f "$file"

# ==============================================
#
echo "Michalewicz:"
echo "" >> "./Results/all-final-2.txt"
echo "---------- Michalewicz: ----------" >> "./Results/all-final-2.txt"
file="./Charts/michalewicz-roleta"
./a.out -v 50 -p 50 -c 3 -S 0 -X 4 -M 4 -F 5 -l 0 -u 3.1415 -g 50000 -r 100 -k 4 -K 1.00 -d 4 -x 1.00 -m 0.01 -E 1 -b 1.2 -e 2.0 -a 0.8 -A 0.5 -R 0.6 -f $file >> "./Results/all-final-2.txt"
# python3 ./Charts/charts.py -f "$file.txt"
# python3 ./Charts/diversity_charts.py -f "$file"

# ==============================================

# make clean
