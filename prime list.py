
# Import the time library
import math
import time
def list_primes_old(num):
    x = list(range(2, num+1))
    n = 2
    count = 0
    #start = 2
    while n < int(num ** 0.5 + 1):
        value = n**2
        index = x.index(value)
        #print(index)
        length = len(x)
        while index < length:
            if x[index] % n == 0:
                x.remove(x[index])
                length -= 1
            else:
                index += 1
        #print(x)
        
        n = x[x.index(n)+1]
        count += 1
        if count % 10 == 0:
            print("Current Prime: ", n)
    #print(x)
    return x

def list_primes(num):
    x = list(range(2, num+1))
    count = 0
    endValue = int(num ** 0.5 + 1)
    print(endValue)
    for n in range(2, endValue):
        if not n in x:
            continue
        value = n**2
        index = x.index(value)
        length = len(x)
        for i in range(index, length):
            if x[i] % n == 0:
                x[i] = -1        
        x = [i for i in x if i != -1] 
        count += 1
        if count % 10 == 0:
            print("Current Prime: ", n)
    return x


value =  int(input("Enter value here: "))
# Calculate the start time
start = time.time()
output = 3
# Code here
#output = list_primes(value)
outputfor = list_primes(value)
print(output == outputfor)
# Calculate the end time and time taken
end = time.time()
length = round(end - start, 3)
print(len(outputfor))
# Show the results : this can be altered however you like
print("It took", length, "seconds!")
