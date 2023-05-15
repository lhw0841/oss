from numpy import zeros, set_printoptions

def LU(A, b, n):

    L = zeros((n, n))
    U = zeros((n, n))

    for i in range(n):
        L[i, i] = 1

    for i in range(n):
        for j in range(i, n):
            sum_lu = 0
            for k in range(i):
                sum_lu += L[i, k] * U[k, j]
            U[i, j] = A[i, j] - sum_lu

        for j in range(i+1, n):
            sum_lu = 0
            for k in range(i):
                sum_lu += L[j, k] * U[k, i]
            L[j, i] = (A[j, i] - sum_lu) / U[i, i]

    with open("LU_out.txt", "w") as f:
        for i in range(n):
            f.write(" ".join("{:.3f}".format(x) for x in L[i]))
            f.write("\n")
        f.write("\n")
        for i in range(n):
            f.write(" ".join("{:.3f}".format(x) for x in U[i]))
            f.write("\n")

    y = zeros(n)
    for i in range(n):
        sum_ly = 0
        for j in range(i):
            sum_ly += L[i, j] * y[j]
        y[i] = (b[i] - sum_ly) / L[i, i]

    x = zeros(n)
    for i in range(n-1, -1, -1):
        sum_ux = 0
        for j in range(i+1,n):
            sum_ux += U[i,j]*x[j]
        x[i] = (y[i]-sum_ux)/U[i,i]

    with open("LU_out.txt", "a") as f:
        f.write("\n")
        f.write("[")
        f.write("y = ")
        f.write(" ".join("{:.3f},".format(x) for x in y))
        f.write("]")

        f.write("\n\n")
        for i in range(n):
            f.write("x{} ={:8.3f} ".format(i + 1, round(x[i], 2)))

    return L,U,y,x

with open("LU_in.txt", "r") as f:
    lines = f.readlines()
    n = len(lines)
    A = zeros((n,n))
    b = zeros(n)
    for i,line in enumerate(lines):
        values = line.strip().split()
        A[i,:] = list(map(float,values[:-1]))
        b[i] = float(values[-1])

L,U,y,x=LU(A, b, n)

with open("LU_out.txt", "r") as f:
    result = f.read()
    print(result)