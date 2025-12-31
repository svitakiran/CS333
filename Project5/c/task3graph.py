# Visualizing the task 3 with a graph

# Svita Kiran
# 11/13/2025
# CS333

import matplotlib.pyplot as plt

sizes = [400, 40000, 4000000]
avg_times = [0.12, 0.66, 0.65]

plt.figure(figsize=(8,5))
plt.plot(sizes, avg_times)
plt.xscale('log')
plt.xlabel('allocation size (bytes)')
plt.ylabel('average time (microseconds)')
plt.title('memory allocation')
plt.show()