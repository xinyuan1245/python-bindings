import time

start_time = time.time()
import cffi_example
result1 = cffi_example.add(2.5, 3.7)
result2 = cffi_example.add(5, 7)
end_time = time.time()

execution_time = end_time - start_time
print("Result 1:", result1)  # 输出: Result 1: 6.2
print("Result 2:", result2)  # 输出: Result 2: 12
print("Execution time:", execution_time, "seconds")

