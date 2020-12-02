# this script generates cloths in obj format
import sys

# cloth resolution

n = int(sys.argv[1])
m = int(sys.argv[2])
z = 0

# cloth scale
scl = int(sys.argv[3])

# find width and height
width = (n - 1) * scl
height = (m - 1) * scl

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

#reset
file.write("\n")
print(width)
print(height)
currPos = [startX, startY]
# write texture coordinates
for i in range(0, m):
    # reset
    currPos[0] = startX
    for j in range(0, n):
        # calcualte uv
        u = (currPos[0] + (width / 2)) / width
        v = (currPos[1] + height) / height
        file.write("vt " + str(u) + " " + str(v) + "\n")

        #update X
        currPos[0] += scl
    # update Y
    currPos[1] += scl

idx = 0
file.write("\n")
# write indices
for j in range(0, m - 1):

    idx = j * n + 1
    for i in range(0, n - 1):
        # upper face
        a = str(idx + i)
        b = str(idx + i + n)
        c = str(idx + i + 1)
        file.write("f " + a + "/" + a + " " + b + "/" + b + " " + c + "/" + c + "\n")

        # lower face
        a = str(idx + i + n)
        b = str(idx + i + n + 1)
        c = str(idx + i + 1)
        file.write("f " + a + "/" + a + " " + b + "/" + b + " " + c + "/" + c + "\n")
