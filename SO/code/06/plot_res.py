import sys
import os
import pandas as pd
import matplotlib.pyplot as plt

def plot_results(csv_file, output_folder):
    
    # check esistenza file csv
    if not os.path.isfile(csv_file):
        print(f"Errore: file CSV '{csv_file}' non trovato.")
        sys.exit(1)

    # verifica colonne richieste
    try:
        data = pd.read_csv(csv_file)
    except Exception as e:
        print(f"Errore durante la lettura del file CSV: {e}")
        sys.exit(1)

    required_columns = {"nome_programma", "page_ref", "page_faults"}
    if not required_columns.issubset(data.columns):
        print(f"Errore: il file CSV deve contenere le colonne {required_columns}.")
        sys.exit(1)

    # marker per i plot
    markers = ['o', 's', 'D', '^', 'v', 'p', '*', 'h', 'x', '+']
    marker_index = 0

    plt.figure(figsize=(10, 6))
    for program in data["nome_programma"].unique():
        print(f"Sto aggiungendo l'algoritmo {program} al plot...")
        program_data = data[data["nome_programma"] == program]
        plt.plot(
            program_data["page_ref"], 
            program_data["page_faults"], 
            marker=markers[marker_index % len(markers)], 
            label=program
        )
        marker_index += 1

    plt.title("Page faults")
    plt.xlabel("Page references")
    plt.ylabel("Page faults")
    plt.legend(title="Programmi")
    plt.grid(True)

    os.makedirs(output_folder, exist_ok=True)
    output_file = os.path.join(output_folder, "page_faults_plot.png")
    plt.savefig(output_file)
    print(f"Plot salvato in: {output_file}")

    # mostra il plot
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python3 plot_res.py <file_csv> <cartella_output>")
        sys.exit(1)

    csv_file = sys.argv[1]
    output_folder = sys.argv[2]
    plot_results(csv_file, output_folder)