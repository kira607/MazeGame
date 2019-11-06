//
//  Created by kira607 on 04.11.2019.
//  Copyright В© 2019 В Una Lada Reader. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

//#define sec 1000000

using namespace std;
const int wt = 10, ht = 5;

struct Charecter
{
	int x;
	int y;
};

void frame(char** map, Charecter p, int mvs)
{
	for(int i = 0; i < ht; i++)
	{
		for(int j = 0; j < wt; j++)
		{
			if((i == 0)||(i == ht - 1))
            {
                map[i][j] = '#';
            }
            else if((j == 0)||(j == wt - 1))
            {
                map[i][j] = '#';
            }
			else if((j == p.x)&&(i == p.y))
            {
                map[i][j] = '@';
            }
            else
            {
                map[i][j] = ' ';
            }
		}
	}
	
	clear();
	for(int i = 0; i < ht; i++)
	{
		for(int j = 0; j < wt; j++)
		{
			printw("%c",map[i][j]);
		}
	printw("\n");
	}
	
	printw("POS: x:%d y:%d\tmoves:%d\n\n",p.x,p.y,mvs);
	printw("Use W A S D to move:\n\n");
	printw("  W  \n");
	printw("A   D\n");
	printw("  S  \n\n");
	printw("To quit press q\n");
}

void finish(short a, int mvs)
{
	if(a==0)
	{
		clear();
		printw("You have quit the game\nPress any key to exit");
		getch();
		endwin();
	}
	else
	{
		clear();
		printw("You have passed this game!\nMoves:\t%d\nPress any key to exit",mvs);
		getch();
		endwin();
	}
}

int main()
{	
	char** map;
	map = new char* [ht];
	for(int i = 0; i < ht; i++)
	{
		map[i] = new char [wt];
	}
	
	Charecter p;
	p.y = ht-2;
	p.x = wt-2;

	int moves = 0;
	
	initscr();
	//usleep(sec/2);
	int x;
	while(true)
	{
		frame(map,p,moves);
		refresh();
		x = getch();
		
		switch(x)
		{
			case 'd':
			if(map[p.y][p.x+1] != '#')
			{
			p.x++; 
			moves++;
			}
			if(map[p.y][p.x+1] == 'F')
			finish(1,moves);
			break;
			
			case 'a':
			if(map[p.y][p.x-1] != '#')
			{
			p.x--;
			moves++;
			}
			if(map[p.y][p.x+1] == 'F')
			finish(1,moves);
			break;
			
			case 'w':
			if(map[p.y-1][p.x] != '#')
			{
			p.y--;
			moves++;
			}
			if(map[p.y][p.x+1] == 'F')
			finish(1,moves);
			break;
			
			case 's':
			if(map[p.y+1][p.x] != '#')
			{
			p.y++;
			moves++;
			}
			if(map[p.y][p.x+1] == 'F')
			finish(1,moves);
			break;
			
			case 'q':
			finish(0,0);
			return 0;
			break;
			
		}
	}
	return 0;
}

/*
############################################################
#                                                          #
# ######################################################## #
###                                                      # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                                        # #
#                                            # #         # #
#                                            # #         # #
#                                            # #         # #
#                                            # #         # #
#                                            # #         # #
#                                        ##### #         # #
#                                        #   # #         # #
#                                        # #   ########### #
#                                        # # #             #
########################################## #################
*/

/*
##########
#    # # #
# ## #   #
# F#   # #
##########
*/