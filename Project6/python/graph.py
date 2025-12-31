import matplotlib.pyplot as plt

# threads = [1, 2, 4]
# # times = [0.020598, 0.015793, 0.009669]
# # plt.title("computation time vs threads")

# # times = [1.484694, 1.490534, 1.478129]
# # plt.title("computation time vs threads - python")

# #times = [0.004895, 0.002427, 0.001265]
# # plt.title("computation time vs threads - go")


# # times = [1.865197, 1.733990, 1.730421]
# # plt.title("computation time vs threads - haskell")

# plt.figure()
# plt.plot(threads, times, marker='o', linestyle='-', color='blue')
# plt.xlabel("threads")
# plt.ylabel("computation time (seconds)")
# plt.grid(True)
# plt.xticks(threads)
# plt.savefig("hstask2.png")
# plt.show()


versions = [
    "sequential",
    "global - single mutex",
    "global - array of mutexes",
    "local - single mutex",
    "local - array of mutexes",
    "thread - no mutex",
    "digit - no mutex"
]

mean_times = [0.000309, 0.000542, 0.001945, 0.000405, 0.000320, 0.000331, 0.000377]

plt.figure(figsize=(10,6))
plt.bar(versions, mean_times, color='blue')
plt.ylabel("mean execution time (seconds)")
plt.title("execution time comparison of program versions")
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig("ctask1.png")
plt.show()
