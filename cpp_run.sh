g++ contests/$1/code$2.cpp -I.
if [ $? -ne 0 ]; then
    exit 1
fi

# Creating final cpp file to be submitted to the system
python3 merge.py contests/$1/code$2.cpp

g++ final.cpp
if [ $? -ne 0 ]; then
    exit 1
fi

cat contests/$1/input$2.txt | ./a.out
rm a.out


