arq="uf20-01"

reset
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\tSchedule %d",$schedule;  
    python3 ./scripts/grafico.py -f ${arq} -s ${schedule}
    echo " - OK"    

done

    python3 scripts/box.py -f ${arq}

arq="uf100-01"
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\tSchedule %d",$schedule;  
    python3 ./scripts/grafico.py -f ${arq} -s ${schedule}
    echo " - OK"    

done

    python3 scripts/box.py -f ${arq}

arq="uf250-01"
echo "${arq}"
for schedule in `seq 0 9`
do
    printf "\tSchedule %d",$schedule;  
    python3 ./scripts/grafico.py -f ${arq} -s ${schedule}
    echo " - OK"    
done

    python3 scripts/box.py -f ${arq}