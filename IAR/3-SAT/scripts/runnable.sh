t0=250
tn=0.01
it=250000
schedule=5


reset
arq="uf20-01"
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\t-Schedule %d" $schedule;
    printf "\n\t\t"
    for i in `seq 0 9`
    do
        ./sa.out ${arq} ${tn} ${t0} ${it} ${schedule} ${i}
        ./rs.out ${arq} ${it} ${schedule} ${i}
        printf "%d " $i;
    done
    printf "\n"
done


arq="uf100-01"
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\t-Schedule %d" $schedule;
    printf "\n\t\t"
    for i in `seq 0 9`
    do
        ./sa.out ${arq} ${tn} ${t0} ${it} ${schedule} ${i}
        ./rs.out ${arq} ${it} ${schedule} ${i}
        printf "%d " $i;
    done
    printf "\n"
done

arq="uf250-01"
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\t-Schedule %d" $schedule;
    printf "\n\t\t"
    for i in `seq 0 9`
    do
        ./sa.out ${arq} ${tn} ${t0} ${it} ${schedule} ${i}
        ./rs.out ${arq} ${it} ${schedule} ${i}
        printf "%d " $i;
    done
    printf "\n"
done