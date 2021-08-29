set -e

if [ ! -z $1 ]; then
    # Running specific test
    echo $1
    g++ tests/$1 -I.
    ./a.out
    exit 0
fi

# Running all tests
echo "prime_related_test.cpp"
g++ tests/prime_related_test.cpp -I.
./a.out

echo "trees_test.cpp"
g++ tests/trees_test.cpp -I.
./a.out

echo "utilities_test.cpp"
g++ tests/utilities_test.cpp -I.
./a.out

echo "graph_test.cpp"
g++ tests/graph_test.cpp -I.
./a.out
