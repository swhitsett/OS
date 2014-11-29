#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>   //for debuging only incase i forget to remove

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
	   	  root->down = NULL;
	      cur = root;
	  }
	  else
	  {
	  	 cur->next = (struct node*)malloc(sizeof(struct node));
	   	 cur->next->priority = i+1;
	   	 cur->down = NULL;
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
	while(cur->priority != priority && cur != NULL)
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
	cur = root;
	for(int i=0; i<4; i++)
	{

		if (cur->down)
		{
			postionInQ = cur->down;
			do
			{
				if (postionInQ->value == pid)
				{
					if (postionInQ->down)
					{
						if (postionInQ->prev)
						{
							postionInQ->prev->down = postionInQ->down;
							postionInQ->down->prev = postionInQ->prev;
						}
						else
						{
							cur->down = postionInQ->down;
							cur->down->prev = NULL;
						}
					}
					else
					{
						if (postionInQ->prev)
						{
							postionInQ->prev->down = NULL;
						}
						else
						{
							cur->down = NULL;
						}
					}
					free(postionInQ);
					return 1;
				}
				else
				{
					postionInQ = postionInQ->down;
				}
			} while (postionInQ);
		}
		cur = cur->next;// return 0;	
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
		// while(cur->next)
		// {
		// 	if (cur->down)
		// 	{
				printf("%d \n", cur->priority);
				struct node* temp = postionInQ = cur->down;
				cur->down = cur->down->down;
				cur->down->up = NULL;
				while (postionInQ->down)
					postionInQ = postionInQ->down;

				postionInQ->down = temp;
				temp->down = NULL;
				temp->up = postionInQ;
				t = temp->priority;
				// printf("%d \n",temp->value);
				return temp->value;
				// break;
		// 	}
		// 	else
		// 		cur = cur->next; //return -1;

		// }
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
