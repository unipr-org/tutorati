#!/usr/bin/env python3
"""
Script per eseguire scenari dello scheduler, visualizzare metriche e diagrammi di Gantt.
Uso: python3 scenarios.py scenario1 scenario2 ...
"""

import subprocess
import sys
import os
import csv

try:
    import matplotlib.pyplot as plt
    import matplotlib.patches as mpatches
    import numpy as np
    HAS_MATPLOTLIB = True
except ImportError:
    HAS_MATPLOTLIB = False
    print("Attenzione: matplotlib/numpy non disponibili, i grafici non verranno generati.")


SCENARIOS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "scenarios")
SCHEDULER_BIN = os.path.join(os.path.dirname(os.path.abspath(__file__)), "scheduler")


def run_scenario(name):
    """Esegue lo scheduler per uno scenario."""
    scenario_path = os.path.join(SCENARIOS_DIR, name)
    if not os.path.isdir(scenario_path):
        print(f"Errore: scenario '{name}' non trovato in {SCENARIOS_DIR}")
        return False

    result = subprocess.run(
        [SCHEDULER_BIN, "--scenario", scenario_path],
        capture_output=True, text=True
    )

    if result.returncode != 0:
        print(f"Errore esecuzione scenario '{name}':")
        print(result.stderr)
        return False

    print(result.stdout.strip())
    return True


def read_results(name):
    """Legge results.csv di uno scenario."""
    path = os.path.join(SCENARIOS_DIR, name, "results.csv")
    rows = []
    comments = []
    header = None

    with open(path, "r") as f:
        for line in f:
            line = line.strip()
            if line.startswith("#"):
                comments.append(line[2:])
                continue
            if not line:
                continue
            if header is None:
                header = line.split(",")
                continue
            parts = line.split(",")
            row = dict(zip(header, parts))
            rows.append(row)

    return rows, comments


def read_gantt(name):
    """Legge gantt.csv di uno scenario."""
    path = os.path.join(SCENARIOS_DIR, name, "gantt.csv")
    rows = []

    with open(path, "r") as f:
        header = next(f).strip().split(",")
        cpu_names = header[1:]  # cpu_0, cpu_1, ...

        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split(",")
            tick = int(parts[0])
            assignments = parts[1:]
            rows.append((tick, assignments))

    return cpu_names, rows


def print_table(name, rows, comments):
    """Stampa una tabella formattata con le metriche."""
    print(f"\n{'=' * 60}")
    print(f"  Scenario: {name}")
    print(f"{'=' * 60}")

    if not rows:
        print("  Nessun risultato.")
        return

    # header
    cols = ["id", "arrival", "burst", "start", "completion", "turnaround", "waiting", "response"]
    widths = [max(len(c), max(len(str(r.get(c, ""))) for r in rows)) for c in cols]

    header_line = " | ".join(c.center(w) for c, w in zip(cols, widths))
    sep_line = "-+-".join("-" * w for w in widths)

    print(f"  {header_line}")
    print(f"  {sep_line}")

    for r in rows:
        line = " | ".join(str(r.get(c, "")).center(w) for c, w in zip(cols, widths))
        print(f"  {line}")

    # medie
    numeric_cols = ["turnaround", "waiting", "response"]
    avgs = {}
    for c in numeric_cols:
        vals = [int(r[c]) for r in rows if c in r]
        avgs[c] = sum(vals) / len(vals) if vals else 0

    print(f"  {sep_line}")
    avg_line = " | ".join(
        (f"{avgs[c]:.1f}" if c in numeric_cols else ("media" if c == "id" else "")).center(w)
        for c, w in zip(cols, widths)
    )
    print(f"  {avg_line}")

    # info utilizzo
    for comment in comments:
        print(f"  {comment}")

    print()


def plot_gantt(name, cpu_names, gantt_rows):
    """Genera il diagramma di Gantt."""
    if not HAS_MATPLOTLIB:
        return

    # raccogli tutti i processi
    all_procs = set()
    for _, assignments in gantt_rows:
        for a in assignments:
            if a != "-":
                all_procs.add(a)

    proc_list = sorted(all_procs)
    colors = plt.cm.Set3(np.linspace(0, 1, max(len(proc_list), 1)))
    color_map = {p: colors[i] for i, p in enumerate(proc_list)}

    n_cpus = len(cpu_names)
    fig, ax = plt.subplots(figsize=(max(8, len(gantt_rows) * 0.5), max(3, n_cpus * 1.2)))

    for cpu_idx in range(n_cpus):
        # raggruppa tick contigui dello stesso processo
        segments = []
        current_proc = None
        start_tick = 0

        for tick, assignments in gantt_rows:
            proc = assignments[cpu_idx] if cpu_idx < len(assignments) else "-"
            if proc != current_proc:
                if current_proc is not None and current_proc != "-":
                    segments.append((start_tick, tick - start_tick, current_proc))
                current_proc = proc
                start_tick = tick

        # ultimo segmento
        if current_proc is not None and current_proc != "-":
            last_tick = gantt_rows[-1][0]
            segments.append((start_tick, last_tick - start_tick + 1, current_proc))

        y = n_cpus - 1 - cpu_idx
        for start, duration, proc in segments:
            ax.broken_barh([(start, duration)], (y - 0.4, 0.8),
                           facecolors=color_map[proc], edgecolor="black", linewidth=0.5)
            ax.text(start + duration / 2, y, proc,
                    ha="center", va="center", fontsize=9, fontweight="bold")

    ax.set_yticks(range(n_cpus))
    ax.set_yticklabels(list(reversed(cpu_names)))
    ax.set_xlabel("Tick")
    ax.set_title(f"Gantt Chart - {name}")
    ax.set_xlim(-0.5, gantt_rows[-1][0] + 1.5)
    ax.grid(axis="x", alpha=0.3)

    # legenda
    patches = [mpatches.Patch(facecolor=color_map[p], edgecolor="black", label=p) for p in proc_list]
    ax.legend(handles=patches, loc="upper right", fontsize=8)

    plt.tight_layout()
    out_path = os.path.join(SCENARIOS_DIR, name, "gantt.png")
    plt.savefig(out_path, dpi=150)
    plt.close()
    print(f"  Gantt chart salvato in {out_path}")


def plot_metrics(name, rows):
    """Genera bar chart delle metriche per processo."""
    if not HAS_MATPLOTLIB:
        return

    procs = [r["id"] for r in rows]
    turnaround = [int(r["turnaround"]) for r in rows]
    waiting = [int(r["waiting"]) for r in rows]
    response = [int(r["response"]) for r in rows]

    x = np.arange(len(procs))
    width = 0.25

    fig, ax = plt.subplots(figsize=(max(6, len(procs) * 1.5), 5))
    ax.bar(x - width, turnaround, width, label="Turnaround", color="#4CAF50")
    ax.bar(x, waiting, width, label="Waiting", color="#FF9800")
    ax.bar(x + width, response, width, label="Response", color="#2196F3")

    ax.set_xlabel("Processo")
    ax.set_ylabel("Tempo (ticks)")
    ax.set_title(f"Metriche - {name}")
    ax.set_xticks(x)
    ax.set_xticklabels(procs)
    ax.legend()
    ax.grid(axis="y", alpha=0.3)

    plt.tight_layout()
    out_path = os.path.join(SCENARIOS_DIR, name, "metrics.png")
    plt.savefig(out_path, dpi=150)
    plt.close()
    print(f"  Metrics chart salvato in {out_path}")


def plot_comparison(scenario_names, all_results):
    """Genera un grafico comparativo tra scenari."""
    if not HAS_MATPLOTLIB or len(scenario_names) < 2:
        return

    avg_turnaround = []
    avg_waiting = []
    avg_response = []

    for name in scenario_names:
        rows = all_results[name]
        t = [int(r["turnaround"]) for r in rows]
        w = [int(r["waiting"]) for r in rows]
        r = [int(r["response"]) for r in rows]
        avg_turnaround.append(sum(t) / len(t) if t else 0)
        avg_waiting.append(sum(w) / len(w) if w else 0)
        avg_response.append(sum(r) / len(r) if r else 0)

    x = np.arange(len(scenario_names))
    width = 0.25

    fig, ax = plt.subplots(figsize=(max(6, len(scenario_names) * 2), 5))
    ax.bar(x - width, avg_turnaround, width, label="Avg Turnaround", color="#4CAF50")
    ax.bar(x, avg_waiting, width, label="Avg Waiting", color="#FF9800")
    ax.bar(x + width, avg_response, width, label="Avg Response", color="#2196F3")

    ax.set_xlabel("Scenario")
    ax.set_ylabel("Tempo medio (ticks)")
    ax.set_title("Confronto scenari")
    ax.set_xticks(x)
    ax.set_xticklabels(scenario_names)
    ax.legend()
    ax.grid(axis="y", alpha=0.3)

    plt.tight_layout()
    out_path = os.path.join(SCENARIOS_DIR, "comparison.png")
    plt.savefig(out_path, dpi=150)
    plt.close()
    print(f"\nGrafico comparativo salvato in {out_path}")


def main():
    if len(sys.argv) < 2:
        print("Uso: python3 scenarios.py <scenario1> [scenario2] ...")
        print("Scenari disponibili:")
        if os.path.isdir(SCENARIOS_DIR):
            for d in sorted(os.listdir(SCENARIOS_DIR)):
                if os.path.isdir(os.path.join(SCENARIOS_DIR, d)):
                    print(f"  - {d}")
        sys.exit(1)

    scenario_names = sys.argv[1:]
    all_results = {}

    for name in scenario_names:
        print(f"\n--- Esecuzione scenario: {name} ---")

        if not run_scenario(name):
            continue

        rows, comments = read_results(name)
        all_results[name] = rows

        print_table(name, rows, comments)

        cpu_names, gantt_rows = read_gantt(name)
        plot_gantt(name, cpu_names, gantt_rows)
        plot_metrics(name, rows)

    if len(all_results) >= 2:
        plot_comparison(list(all_results.keys()), all_results)


if __name__ == "__main__":
    main()
