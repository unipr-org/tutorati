package it.unipr.fdpb.lecture05.es02;

import java.util.NoSuchElementException;

public class AgendaTask<T extends Task & Comparable<T>> {

    private T[] tasks;
    private int numeroTask;
    private static final int CAPACITA_MASSIMA = 100;

    public AgendaTask() {
        this.tasks = (T[]) new Task[CAPACITA_MASSIMA];
        this.numeroTask = 0;
    }

    public void aggiungiTask(T task) {
        if (task == null)
            throw new IllegalArgumentException("Task nullo non ammesso.");
        if (numeroTask >= tasks.length)
            throw new RuntimeException("Agenda piena. Capacita massima: " + tasks.length);

        int insertionPoint = 0;
        while (insertionPoint < numeroTask
                && task.compareTo(tasks[insertionPoint]) > 0) {
            insertionPoint++;
        }

        for (int i = numeroTask; i > insertionPoint; i--) {
            tasks[i] = tasks[i - 1];
        }

        tasks[insertionPoint] = task;
        numeroTask++;
    }

    public T getProssimoTask() {
        if (numeroTask == 0) {
            throw new NoSuchElementException("L'agenda e' vuota.");
        }
        return tasks[0];
    }

    public T completaProssimoTask() {
        if (numeroTask == 0) {
            throw new NoSuchElementException("L'agenda e' vuota.");
        }
        T prossimoTask = tasks[0];

        for (int i = 0; i < numeroTask - 1; i++) {
            tasks[i] = tasks[i + 1];
        }

        tasks[numeroTask - 1] = null;
        numeroTask--;
        return prossimoTask;
    }

    public int getNumeroTask() {
        return numeroTask;
    }

    public void stampaAgenda() {
        System.out.print("[");
        for(int i = 0; i < numeroTask; i++) {
            System.out.print(tasks[i]);
            if(i < numeroTask - 1)
                System.out.print(", ");
        }
        System.out.println("]");
    }
}