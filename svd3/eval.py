def load():
    out = []
    resultU = open("result_U.txt")
    result_V = open("results/result_V.txt")
    for item, item2 in result_U, result_V:
        out.append((item, item2))
    return out

def score(orig, relaxed):
    total = 0.0
    total2 = 0.0
    for a, b in zip(orig, relaxed):
        total += min(abs(a[0] - b[0]), 1.0)
        total2 += min(abs(a[1] - b[1]), 1.0)

    if total > total2:
    	return total / len(orig)
    else:
    	return total2 / len(orig)
