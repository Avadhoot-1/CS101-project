# CS101-project
This game is made as the final project of a course CS101 - Computer Programming and Utilization. It is made using C++ language. [simplecpp](https://www.cse.iitb.ac.in/~ranade/simplecpp/) library is used for graphics.

## Game Instructions:
* After running the program game starts and  you'll be playing level 1. There are total 3 levels.
* On successful completion of current level, you'll move to next level.
* Controls - `a` : left, `d`: right, `w`: shoot bullet, `q`: exit game in middle of a level
* IN each level you will get 50 seconds to shoot all the bubbles. Also, you will get 5 heaths in each level. You have to shoot all the bubbles in the given time, without losing all the healths to complete the level. 

## Features Implemented:
* Vertical motion of bubbles  --> parabolic path
* Collision between bubbles and bullets --> score increases on successful hit
* Collision between bubbles and shooter --> health decreases on successful hit also, shooter changes color on collision
* Levels --> increasing levels increases size of bubbles. also, gravity varies with levels as gravity = level * 4
* Bigger bubbles split in two smaller bubbles moving in opposite direction
* Addition of score, health and time counter

## Link of Game Recording:
https://drive.google.com/drive/folders/12k-8q9vajpms5ekgcyhcwvom3vxzrpjd?usp=sharing
