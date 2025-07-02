#include <stdio.h>

int main() { // Mengubah main() menjadi int main()
    int i, n, t;
    int bu[10], wa[10], tat[10], ct[10]; // bu: burst_remaining, ct: original_burst_time
    float awt = 0, att = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time dan simpan burst time asli
    for (i = 0; i < n; i++) {
        printf("\nEnter the burst time for process %d: ", i + 1);
        scanf("%d", &bu[i]);
        ct[i] = bu[i]; // Simpan burst time asli (completion time) untuk perhitungan turnaround time
    }

    printf("\nEnter the size of time slice (quantum): ");
    scanf("%d", &t);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------\t----------\t------------\t---------------\n");

    int time = 0; // Waktu saat ini (current time)
    int completed_processes = 0;
    int process_order[100]; // Untuk melacak urutan eksekusi, opsional
    int order_index = 0;

    // Loop utama Round Robin: terus berjalan selama masih ada proses yang belum selesai
    while (completed_processes < n) {
        int all_idle = 1; // Flag untuk mengecek apakah semua proses sedang idle (burst time 0)

        for (i = 0; i < n; i++) {
            if (bu[i] > 0) { // Jika proses i masih memiliki burst time
                all_idle = 0; // Ada setidaknya satu proses yang masih berjalan

                if (bu[i] <= t) { // Jika sisa burst time <= time slice
                    time += bu[i];    // Tambahkan sisa burst time ke waktu global
                    tat[i] = time;    // Turnaround time adalah waktu saat ini
                    bu[i] = 0;        // Proses selesai
                    completed_processes++; // Hitung proses yang selesai
                } else { // Jika sisa burst time > time slice
                    bu[i] -= t;      // Kurangi burst time dengan time slice
                    time += t;       // Tambahkan time slice ke waktu global
                }
            }
        }

        // Ini adalah kasus di mana semua proses telah selesai diproses dalam satu putaran for,
        // tetapi loop while masih berjalan karena completed_processes < n.
        // Ini bisa terjadi jika ada proses yang baru datang atau jika ada bug.
        // Dengan implementasi ini, `all_idle` memastikan kita tidak terjebak loop tak terbatas
        // jika semua proses sudah selesai.
        if (all_idle && completed_processes < n) {
            // Ini menunjukkan ada masalah jika ini terjadi, karena semua proses harus memiliki burst time > 0
            // jika completed_processes < n
            break; // Keluar dari loop jika tidak ada lagi yang bisa dieksekusi
        }
    }

    // Hitung Waiting Time setelah semua Turnaround Time dihitung
    for (i = 0; i < n; i++) {
        wa[i] = tat[i] - ct[i]; // Waiting time = Turnaround Time - Original Burst Time
        awt += wa[i]; // Akumulasi total waiting time
        att += tat[i]; // Akumulasi total turnaround time

        // Cetak detail untuk setiap proses
        printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, ct[i], wa[i], tat[i]);
    }

    // Hitung dan cetak rata-rata
    awt /= n;
    att /= n;

    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", att);

    return 0; // Indikasi bahwa program berhasil dieksekusi
}