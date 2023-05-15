from numpy import zeros
import numpy as np

def gausselim(A, b, n):
    # AUGMENTED MATRIX
    augA = np.c_[A, b]
    for i in range(n - 1):
        for j in range(i + 1, n):
            ratio = augA[j, i] / augA[i, i]
            augA[j,:] -= ratio * augA[i,:]

    with open("gauss_out.txt", "w") as f:
        for i in range(n):
            f.write(" ".join("{:.3f}".format(x) for x in augA[i,:-1]))
            f.write("\n")

    # BACK SUBSTITUTION
    x = zeros(n)
    x[n - 1] = augA[n - 1,n] / augA[n - 1,n - 1]
    for i in range(n - 2,-1,-1):
        x[i] = (augA[i,n]-np.dot(augA[i,i+1:n],x[i+1:n]))/augA[i,i]

    with open("gauss_out.txt", "a") as f:
        f.write("\n")
        for i in range(n):
            f.write("x{} ={:8.3f} ".format(i + 1,x[i]))

with open("gauss_in.txt", "r") as f:
    lines = f.readlines()
    n = len(lines)
    A = np.zeros((n,n))
    b = np.zeros(n)
    for i,line in enumerate(lines):
        values = line.strip().split()
        A[i,:] = list(map(float,values[:-1]))
        b[i] = float(values[-1])

gausselim(A,b,n)

with open("gauss_out.txt", "r") as f:
    result = f.read()
    print(result)
