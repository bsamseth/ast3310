#! /bin/bash
cd build
make
./main.x "$1" "$2" "$3" "$4"
cd ../python
python plot.py
cd ..
