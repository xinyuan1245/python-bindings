import time

start_time = time.time()
import pythoncapi_example
result1 = pythoncapi_example.add(2.5,3.7)
result2 = pythoncapi_example.add(5,7)
end_time = time.time()

execution_time = end_time-start_time
print("Result 1:",result1)
print("Result 2:",result2)
print("Exectcution time:",execution_time,"seconds")