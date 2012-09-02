#include <stdio.h>
#include <stdlib.h>

extern int time(void*);

typedef struct __list_element {
    struct __list_element* next;
    int id;             // unique id of the element (1,2,3,4...)
    int value;          // payload
} list_element;

// print out the list like "id : value"
void printout(list_element* p)
{
    while(p != NULL)
    {
        printf("%2d : %d\n", p->id, p->value);
        p = p->next;
    }
    printf("\n");
}

// bubble sort
void sort(list_element* head)
{
	list_element* p0;
	list_element* p;
	list_element* q;
	int i = 0;

	// define number of elements in the list
	p = head->next;
	while(p != NULL)
	{
		p = p->next;
		i++;
	}

	while (i > 0)	// repeat i times
	{
		p0 = head;
		while(p0->next->next != NULL)
		{
			p = p0->next;
			q = p->next;
			if(p->value > q->value)
			{
				p->next = q->next;
				q->next = p;
				p0->next = q;
			}
			else
			{
				p0 = p0->next;
			}
		}
		i--;
	}
}

// reverse current list upside down
void reverse(list_element* head)
{
	list_element* m;	// 'memory' - temporary cell for storing next element values
	list_element* p;
	list_element* q;

	p = head->next;
	q = p->next;
	m = q->next;

	p->next = NULL;
	q->next = p;

	while (m != NULL)
	{
		p = q;
		q = m;
		m = q->next;
		q->next = p;
	}

	head->next = q;
}

int main(void)
{
    list_element* head;
    list_element* p;
    list_element* q;

    int i;
    srand(time(NULL));

    // create list head
    head = (list_element*)malloc(sizeof(list_element));
    head->next = NULL;
    head->id = -1;
    head->value = -1;

    // generate list with 10 random values
    p = head;
    for (i = 0; i<10; i++)
    {
        q = (list_element*)malloc(sizeof(list_element));
        q->next = p->next;
        q->id = i;
        q->value = rand();
        p->next = q;
        p = q;
    }
    printout(head);

    // reverse list, print out
	reverse(head);
	printout(head);

    // sort it by the values, print out
    sort(head);
    printout(head);

	// reverse (already sorted) list, print out
	reverse(head);
	printout(head);

	getchar();
	return 0;
}
