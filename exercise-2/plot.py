from matplotlib import pyplot as plt

threads = (1,2,4,8,12,16,20,24,28,32)
results = (7001.9, 11413.8, 22815.3, 37270.3, 40617.9, 40880.2, 40775.8, 41236.9, 41249.5, 42463.2)

plt.plot(threads, results, "-b+", label="Thread copy bandwidth ")
plt.legend(loc="lower right")
plt.xlabel("Number of threads")
plt.ylabel("Copy bandwidth (MB/s)")
plt.savefig("bandwidth")