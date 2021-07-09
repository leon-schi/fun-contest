import random
import math
from pathlib import Path

random.seed(-6335419274901380260)

SAMPLES = [
    ['sample1',
'''6 7
1 2
2 4
4 3
3 1
4 5
5 6
6 4
'''],
    ['sample2',
'''4 5
1 2
2 4
4 3
3 1
4 1
''']
]

def generate_valid_graph(k, m): # k circles and m edges
    borders = sorted(random.sample(list(range(math.floor(m/2) - 2)), k-1))
    borders = [(b+1)*2 for b in borders] + [m]
    r = []
    cur_node_id, next_edge_id = 0, 0
    for border in borders:
        start_node_id = random.randint(0, cur_node_id)
        cur_node_id += 1
        r.append([next_edge_id, start_node_id, cur_node_id])
        next_edge_id += 1
        while next_edge_id < border-1:
            r.append([next_edge_id, cur_node_id, cur_node_id+1])
            next_edge_id += 1
            cur_node_id += 1
        r.append([next_edge_id, cur_node_id, start_node_id])
        next_edge_id += 1
    r = [add_one(e) for e in r]
    n = cur_node_id + 1
    return n, m, r

def generate_invalid_graph(n, m): # m edges
    # n must be at most m + 1
    assert n <= m + 1

    # connect all but nodes in a line
    r = [[a, a, a+1] for a in range(n-1)]

    next_edge_id = n-1
    while next_edge_id < m:
        a, b = random.randint(0,n-2), random.randint(0,n-2)
        r.append([next_edge_id, a, b])
        next_edge_id += 1
    
    r = [add_one(e) for e in r]
    return n, m, r

def add_one(l):
    return [x+1 for x in l]

def int_to_string_list(l):
    return [str(x) for x in l]

def generate_valid_testcase(k, m):
    n, m, r = generate_valid_graph(k, m)
    s = [' '.join(int_to_string_list(e[1:])) for e in r]
    return f'{n} {m}\n' + '\n'.join(s) + '\n'

def generate_invalid_testcase(n, m):
    n, m, r = generate_invalid_graph(n, m)
    s = [' '.join(int_to_string_list(e[1:])) for e in r]
    return f'{n} {m}\n' + '\n'.join(s) + '\n'

for name, s in SAMPLES:
    Path(name + '.in').write_text(s+'\n')
    Path(name + '.desc').write_text(name+'\n')

i = 0
for m in range(500, 2001, 500):
    for k in [2, 10, 20]:
        Path(f'random-{i}.in').write_text(generate_valid_testcase(k, m))
        Path(f'random-{i}.desc').write_text(f'random valid testcase {i} with {k} circles and {m} edges')
        i += 1

Path(f'largest.in').write_text(generate_valid_testcase(5000, 50000))
Path(f'largest.desc').write_text(f'random valid testcase {i} with {5000} circles and {50000} edges')

for n in range(500, 2001, 500):
    m_max = min(n*4 + 1, math.floor((n-1)*(n-2)/2))
    for m in range(n, m_max, n):
        Path(f'random-{i}.in').write_text(generate_invalid_testcase(n, m))
        Path(f'random-{i}.desc').write_text(f'random invalid testcase (graph has no eulerian cycle) with {n} nodes and {m} edges')
        i += 1