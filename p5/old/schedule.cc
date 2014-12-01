//creates 77% of the output before the odd segfualt breaks it
#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>   //for debuging only incase i forget to remove

int currentQ = 1;
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
			while(postionInQ != NULL)
			{
				if(postionInQ->value == pid)
				{
					struct node* tmp;
					tmp = postionInQ;
					postionInQ = tmp->down;
					free(tmp);
					return 1;
				}
				else
					postionInQ = postionInQ->down;
			}
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
	while(1)
	{
		if(cur->priority != currentQ)
		{
			cur = cur->next;
		}
		else if(cur->down == NULL)
		{
			if((currentQ == 1) || (currentQ == 4))
				currentQ = 2;
			else if((currentQ == 2) || (currentQ == 4))
				currentQ = 3;
			else if((currentQ == 3) || (currentQ == 4))
				currentQ = 4;
			else if(currentQ == 4)
				currentQ = 1;

			cur = root;
		}
		else 
			break;
	}
	// printf("here 1");
	if (cur->down)
	{
		// printf("here 2");
		struct node* temp = postionInQ = cur->down;
		cur->down = cur->down->down;
		cur->down->up = NULL;
		// printf("here 3");
		while (postionInQ->down)
			postionInQ = postionInQ->down;

		postionInQ->down = temp;
		temp->down = NULL;
		temp->up = postionInQ;
		// printf("here 4");
		if(cur->priority == 1)
			t = 4;
		else if(cur->priority == 2)
			t = 3;
		else if(cur->priority == 3)
			t = 2;
		else if(cur->priority == 4)
			t = 1;
		// printf("here 5");
		if(currentQ == 1)
			currentQ = 2;
		else if(currentQ == 2)
			currentQ = 3;
		else if(currentQ == 3)
			currentQ = 4;
		else if(currentQ == 4)
			currentQ = 1;
		// printf("here 6");
		return temp->value;
	}
	else
	{
		return -1;//cur = cur->next;
	}

	// cur = root;
	// for(int i=0; i<4; i++)
	// {
	// 	if(cur->priority == currentQ)
	// 	{
	// 		if (cur->down)
	// 		{
	// 			struct node* temp = postionInQ = cur->down;
	// 			cur->down = cur->down->down;
	// 			cur->down->up = NULL;
	// 			while (postionInQ->down)
	// 				postionInQ = postionInQ->down;

	// 			postionInQ->down = temp;
	// 			temp->down = NULL;
	// 			temp->up = postionInQ;
	// 			t = temp->priority;
	// 			return temp->value;
	// 		}
	// 		else
	// 		{
	// 			cur = cur->next;
	// 		}
	// 	}
	// }
	// return -1;

	//return -1;
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
			cur = cur->next;
		else
			return 1;
	}
	return 0;
	// cur = root;
	// for(int i=0; i<4; i++)
	// {
	// 	if(cur->down == NULL)
	// 		return 0;
	// 	else
	// 		cur = cur->next;
	// }
	// return 1;
	//============================
	// if(root == NULL)
	// 	return 0;
	// else
	// 	return 1;
}