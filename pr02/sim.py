import matplotlib.pyplot as plt
import numpy as np

# Llegir dades de orbita_lyapunov.txt
data = np.loadtxt('orbita_lyapunov.txt')
x = data[:, 1]
y = data[:, 2]

# Graficar l'òrbita
plt.figure(figsize=(10, 6))
plt.plot(x, y, label='Òrbita de Lyapunov')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Òrbita de Lyapunov')
plt.legend()
plt.grid(True)
#plt.axis('equal')
plt.xlim(-0.8475, -0.8275)
plt.show()
