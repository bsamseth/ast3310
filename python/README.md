# A note on the Python scripts
The programs written in Python are for the most part completely
undocumented. This is simply due to the rather trivial nature of the
code; it invokes the main C++ application to produce data for some
inputs, and then makes various plots of the data. In addition, much
care has not been taken in order to clean the code, so parts of it is
quite messy.

Most relevant are the [plot.py](plot.py) and [plot3.py](plot3.py) files, they produce the most relevant plots, based on data assumed to be in `../build/output.dat`. The best way to run these are through the [run script](../build_run_plot.sh).
