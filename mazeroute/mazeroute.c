#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAZE_SIZE 10
#define MAX_STACK_SIZE 100



typedef struct {
	short r;
	short c;
}element;


typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;


element here = { 1,0 }, entry = { 1,0 };

element t_here = { 1,0 }, t_entry = { 1,0 };

void init_stack(StackType* s)
{
	s->top = -1;
}


int is_empty(StackType* s)
{
	return(s->top == -1);
}


int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}



void push(StackType* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}


element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return;
	}
	else return s->data[(s->top)--];


}





char maze[MAZE_SIZE][MAZE_SIZE] = {

		{'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'}

		//{'1','1','1','1','1','1'},
		//{'e','0','0','0','0','1'},
		//{'1','0','1','0','1','1'},
		//{'1','1','1','0','0','x'},
		//{'1','1','1','1','1','1'},
		//{'1','1','1','1','1','1'}

};


void reverse(StackType* s, StackType* t)
{
	while (!is_empty(s))
	{
		push(t, pop(s));
	}
}


void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);

	}
}



int check(int r, int c)
{
	if ((maze[r - 1][c] == '1' || maze[r - 1][c] == '.')
		&& (maze[r + 1][c] == '1' || maze[r + 1][c] == '.')
		&& (maze[r][c - 1] == '1' || maze[r][c - 1] == '.')
		&& (maze[r][c + 1] == '1' || maze[r][c + 1] == '.')
		)
	{
		return 1;
	}
	else return 0;
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void)
{
	int r, c;
	int t_r, t_c;
	StackType s;
	StackType t;

	init_stack(&s);
	init_stack(&t);
	here = entry;
	t_here = t_entry;
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		t_r = t_here.r;
		t_c = t_here.c;
		maze[r][c] = '.';
		//maze_print(maze);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_empty(&s))
		{
			printf("실패\n");
			return;
		}
		else
		{




			
			printf("%d %d 원본\n", r, c);
			push(&t, here);
			here = pop(&s);


			while (!is_empty(&t) && check(r, c) == 1)
			{
				printf("%d %d 복사\n", r, c);
				here = pop(&t);
				r = here.r;
				c = here.c;
			}

		}



	}
	printf("성공\n");

	return 0;
}