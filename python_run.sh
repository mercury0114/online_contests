# Run python:
export PYTHONPATH=~/Desktop/my_projects_linux/kickstart/:$PYTHONPATH
cat $1/input$2.txt | python3 $1/code$2.py

tail -n +3 $1/code$2.py >temp.py
cat utilities.py temp.py >final.py
rm temp.py

