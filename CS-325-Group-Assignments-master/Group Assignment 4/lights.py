from cnf2sat import satisfiable

inputFile = open('input.txt','r')
infoLine = inputFile.readline().rstrip().split(",")

n = int(infoLine[0])
m = int(infoLine[1])

lightsInfo = inputFile.readline().split(",")
initState = []
initState.append('None')

#0-light off
#1-light on
for i in range (0,m):
    initState.append(int(lightsInfo[i]))

connections = []
connections.append('None')

for i in range (0,m):
    connections.append([])

for i in range (1,n+1):
    switchConnections = inputFile.readline().split(",")
    j = 0
    while (True):
        connections[int(switchConnections[j])].append(i)
        if (switchConnections[j] == switchConnections[-1]):
            break
        j = j + 1

SAT = []

for i in range (1,m+1):
    #light on
    #(-c1 OR c2)AND(c1 OR -c2)
    if(initState[i] == 0):
        SAT.append((connections[i][0]*-1, connections[i][1]))
        SAT.append((connections[i][0], connections[i][1]*-1))
    #(c1 OR c2)AND(-c1 OR -c2)
    #light off
    else:
        SAT.append((connections[i][0], connections[i][1]))
        SAT.append((connections[i][0]*-1, connections[i][1]*-1))

outputFile = open('output.txt','w')

if (satisfiable(SAT)):
    outputFile.write('yes')
else:
    outputFile.write('no')

outputFile.close()
inputFile.close()
