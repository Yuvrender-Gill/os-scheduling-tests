import sys

def parse(file):
  counts = {}
  inst_d = {}
  data_d = {}
  with open(file) as f:
    for line in f.readlines():
      info = line.split(',')
      inst = info[0].split()[0]
      addr = info[0].split()[1]
      vpn = hex(int(addr[:-3] + "000", 16))
      if inst == "I":
        if "Instructions" in counts:
          counts["Instructions"] += 1
        else:
          counts["Instructions"] = 1

        if vpn in inst_d:
          inst_d[vpn] += 1
        else:
          inst_d[vpn] = 1
      else:
        if inst in counts:
          counts[inst] += 1
        else:
          counts[inst] = 1

        if vpn in data_d:
          data_d[vpn] += 1
        else:
          data_d[vpn] = 1
  return counts, inst_d, data_d
if __name__ == "__main__":
  counts, inst_d, data_d = parse(sys.argv[1])
  print("Counts:")
  print("  Instructions: ", counts["Instructions"])
  print("  Loads: ", counts["L"])
  print("  Stores: ", counts["S"])
  print("  Modifies: ", counts["M"])
  print("")
  print("Instructions:")
  for ins in inst_d:
    print(ins + ',' + str(inst_d[ins]))
  print("Data:")
  for data in data_d:
    print(data + ',' + str(data_d[data]))