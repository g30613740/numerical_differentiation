import matplotlib.pyplot as plt
import numpy as np
import math
import sys


f = open ("parameters.txt", "r")

M_viz = int (f.readline ())
M = int (f.readline ())
shredded_M = int (f.readline ())

x_viz = list (map (float, f.readline ()).split ())
y_viz = list (map (float, f.readline ()).split ())
x = list (map (float, f.readline ()).split ())
nm_derivative = list (map (float, f.readline ()).split ())
shredded_x = list (map (float, f.readline ().split ()))
shredded_nm_derivative = list (map (float, f.readline ().split ()))
updated_runge_solution = list (map (float, f.readline ().split ()))

f.close ()

fig, ax = plt.subplots (10, 6)                                                                         # create plot
ax.plot (x_viz, y_viz, linewidth=2, label="Analytical derivative", color="black")                                           # draw f'(x)
ax.plot (x, nm_derivative, "o", markersize=6, color="green", label="Numerical, h")
ax.plot (shredded_x, shredded_nm_derivative, "o", markersize=6, color="red", label="Numerical, h/2")
ax.plot (x, updated_runge_solution, "o", markersize=6, color="blue", label="Runge-improved")

ax.set_xlabel ("x", fontsize=12)
ax.set_ylabel ("f'(x)", fontsize=12)
ax.set_title ("Comparsion of Derivatives", fontsize=14)
ax.grid (True, linestyle="--", alpha=0.6)
ax.legend (loc="best")

plt.savefig ("plot.png", dpi=150, bbox_inches="tight")
print ("Plot saved as plot.png")

plt.show ()