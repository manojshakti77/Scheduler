#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX 5

struct st {
	unsigned int time;
	unsigned int pri;
	void (*fptr)(void);
	struct st *nptr;
};


void fun1(void);
void add(unsigned int i,unsigned int pri,unsigned int time);
void display(unsigned int i);
void dispatch_time(void);
void alarm_handler(int val);


void add_sort_by_time(struct st **hptr,struct st *ptr);
void print(struct st *temp);
