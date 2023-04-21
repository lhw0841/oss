from numpy import array,zeros
from numpy.linalg import det

filename_in = 'cramer_in.txt'
filename_out = 'cramer_out.txt'

# 파일로부터 행렬을 읽는 함수 선언
def read_matrix(filename_in):
    with open(filename_in, 'r') as f:
        lines = f.readlines()
    matrix = []
    for l1 in lines:
        row = [float(x) for x in l1.strip().split()]
        matrix.append(row)
    return matrix
# 2x2 3x3 행렬 판별
def read_matrix_row(filename_in):
    with open(filename_in, 'r') as f:
        lines = f.readlines()
    matrix = []
    for l1 in lines:
        row = [float(x) for x in l1.strip().split()]
        matrix.append(row)
        num_row = len(row)
    return num_row

#크래머 공식 함수
def crammer(A,b):
    n = len(b)
    detsub = zeros((n))
    x = zeros((n))
    # det함수 사용.
    detA = det(A)
    for i in range(n):
        # Atemp 라는 변수에 A행렬을 복사
        Atemp = A.copy()
        # 복사한 Atemp 변수에 b 행렬을 왼쪽부터 순서대로 한 행씩 바꿔줌
        Atemp[:,i] = b
        # detsub 배열의 i 번째에 b행렬 값이 추가된 Atemp의 det값을 더해줌
        detsub[i] = det(Atemp)
        # x배열의 i번째에 detsub/detA를 해서 더해줌.
        x[i] = detsub[i]/detA
    return  detsub,x

list = read_matrix(filename_in)

a = []
A = []
b = []
row = []
# 2x2 행렬 index 정의
indices_2x2_a = [(0,0), (0,1), (1,0), (1,1)]
indices_2x2_b = [(0,2), (1,2)]
# 3x3 행렬 index 정의
indices_3x3_b = [(0, 3), (1, 3), (2, 3)]
indices_3x3_a = [(0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2)]


if((read_matrix_row(filename_in)-1)==2):
    # 2x2 임시A 행렬 일차원배열 형태로 추출
    for i, j in indices_2x2_a:
        a.append(list[i][j])
    # 2x2 B행렬 일차원배열 형태로 추출
    for i, j in indices_2x2_b:
        b.append(list[i][j])
    # 2x2 A 행렬 2차원배열 형태로 변환
    for i in range(len(a)):
        row.append(a[i])
        if len(row) == 2:
            A.append(row)
            row = []
elif((read_matrix_row(filename_in)-1)==3):
    # 3x3 임시A 행렬 일차원배열 형태로 추출
    for i,j in indices_3x3_a:
        value = list[i][j]
        a.append(value)
    # 3x3 B행렬 일차원배열 형태로 추출
    for i,j in indices_3x3_b:
        value = list[i][j]
        b.append(value)
    # 3x3 A 행렬 2차원배열 형태로 변환
    for i in range(len(a)):
        row.append(a[i])
        if len(row) == 3:
            A.append(row)
            row = []

print(A)
print(b)

A1 = array(A)
b1 = array(b)
detsub,x = crammer(A1,b1)

print('det(A) = %8.4f' %det(A))
print('det(A1) = %8.4f' %detsub[0])
print('det(A2) = %8.4f' %detsub[1])

if((read_matrix_row(filename_in)-1)==3):
    print('det(A3) = %8.4f' %detsub[2])

print('x1 = %8.4f' %x[0])
print('x2 = %8.4f' %x[1])
if((read_matrix_row(filename_in)-1)==3):
    print('x3 = %8.4f' % x[2])

with open(filename_out, 'w') as f:
    for i in range(len(x)):
        f.write('x{} =, {},'.format(i + 1, x[i]))