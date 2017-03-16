import regression
import sys
import numpy as np

"""
Usage: regression csv_file state_order output_file
where csv_file is a .csv file containing the logs
and state_order is a string showing the location of the data.
state_order has 'x' for a state variable and 'u' for an input variable,
so if the .csv file had "state1, input1, debug, state2",
state_order would be "xu-x".
"""

if not (len(sys.argv) == 3 or len(sys.argv) == 4):
    print("Arguments must be a csv file and the order of states.")
    exit()

csv = np.loadtxt(open(sys.argv[1], "rb"), delimiter=",", skiprows=1)
order = sys.argv[2]

xt, ut = regression.seperate_data(csv, order)
A, B = regression.state_space_regression(xt, ut)

if(len(sys.argv) == 4):
  np.savez(sys.argv[3], A=A, B=B)
else:
  print("Matrix A:")
  print(A)
  print("Matrix B:")
  print(B)
