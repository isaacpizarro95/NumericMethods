import matplotlib.pyplot as plt

# Llegir les dades de l'arxiu horizons.txt
data = []
with open('horizons.txt') as file:
    for line in file:
        x, y = map(float, line.split())
        data.append((x, y))

# Separar les dades en dues llistes
x_data, y_data = zip(*data)

# Valors interpolats de x
x_1 = 110.129205
x_2 = 296.530721

# Crear el gràfic
plt.figure(figsize=(10, 6))
plt.plot(x_data, y_data, label='Declinació del Sol')
plt.axhline(y=0, color='r', linestyle='--', label='vimg = 0')
plt.axvline(x=x_1, color='g', linestyle='--', label=f'Primavera en x ≈ {x_1:.2f}')
plt.axvline(x=x_2, color='orange', linestyle='--', label=f'Tardor en x ≈ {x_2:.2f}')
plt.scatter([x_1], [0], color='g')  # Primer punt interpolat
plt.scatter([x_2], [0], color='orange')  # Segon punt interpolat

# Afegir etiquetes i llegenda
plt.xlabel('Dies Julians')
plt.ylabel('Declinació (graus)')
plt.title('Declinació del Sol vs. Temps')
plt.legend()
plt.grid(True)
plt.show()
