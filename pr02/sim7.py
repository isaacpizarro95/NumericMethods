import matplotlib.pyplot as plt
import numpy as np

# Funció per a traçar l'òrbita des d'un fitxer
def plot_orbit(filename, label):
    data = np.loadtxt(filename)
    x = data[:, 1]
    y = data[:, 2]
    plt.plot(x, y, label=label)

# Crear la figura
plt.figure(figsize=(10, 6))

# Traçar les òrbites amb diferents constants de Jacobi
plot_orbit('orbita_lyapunov.txt', 'c = 3.196255396314419') # x = -0.8291710221854511
plot_orbit('orbita_c1.txt', 'c = 3.17') # x = -0.8179753540007596
plot_orbit('orbita_c2.txt', 'c = 3') # x = -0.7592221825317479
plot_orbit('orbita_c3.txt', 'c = 2.95') # x = -0.6947469451159167
plot_orbit('orbita_c4.txt', 'c = 2.93') # x = -0.7882175095472678

# Coordenades de la Terra i la Lluna
lluna_x, lluna_y = -0.987849414390376, 0

# # Afegir la Terra
# plt.scatter(terra_x, terra_y, color='blue', s=100, label='Terra')
# plt.text(terra_x, terra_y, ' Terra', verticalalignment='bottom', horizontalalignment='right')

# Afegir la Lluna
plt.scatter(lluna_x, lluna_y, color='gray', s=100, label='Lluna')
plt.text(lluna_x, lluna_y, ' Lluna', verticalalignment='bottom', horizontalalignment='left')

# Etiquetes i títol del gràfic
plt.xlabel('x')
plt.ylabel('y')
plt.title('Òrbites de Lyapunov amb Diferents Constants de Jacobi')

# Llegenda i quadrícula
plt.legend()
plt.grid(True)

# Assegurar que la relació d'aspecte és igual
plt.axis('equal')

# Mostrar el gràfic
plt.show()


