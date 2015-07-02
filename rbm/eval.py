def load():
	out = []
	with open("out.txt") as f:
		for item in f:
			out.append(int(item))
	return out

def score(orig, relaxed):
	total = 0.0
	for a, b in zip(orig, relaxed):
		total += min(abs(a - b), 1.0)
	return total / len(orig)