# Run python:
export PYTHONPATH=~/Desktop/my_projects_linux/kickstart/:$PYTHONPATH

declare -i count=0
while [ $? -eq 0 ]
do
    echo "Generating $count"
    count=$(( count + 1 ))
    python3 $1/generate$2.py >input.txt
    echo "Running code"
    cat input.txt | python3 $1/code$2.py # >my_output.txt
    echo "Code executed"
    # cat input.txt | python3 $1/dummy.py >dummy_output.txt
    # cmp my_output.txt dummy_output.txt
done

