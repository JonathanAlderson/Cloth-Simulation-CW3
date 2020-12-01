# this script generates cloths in obj format
import sys

# cloth resolution

n = int(sys.argv[1])
m = int(sys.argv[2])
z = 0

# cloth scale
scl = int(sys.argv[3])

# keeps track of positon
startX = (-(n-1) / 2) * scl
startY = -(m-1) * scl
currPos = [startX, startY]


file = open("objFiles/cloth-" + str(n) + "x" + str(m) + ".obj", "w")

# write vertices
for i in range(0, m):
    # reset
    currPos[0] = startX
    for j in range(0, n):

        file.write("v " + str(currPos[0]) + " " + str(currPos[1]) + " 0\n")

        #update X
        currPos[0] += scl
    # update Y
    currPos[1] += scl


file.write("\n")

idx = 0
for j in range(0, m - 1):

    idx = j * n + 1
    for i in range(0, n - 1):
        # upper face
        file.write("f " + str(idx + i) + " " + str(idx + i + n) + " " + str(idx + i + 1) + "\n")

        # lower face
        file.write("f " + str(idx + i + n) + " " + str(idx + i + n + 1) + " " + str(idx + i + 1) + "\n")
