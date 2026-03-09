import random
import csv

min = 1
max = 100

cols = 10
rows = 10

with open("matrix.csv", "w") as file:
    writer = csv.writer(file)
    for _ in range(0, rows):
        row = []
        for _ in range(0, cols):
            row.append(random.randint(min,max +1))
        writer.writerow(row)
