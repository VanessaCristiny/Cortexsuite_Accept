def load():
    return 'file:result/result_U.txt'

def parse(f):
    items = []
    for item in f:
        items.append(item)
    return items

def score(orig, relaxed):

   orig_list = parse(orig)
   relaxed_list = parse(relaxed)
   if len(orig_list) != len(relaxed_list):
      return 1.0
   return 0.0
