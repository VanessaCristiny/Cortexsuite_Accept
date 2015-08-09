def load():
	out = []
	with open('out.txt') as f:
		for word in f:
			for letter in word:
				out.append(letter)
	return out

def score(orig, relaxed):
	total = 0.0
	for a, b in zip(orig, relaxed):
		if a != b:
			total += 1.0
	return total/len(orig)

