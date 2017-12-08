#Made by Lauren Rolan

import sys

if len(sys.argv) < 4:
  print "Too few arguments."
  print "Type \'python grafico.py <trace.tr> <flow> <node>\'"
  return

#Inputs
inputFile = sys.argv[1]
flow = sys.argv[2]
node = sys.argv[3]
words = []

#Counters
received = 0
dropped = 0

with open (inputFile, 'r') as f:
  reader = f.read()

for line in reader:
  words = line.split()
  #Counts received
  if words[0] == 'r' and words[3] == node and words[7] == flow:
    received += 1
  #Counts dropped
  if words[0] == 'd' and words[3] == node and words[7] == flow:
    dropped += 1

print "Received at node " + node + ": " + str(received)
print "Dropped at node " + node + ": " + str(dropped)
print "Loss rate at node " + node + ": " + str(dropped/received)
