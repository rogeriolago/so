#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30
#define QUANTUM 2

// FCFS
void fcfs(int bt[]) {
    int wt[N] = {0}, tat[N];
    float total_wt = 0, total_tat = 0;

    for (int i = 1; i < N; i++)
        wt[i] = bt[i - 1] + wt[i - 1];

    for (int i = 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("FCFS: Avg WT = %.2f, Avg TAT = %.2f\n", total_wt / N, total_tat / N);
}

// SJF (nao preemptivo)
void sjf(int bt[]) {
    int wt[N] = {0}, tat[N], idx[N], tmp;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < N; i++) idx[i] = i;

    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            if (bt[idx[j]] < bt[idx[i]]) {
                tmp = idx[i];
                idx[i] = idx[j];
                idx[j] = tmp;
            }
        }
    }

    for (int i = 1; i < N; i++)
        wt[idx[i]] = bt[idx[i - 1]] + wt[idx[i - 1]];

    for (int i = 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("SJF: Avg WT = %.2f, Avg TAT = %.2f\n", total_wt / N, total_tat / N);
}

// SRTF (preemptivo)
void srtf(int bt[]) {
    int rt[N], wt[N] = {0}, tat[N];
    for (int i = 0; i < N; i++) rt[i] = bt[i];
    int complete = 0, t = 0, minm = 9999, shortest = -1, finish_time;
    int check = 0;

    while (complete != N) {
        minm = 9999;
        check = 0;

        for (int j = 0; j < N; j++) {
            if (rt[j] > 0 && rt[j] < minm) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        rt[shortest]--;
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest];
        }
        t++;
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("SRTF: Avg WT = %.2f, Avg TAT = %.2f\n", total_wt / N, total_tat / N);
}

// Prioridades (aleatorias entre 1 e 10)
void prioridade(int bt[]) {
    int wt[N] = {0}, tat[N], prio[N], idx[N], tmp;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < N; i++) {
        prio[i] = rand() % 10 + 1;
        idx[i] = i;
    }

    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            if (prio[idx[j]] < prio[idx[i]]) {
                tmp = idx[i];
                idx[i] = idx[j];
                idx[j] = tmp;
            }
        }
    }

    for (int i = 1; i < N; i++)
        wt[idx[i]] = bt[idx[i - 1]] + wt[idx[i - 1]];

    for (int i = 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Prioridade: Avg WT = %.2f, Avg TAT = %.2f\n", total_wt / N, total_tat / N);
}

// Round Robin
void round_robin(int bt[], int quantum) {
    int rem_bt[N], wt[N] = {0}, tat[N];
    for (int i = 0; i < N; i++) rem_bt[i] = bt[i];

    int t = 0, done;
    do {
        done = 1;
        for (int i = 0; i < N; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!done);

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Round Robin: Avg WT = %.2f, Avg TAT = %.2f\n", total_wt / N, total_tat / N);
}

int main() {
    srand(time(NULL));
    int bt[N];
    int valores[] = {5, 8, 12};

    for (int i = 0; i < N; i++)
        bt[i] = valores[rand() % 3]; // agora é exatamente 5, 8 ou 12

    fcfs(bt);
    sjf(bt);
    srtf(bt);
    prioridade(bt);
    round_robin(bt, QUANTUM);
    return 0;
}
