#include "schedule.h"
#include <stdlib.h>

struct node* root;
struct node* postionInQ;
struct node* cur;

struct node
{
	int value;
	int priority;
	struct node* prev;
	struct node* next;
	struct node* down;
	struct node* up;
};

/*
 * Function to initialize any global variables for the scheduler. 
 */
void init()
{
   for(int i=0; i<4; i++)
   {
      if(!root)
      {
	   	  root = (struct node*)malloc(sizeof(struct node));
	   	  root->priority = 1;
	      cur = root;
	  }
	  else
	  {
	  	 cur->next = (struct node*)malloc(sizeof(struct node));
	   	 cur->next->priority = i+1;
	     cur = cur->next;
	  }

	}
	// root->value = -1;
}

/*
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the 
 *      scheduler queue
 * @Param priority - priority of the process being added
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid, int priority)
{
	cur = root;
	while(cur->priority != priority && cur->next != NULL)
		cur = cur->next;

	if(!cur->down)
	{
		cur->down = (struct node*)malloc(sizeof(struct node));
		postionInQ = cur->down;
	}
	else
	{
		postionInQ = cur->down;
		while(postionInQ->down)
			postionInQ = postionInQ->down;

		postionInQ->down = (struct node*)malloc(sizeof(struct node));
		postionInQ->down->up = postionInQ;
		postionInQ = postionInQ->down;
	}
	postionInQ->value = pid;
	return 1;
}

/*
 * Function to remove a process from the scheduler queue
 * @Param pid - the ID for the process/thread to be removed from the
 *      scheduler queue
 * @Return true/false response for if the removal was successful
 */
int removeProcess(int pid)
{
	if (root)
	{
		cur = root;
		do
		{
			if (cur->value == pid)
			{
				if (cur->next)
				{
					if (cur->prev)
					{
						cur->prev->next = cur->next;
						cur->next->prev = cur->prev;
					}
					else
					{
						root = cur->next;
						root->prev = NULL;
					}
				}
				else
				{
					if (cur->prev)
					{
						cur->prev->next = NULL;
					}
					else
					{
						root = NULL;
					}
				}
				free(cur);
				return 1;
			}
			else
			{
				cur = cur->next;
			}
		} while (cur);
	}
	return 0;	
}
/*
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for
 * @Return returns the thread id of the next process that should be 
 *      executed, returns -1 if there are no processes
 */
int nextProcess(int &t)  //changed to t because sublime's syntax hilighting bothers me
{
	cur = root;
	if(cur)
	{
		while(cur->next)
		{
			if (cur->down)
			{
				struct node* temp = postionInQ = cur->down;
				cur->down = cur->down->down;
				cur->down->up = NULL;
				while (postionInQ->down)
					postionInQ = postionInQ->down;

				postionInQ->down = temp;
				temp->down = NULL;
				temp->up = postionInQ;
				t = temp->priority;
				return temp->value;
			}
			else
				return -1;
		}
	}
	else
		return -1;
}

/*
 * Function that returns a boolean 1 True/0 False based on if there are any 
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more 
 *		scheduled processes
 */
int hasProcess()
{
	cur = root;
	for(int i=0; i<4; i++)
	{
		if(cur->down == NULL)
			return 0;
		else
			cur = cur->next;
	}
	return 1;
	// if(root == NULL)
	// 	return 0;
	// else
	// 	return 1;
}
