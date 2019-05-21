#include "sch_main.h"

void add_sort_by_time(struct st **hptr,struct st *ptr)
{
	struct st *temp;
	struct st *temp1;
	if((*hptr) == NULL)
	{
		(*hptr) = ptr;
		return;
	}

	/* Insert at the starting */
	if(((*hptr)->time) > (ptr->time))
	{
		ptr->nptr = (*hptr);
		(*hptr) = ptr;
		return;
	}
	
	/* Insert in the Middle */
	temp = (*hptr);

	while((temp->nptr != NULL) && ((temp->nptr->time) < (ptr->time)))
	{
		temp = temp->nptr;
	}
	ptr->nptr = temp->nptr;;
	temp->nptr = ptr;

}

void print(struct st *temp)
{
	while(temp)
	{
		printf("time::%d \n",temp->time);
		temp = temp->nptr;
	}
}
