# ➕ `pth_addition.c` – Multithreaded Array Summation in C with Pthreads

A multithreaded C program that demonstrates how to use **POSIX threads (pthreads)** to parallelize the summation of a large array. Each thread computes a portion of the sum, and the main thread aggregates the results. The performance is measured and compared with Euler's formula.

---

## 📄 File Information

- **File Name:** `pth_addition.c`  
- **Language:** C  
- **Author:** Jerrin C. Redmon  
- **Version:** 1.0.0  
- **Date:** April 14, 2025  

---

## 🧠 Description

This program:

- Accepts a command-line argument specifying the number of threads.
- Initializes an array of the first 1,000,000 integers.
- Splits the array into segments, one for each thread.
- Computes the partial sum in each thread.
- Joins all threads and combines their results into a total sum.
- Compares the result with Euler's formula: \( S = \frac{n(n+1)}{2} \).
- Measures the wall time taken for the summation.

---

## 🚀 How to Compile and Run

### 🔧 Compile

```bash
gcc -o pth_addition pth_addition.c -lpthread
```

### ▶️ Run

```bash
./pth_addition <num_threads>
```

Example:

```bash
./pth_addition 8
```

---

## ⌛ Results (with 8 threads)

```
Computed sum: 500000500000
Euler's Formula: 500000500000
Wall time with 8 threads: 0.001541 seconds
```

---

## 🧱 Code Structure

- `ThreadData struct`: Holds a pointer to the array, start/end indices, and partial sum.
- `sum_array`: Function run by each thread to compute its segment sum.
- `main`: 
  - Parses the number of threads.
  - Initializes the array.
  - Launches and joins threads.
  - Aggregates partial sums.
  - Verifies correctness and benchmarks execution time.

---

## 📦 Dependencies

- `pthread.h` — POSIX threads  
- `stdlib.h`, `stdio.h`, `time.h` — Standard C headers  

Link with `-lpthread` during compilation.

---

## 🪪 License

Released under the MIT License.  
Free for use in academic, personal, and professional projects.

---

## 👨‍💻 Author

**Jerrin C. Redmon**  
Contact for collaborations, feedback, or educational purposes.
