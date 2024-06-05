import matplotlib.pyplot as plt

# Llegir les dades de l'arxiu horizons.txt
data = []
with open('horizons.txt') as file:
    for line in file:
        x, y = map(float, line.split())
        data.append((x, y))

# Separar les dades en dues llistes
x_data, y_data = zip(*data)

# Valors interpolats de x per als solsticis
x_hivern = 21.138147
x_estiu = 202.865507
x_segon_hivern = 386.395609

# Crear el gràfic
plt.figure(figsize=(10, 6))
plt.plot(x_data, y_data, label='Declinació del Sol')
plt.axhline(y=0, color='r', linestyle='--', label='vimg = 0')
plt.axvline(x=x_hivern, color='g', linestyle='--', label=f'Solstici d\'hivern en x ≈ {x_hivern:.2f}')
plt.axvline(x=x_estiu, color='orange', linestyle='--', label=f'Solstici d\'estiu en x ≈ {x_estiu:.2f}')
plt.axvline(x=x_segon_hivern, color='b', linestyle='--', label=f'Segon solstici d\'hivern en x ≈ {x_segon_hivern:.2f}')
plt.scatter([x_hivern], [0], color='g')  # Primer punt interpolat (hivern)
plt.scatter([x_estiu], [0], color='orange')  # Segon punt interpolat (estiu)
plt.scatter([x_segon_hivern], [0], color='b')  # Tercer punt interpolat (segon hivern)

# Afegir etiquetes i llegenda
plt.xlabel('Dies Julians')
plt.ylabel('Declinació (graus)')
plt.title('Declinació del Sol vs. Temps')
plt.legend()
plt.grid(True)
plt.show()
