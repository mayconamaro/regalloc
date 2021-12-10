import sys
import random

# n = 3
# sizes = [10, 40, 80]
# for i in range(1, n+1):
#     for s in sizes:
#         arquivo = open('instances/random/n'+str(i)+'s'+str(s)+'.txt', 'w')
#         n_points = random.randrange(s, 10*s)
#         arquivo.write(str(n_points)+'\n')
#         for j in range(0, n_points):
#             n_vars = random.randrange(1, s)
#             arquivo.write(str(n_vars))
#             for k in range(0, n_vars):
#                 arquivo.write(' '+str(random.randrange(0, s)))
#             arquivo.write('\n')

n = 3
sizes = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120]
for s in sizes:
    arquivo = open('instances/trivial/s'+str(s)+'.txt', 'w')
    n_points = s
    arquivo.write(str(n_points)+'\n')
    for j in range(0, n_points):
        n_vars = 1
        arquivo.write(str(n_vars))
        for k in range(0, n_vars):
            arquivo.write(' '+str(j))
        arquivo.write('\n')