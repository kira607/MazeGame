//
//  Created by kira607 on 04.11.2019.
//  Copyright В© 2019 В kira607. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include <string>

//#define sec 1000000

using namespace std;
const int wt = 60, ht = 30;

struct Charecter
{
	int x;
	int y;
};

void frame(char** map, Charecter p, int mvs, unsigned char* smap)
{
	//char smap[] = "###########    # # ## ## #   ## F#   # ###########";
	for(int i = 0; i < ht; i++)
	{
		for(int j = 0; j < wt; j++)
		{
			if((j == p.x)&&(i == p.y))
            {
                map[i][j] = '@';
            }
			else if(smap[((ht-1-i)*wt+j)]==0) //(ht-1-i)*wt+j)
			{
				map[i][j] = '#';
			}
			else if((j == 2)&&(i == ht-2))
			{
				map[i][j] = 'F';
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

/*
void init_map(char** map)
{
	char smap[] = "###########    # # ## ## #   ## F#   # ###########";
	for(int i = 0; i < ht; i++)
	{
		for(int j = 0; j < wt; j++)
		{
			map[i][j] = smap[i+j+(wt-1)*i];
		}
	}
}
*/

unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int size = 3 * width * height;
	
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
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
	
	char fname[] = "maze2.bmp";
	unsigned char* predata = readBMP(fname);
	unsigned char* data = new unsigned char [wt*ht];
	int j = 0;
	for(int i = 0; i < wt*ht*3; i += 3)
	{
		data[j] = predata[i];
		j++;
	}
	
	delete [] predata;
	
	initscr();
	//usleep(sec/2);
	int x;
	while(true)
	{
		frame(map,p,moves,data);
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
			if(map[p.y][p.x] == 'F')
			{
			finish(1,moves);
			return 0;
			}
			break;
			
			case 'a':
			if(map[p.y][p.x-1] != '#')
			{
			p.x--;
			moves++;
			}
			if(map[p.y][p.x] == 'F')
			{
			finish(1,moves);
			return 0;
			}
			break;
			
			case 'w':
			if(map[p.y-1][p.x] != '#')
			{
			p.y--;
			moves++;
			}
			if(map[p.y][p.x] == 'F')
			{
			finish(1,moves);
			return 0;
			}
			break;
			
			case 's':
			if(map[p.y+1][p.x] != '#')
			{
			p.y++;
			moves++;
			}
			if(map[p.y][p.x] == 'F')
			{
			finish(1,moves);
			return 0;
			}
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
60x30
############################################################
#                                                          #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
# #                                                        #
###                                                        #
#                                                          #
############################################################
*/

/*
##########
#    # # #
# ## #   #
# F#   # #
##########

###########    # # ## ## #   ## F#   # ###########
*/
