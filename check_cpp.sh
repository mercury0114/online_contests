g++ $1/code$2.cpp -I./ -o my.out
g++ $1/dummy$2.cpp -I./ -o dummy.out

declare -i count=0
while [ $? -eq 0 ]
do
    echo $count
    count=$(( count + 1 ))
    python3 $1/generate$2.py >input.txt
    cat input.txt | ./my.out >my_output.txt
    cat input.txt | ./dummy.out >dummy_output.txt
    cmp my_output.txt dummy_output.txt
done
