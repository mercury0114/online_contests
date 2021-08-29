g++ $1/code$2.cpp -I. -D_GLIBCXX_DEBUG
if [ $? -ne 0 ]; then
    exit 1
fi

# Creating the final cpp file to be submitted to the system
python3 merge.py $1/code$2.cpp

g++ final.cpp -D_GLIBCXX_DEBUG
if [ $? -ne 0 ]; then
    exit 1
fi

cat $1/input$2.txt | ./a.out
rm a.out
