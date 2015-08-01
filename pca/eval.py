def load():
	out = []
	with open('output.txt') as f:
		for item in f:
			out.append(float(item))
	return out

def score(orig, relaxed):
	total = 0.0
	for a, b in zip(orig, relaxed):
		total += min(abs(a - b), 1.0)
	return total / len(orig)