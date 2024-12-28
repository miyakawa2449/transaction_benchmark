import threading
import time

def process_transaction(transaction_id):
    # 模擬トランザクション処理
    transaction_id * 2

def main():
    transaction_count = 100000
    threads = []

    start_time = time.time()

    for i in range(transaction_count):
        # スレッドを作成して開始
        thread = threading.Thread(target=process_transaction, args=(i,))
        threads.append(thread)
        thread.start()

    for thread in threads:
        # 全スレッドの完了を待つ
        thread.join()

    end_time = time.time()

    print(f"Completed {transaction_count} transactions in {end_time - start_time:.6f} seconds")

if __name__ == "__main__":
    main()