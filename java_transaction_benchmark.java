import java.util.concurrent.*;
import java.util.stream.IntStream;

public class transaction_benchmark {

    public static void processTransaction(int id) {
        // 模擬トランザクション処理
        int result = id * 2; // 処理結果は捨てる
    }

    public static void main(String[] args) throws InterruptedException {
        int transactionCount = 100000;
        ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        CountDownLatch latch = new CountDownLatch(transactionCount);

        long startTime = System.nanoTime();

        IntStream.range(0, transactionCount).forEach(id -> {
            executor.submit(() -> {
                try {
                    processTransaction(id);
                } finally {
                    latch.countDown();
                }
            });
        });

        latch.await(); // 全タスクが終了するのを待機
        executor.shutdown();

        long elapsedTime = System.nanoTime() - startTime;
        System.out.printf("Completed %d transactions in %.3f ms%n",
                transactionCount, elapsedTime / 1_000_000.0);
    }
}
