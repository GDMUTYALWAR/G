/*
<Rat maze Game > Copyright (C) < 2015 >  < Gaurav Mutyalwar>
< mutyalwar96@gmail.com >

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/





#include<ncurses.h>
#include<errno.h>
#include<stdio.h>
#include<panel.h>
#include<time.h>
#include<unistd.h>
#define w 21
#define h 41

void screen_init (void) {
  initscr ();
  start_color();
  noecho ();
  cbreak ();
  keypad (stdscr,TRUE);
  refresh ();
}

struct mfile {
int k;
int l;
char arr[w][h];
};
struct mfile g[7];
struct mfile gt;

int seekpanel(PANEL *P);
WINDOW *create_newwin(int height,int width,int starty,int startx);
void getrat (WINDOW *window, int b, int a);

int main (int argc, char *argv[]) {	
//main_function//
if(argc < 8)  {
		errno = EINVAL;					//error msg//
		perror("usage: ./program filename\n");
		return errno;}	
int flag,i,j,x,y,ch;
int a=1;
int b=1;
	
	
	screen_init ();
	initscr();   		//start ncurses//
	cbreak();


WINDOW *win[8];
win[0] = create_newwin(21,41,3,6);
win[1] = create_newwin(21,41,6,12);				//setting up windows//
win[2] = create_newwin(21,41,9,18);
win[3] = create_newwin(21,41,16,44);
win[4] = create_newwin(21,41,3,93);
win[5] = create_newwin(21,41,6,82);				//setting up windows//
win[6] = create_newwin(21,41,9,75);
//game complt window//
win[7] = create_newwin(5,28,35,0);
WINDOW *mywin;

PANEL *panel[8];
PANEL *top;
for(i=0;i<8;i++) {
	panel[i] = new_panel(win[i]);
	keypad(stdscr, TRUE);
	}
set_panel_userptr(panel[0], panel[1]);
set_panel_userptr(panel[1], panel[2]);			// setting up panels//
set_panel_userptr(panel[2], panel[3]);
set_panel_userptr(panel[3], panel[6]);
set_panel_userptr(panel[6], panel[5]);			// setting up panels//
set_panel_userptr(panel[5], panel[4]);
set_panel_userptr(panel[4], panel[0]);
//game complete window//
hide_panel(panel[7]);

/*Initialize all the colors */
init_pair(1, COLOR_WHITE, COLOR_BLUE);
init_pair(2, COLOR_RED, COLOR_BLACK);
init_pair(3, COLOR_YELLOW, COLOR_WHITE);
init_pair(4, COLOR_CYAN, COLOR_BLUE);

wattron(win[0],COLOR_PAIR(1));
wattron(win[1],COLOR_PAIR(2));
wattron(win[2],COLOR_PAIR(3));	
wattron(win[4],COLOR_PAIR(1));
wattron(win[5],COLOR_PAIR(2));
wattron(win[6],COLOR_PAIR(3));
wattron(win[3],COLOR_PAIR(4));

update_panels();	


for(x=0;x<7;x++) {
 
	FILE *fp[7];
	for(i=0; i<w; i++)
		{for(j=0; j<h; j++)
			g[x].arr[i][j] = '0';
		}
fp[x] = fopen(argv[x+1],"r");		//read file//
	curs_set(1);
	
for(i=0;i<w;i++){
	for(j=0;j<h;j++)
		fscanf(fp[x],"%c",&(g[x].arr[i][j]));
		}

for (i=0;i<w;i++)
  {	for (j=0;j<h;j++)
	{	wmove(win[x], i, j);	//game draw//
		if(g[x].arr[i][j] == '0'|| g[x].arr[i][j] =='\n') {			
			 waddch (win[x], ' ' | A_STANDOUT);
		} else
			waddch (win[x], ' ');
	}
	
  }

wmove (win[x], 19, 38);
waddch(win[x], '#');
update_panels();
doupdate();
}
mvwprintw(win[7],2,2,"Congo game completed");
mvprintw(30,0,"Press Enter to Reset the game");
mvprintw(31,0,"Press f1 to exit");
mvprintw(0,0,"GAURAV MAZE GAME");						
mvprintw(32,0,"Use TAB key to change the maze");

WINDOW *seekpanel(PANEL *P) {
WINDOW *mywin;
top_panel(P);
	if(P == panel[0])
		mywin= win[0];
	if(P == panel[1])
			mywin= win[1];
	if(P == panel[2])
		      mywin = win[2];
	if(P == panel[3])
			 mywin= win[3];
	if(P == panel[4])
			mywin= win[4];
	if(P == panel[5])
		      mywin = win[5];
	if(P == panel[6])
		      mywin = win[6];	

		refresh();
return mywin;
		}



// player initial position//
for(i=0;i<7;i++){
wmove(win[i], 1, 1);
waddch(win[i], ACS_DIAMOND);		
}
update_panels();
 doupdate();

keypad(stdscr,TRUE);
	top_panel(panel[3]);
	top = panel[3];				//INITIAL conditions of game//
	mywin= win[3];
update_panels();	
doupdate();			
struct mfile changemaze() {
WINDOW *WIN;
WIN = seekpanel(top);

		
if(WIN == win[0]){			
	gt = g[0]; 
return gt;   }

if(WIN == win[1]){
	gt = g[1];
return gt;}	              		/* getting changed maze */
		
if(WIN ==  win[2]){		
	gt = g[2];
return gt;}	
	
if(WIN == win[3]){						
	gt = g[3]; 
return gt;   }

if(WIN == win[5]){
	gt = g[5];
return gt;}	
		
if(WIN ==  win[4])
	{gt = g[4];
return gt;}
if(WIN == win[6]){
	gt = g[6];
return gt;}
	}

doupdate();
						
while((ch = getch()) != KEY_F(1)) {
		
	switch(ch) {
case KEY_LEFT:
	mywin = seekpanel(top);	
	gt = changemaze();
			if(gt.arr[b][a-1] != '0') {				
			mvwprintw(mywin, b, a," ");
			a = a-1;
			b = b;
			getrat(mywin,b,a);
			getyx(mywin,y,x);
				if(y==19&&x==39){
				show_panel(panel[7]);
				}
			
		}					//flip//
		else 
			wmove(mywin,0,0);
	break;

case KEY_RIGHT:
	mywin = seekpanel(top);
	gt = changemaze();	
		if(gt.arr[b][a+1] != '0'){
			mvwprintw(mywin, b, a, " ");
			a = a + 1;
			b = b;
			getrat(mywin,b,a);
			getyx(mywin,y,x);
				if(y==19&&x==39){
				show_panel(panel[7]);
				}
		}
		else 
			wmove(mywin,0,0);
	break;

case KEY_UP:		
		mywin = seekpanel(top);	
		gt = changemaze();	
		if(gt.arr[b-1][a] != '0') {			
			mvwprintw(mywin,b,a, " ");
			a = a;
			b = b-1;
			
			getrat(mywin,b,a);
			getyx(mywin, y,x);
				if(y==19&&x==39){
				show_panel(panel[7]);
				}	
		}
		else 
			wmove(mywin,0,0);
		break;

case KEY_DOWN:
	mywin = seekpanel(top);	
	gt = changemaze();				
		if(gt.arr[b+1][a] != '0') {
			mvwprintw(mywin,b,a," ");
			a = a;
			b = b+1;
			getrat(mywin,b,a);
			getyx(mywin, y, x);
				if(y==19&&x==39){
				show_panel(panel[7]);
				}
		}else
			wmove(mywin,0,0);
			break;

case 9:	//using tab//
	
	mvwprintw(mywin,y,x-1," ");
	top = (PANEL *)panel_userptr(top);
	top_panel(top);
	a=1;
	b=1;
	mvwaddch(mywin,1,1,ACS_DIAMOND);
	
	break;
case 10:// using enter//
	mvwprintw(mywin,y,x-1," ");
	a=1;b=1;	
	wmove (mywin, 19, 38);
	waddch(mywin, '#');
	wmove (mywin,1,1);
	waddch(mywin,ACS_DIAMOND);
	hide_panel(panel[7]);
	break;
	}

update_panels();
doupdate();


}

wattroff(win[0],COLOR_PAIR(1));
wattroff(win[1],COLOR_PAIR(2));
wattroff(win[2],COLOR_PAIR(3));			//End colours of 7 panels//
wattroff(win[4],COLOR_PAIR(1));
wattroff(win[5],COLOR_PAIR(2));
wattroff(win[6],COLOR_PAIR(3));
wattroff(win[3],COLOR_PAIR(4));

refresh();
endwin();
return 0;			
}

WINDOW *create_newwin(int height , int width, int starty, int startx)
{	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);							//create windows//
	wrefresh(local_win);
return local_win;
}
void getrat (WINDOW *window,int b,int a) {
	
 	wmove (window, b, a);				//draw player postion//
  	waddch (window, ACS_DIAMOND);
}
