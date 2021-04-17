import matplotlib.pyplot as plt
import matplotlib
import numpy as np


n, e_t, e_s = np.loadtxt('ex1.txt', unpack=True)

plt.yscale('log')
plt.xlabel('Subdivisions')
plt.ylabel('Error')
plt.plot(n, e_t, 'ro', label='Trapezoidal')
plt.plot(n, e_s, 'bo', label="Simpson")
plt.legend()
plt.savefig('prova.png')
