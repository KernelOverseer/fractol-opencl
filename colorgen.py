# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colorgen.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/08 23:55:29 by abiri             #+#    #+#              #
#    Updated: 2019/05/09 00:14:03 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from os import walk

outdir = "./colors/"
filelist = []
gradient = []
colors = []

colornum = int(input("Enter the number of colors in the mixture : "))
for i in range(colornum):
    colors.append(int(input("Enter color number %d: " % (i)), 16))
if colornum > 0:
    step = int(input("Enter number of steps : "))
    colorname = input("Enter color name (Ex 'Yellowstone') : ") + ".col"
else:
    colorname = "NONE"
    step = 0
for (dirpath, dirnames, filenames) in walk(outdir):
    for filename in filenames:
        if filename != "index.col":
            filelist.append(outdir + filename)
    break
if (outdir + colorname not in filelist and colornum > 0):
    filelist.append(outdir + colorname)
def rgb(col):
    return ([col >> 16 & 255, (col >> 8) & 255, col & 255]);
def goodpath(dist1, dist2, step):
    return ((dist2-dist1)/step)
def rgbtoint(r, g, b):
    return (int(r) << 16 | int(g) << 8 | int(b))

def getgradient(col1, col2):
    minrgb = rgb(col1)
    maxrgb = rgb(col2)
    diff = [
            goodpath(minrgb[0], maxrgb[0],step),
            goodpath(minrgb[1], maxrgb[1],step),
            goodpath(minrgb[2], maxrgb[2],step),
            ]
    for i in range(step):
        gradient.append(rgbtoint(minrgb[0] + diff[0]*i, minrgb[1] + diff[1]*i, minrgb[2] + diff[2]*i))

for i in range(colornum):
    color1 = colors[i%colornum]
    color2 = colors[(i+1)%colornum]
    getgradient(color1, color2)

if colornum > 0:
    ff = open(outdir + colorname, "w")
    ff.write(str(len(gradient)) + "\n")
    for i in gradient:
        ff.write(str(i) + "\n")
    ff.close()
    print("Colorfile generated successfully at : " + colorname)
else:
    print("Successfully updated color index")
indexfile = open(outdir + "index.col", "w")
indexfile.write(str(len(filelist)) + "\n")
for filename in filelist:
    indexfile.write(filename + "\n")
indexfile.close()
