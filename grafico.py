import sys

if len(sys.argv) < 4:
  print "Too few arguments."
  print "Type \'python grafico.py <trace.tr> <flow> <node>\'"
  return

with open (sys.argv[1], 'r') as f:
  reader = f.read()

for line in reader:
  print line
