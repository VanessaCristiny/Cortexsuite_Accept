def load():
  with open("result/result_U.txt") as f:
    my_str = f.read()
  return my_str

def score(orig, relaxed):
  total = 0.0
  orig_list = orig.split()
  relaxed_list = relaxed.split()
  if len(orig_list) != len(relaxed_list):
    return 1.0
  for a, b in zip(orig_list, relaxed_list):
    total += min(abs((float(a)) - (float(b))), 1.0)
  return total / len(orig_list)
