# create an image display
import copy
import numpy as np

N = 12 #rows (balls in each tube)
M = 5 #colums (number of tubes)

base = np.zeros((N, M), dtype = np.int)
#[[0 for i in range(M)] for j in range(N)] #base size for all the matraces

#define building blocks for the numbers
print(base)
top_l = copy.copy(base)
bot_l = copy.copy(base)
top_m = copy.copy(base)
mid_m = copy.copy(base)
bot_m = copy.copy(base)
top_r = copy.copy(base)
bot_r = copy.copy(base)
#copy.copy(base)

top_l[2:5,1] = 1
bot_l[6:10, 1] = 1
top_m[1, 1:4] = 1
mid_m[5, 1:4] = 1
bot_m[10, 1:4] = 1
top_r[2:5, 3] = 1
bot_r[6:10, 3] = 1
print(top_l)
print(bot_l)


#[[1, 0, 0], [0, 0, 0], [0, 0, 0]]
#bot_l = [[0, 0, 0], [0, 0, 0], [1, 0, 0]]
#top_m = [[0, 1, 0], [0, 0, 0], [0, 0, 0]]
#mid_m = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
#ot_m = [[0, 0, 0], [0, 0, 0], [0, 1, 0]]
#top_r = [[0, 0, 1], [0, 0, 0], [0, 0, 0]]
#bot_r = [[0, 0, 0], [0, 0, 0], [0, 0, 1]]

#create matrix for the display
one = top_l + bot_l
print(one)
two = bot_l + top_m + mid_m + bot_m + top_r
three = top_l + bot_l + top_m + mid_m + bot_m
four = top_l + mid_m + top_r + bot_r
five = top_l + top_m + mid_m + bot_m + bot_r
six = top_l + bot_l + top_m + mid_m + bot_m + bot_r
seven = top_m + top_r + bot_r
eight = top_l + bot_l + top_m + mid_m + bot_m + top_r + bot_r
nine = top_l + top_m + mid_m + top_r + bot_r
#ect

print_num_8 = True

if print_num_8:
    print(eight)
