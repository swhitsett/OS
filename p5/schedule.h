#ifndef _schedule_h_
#define _schedule_h_

struct node* root;
struct node* cur;

struct node
{
	int value;
	// int priority;
	struct node* prev;
	struct node* next;
};

void init();
int addProcess(int pid, int priority);
int removeProcess(int pid);
int nextProcess(int &time);
int hasProcess();

#endif
