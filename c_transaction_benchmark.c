#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TRANSACTION_COUNT 100000
#define THREAD_COUNT 8

// トランザクション処理を模倣
void* process_transaction(void* arg) {
    int id = *(int*)arg;
    int result = id * 2;  // 計算処理（結果は捨てる）
    free(arg);  // 動的メモリを解放
    return NULL;
}

// スレッドで並列処理を実行
void execute_transactions() {
    pthread_t threads[TRANSACTION_COUNT];
    int active_threads = 0;

    for (int i = 0; i < TRANSACTION_COUNT; i++) {
        // トランザクションIDを動的に割り当て
        int* id = malloc(sizeof(int));
        *id = i;

        pthread_create(&threads[i], NULL, process_transaction, id);
        active_threads++;

        // 同時に実行できるスレッド数を制限
        if (active_threads >= THREAD_COUNT) {
            for (int j = i - THREAD_COUNT + 1; j <= i; j++) {
                pthread_join(threads[j], NULL);
            }
            active_threads -= THREAD_COUNT;
        }
    }

    // 残りのスレッドを待機
    for (int i = TRANSACTION_COUNT - active_threads; i < TRANSACTION_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    clock_t start, end;

    start = clock();
    execute_transactions();
    end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Completed %d transactions in %.6f seconds\n", TRANSACTION_COUNT, elapsed_time);

    return 0;
}
