require 'benchmark'

def process_transaction(id)
  # 模擬トランザクション処理
  id * 2
end

transaction_count = 100000

time = Benchmark.measure do
  threads = []

  transaction_count.times do |i|
    threads << Thread.new { process_transaction(i) }
  end

  threads.each(&:join)
end

puts "Completed #{transaction_count} transactions in #{time.real} seconds"