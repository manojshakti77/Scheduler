#include "sch_main.h"

int time;
int pri;
int pic;
unsigned int clock;
int scheduler_state = 0x01;

struct st *piconet[5];
void fun1(void)
{
	printf("Piconet::%d TIme::%d Pri::%d\n",pic,time,pri);
}
void add(unsigned int i,unsigned int pri,unsigned int time)
{
	struct st *temp;
	temp = malloc(sizeof(struct st));
	temp->pri = pri;
	temp->time = time;
	temp->fptr = fun1;

	add_sort_by_time(piconet+i,temp);
	return;
}

void display(unsigned int i)
{
	struct st *temp = piconet[i];
	while(temp)
	{
		printf("Time %d Priority %d\n",temp->time,temp->pri);
		temp = temp->nptr;
	}
	printf("\n\n");
	return;
}

void dispatch_time(void)
{
	int i;
	struct st *temp = NULL;
	int j = 0xFF;
	int flag = 0x01;
	for(i=0;i<MAX;i++)
	{
		if(piconet[i] == NULL)
		{
			continue;
		}
		flag = 0x00;
		temp = piconet[i];
		if((j == 0xFF) || (piconet[j]->time > piconet[i]->time))
		{
			j = i;
		}
		else if((j == 0xFF) || (piconet[j]->time == piconet[i]->time))
		{
						printf("Time Matched Checking Priority\n");
						/* Higher Value has High Priority 
						 *  0   Low Priority
						 *  255 High Priority */
						if((piconet[j]->pri) > piconet[i]->pri)
						{
										j = i;
						}
		}
		
	}
	if(flag == 0x01)
	{
		printf("No Task Available\n");
		scheduler_state = 0x00;
		return;
	}
	temp = piconet[j];
	pic = j;
	time = temp->time;
	pri = temp->pri;
	(temp->fptr)();
	piconet[j] = temp->nptr;
	free(temp);
	return;
}

void alarm_handler(int val)
{
	alarm(1);
	clock++;
	printf("Scheduler::0x%08X\n",clock);
	dispatch_time();
}
int main(void)
{
	signal(SIGALRM,alarm_handler);
	add(1,30,10);
	add(2,40,30);
	add(2,20,20);
	add(3,20,60);
	add(4,10,50);
	add(3,5,40);
	add(4,15,70);
	add(4,10,20);

#if 0
	display(1);	
	display(2);	
	display(3);	
	display(4);	
#endif

	alarm(1);
	while(scheduler_state);

	return 0;
}
