# lem-in

The goal of this project is to find the quickest way to get n ants across the farm.

Obviously, there are some basic constraints. To be the first to arrive, ants will need

to take the shortest path (and that isn’t necessarily the simplest). They will also

need to avoid traffic jams as well as walking all over their fellow ants.

At the beginning of the game, all the ants are in the room ##start. The goal is

to bring them to the room ##end with as few turns as possible. Each room can

only contain one ant at a time. (except at ##start and ##end which can contain

as many ants as necessary.)

• We consider that all the ants are in the room ##start at the beginning of the game.

• At each turn program will only display the ants that moved.

• At each turn program can move each ant only once and through a tube

(the room at the receiving end must be empty).

Program will receive the data describing the ant farm from the standard output

in the following format:

number_of_ants

the_rooms

the_links

Program will display results on the standard output in the following format:

number_of_ants

the_rooms

the_links

Lx-y Lz-w Lr-o ...

x, z, r represents the ants’ numbers (going from 1 to number_of_ants)

and y, w, o represents the rooms’ names.

Example:

![alt tag](https://github.com/vitalyten/lem-in/blob/master/leminexample.png)

◦ Rooms defined by: name coord_x coord_y

◦ Links defined by: name1-name2

◦ All of it is broken by comments, which start with #

 ##start signals the ant farm’s entrance and ##end its exit.
