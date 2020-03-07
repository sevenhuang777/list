#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

#define INS_LEN 20
#define INSERT "insert"
#define DELETE "delete"
#define QUIT "quit"

enum ins
{
	_none = 0,
	_insert,
	_delete,
	_quit
};

typedef struct tagNode
{
	struct tagNode *next;
	int value;
}Node;

typedef struct
{
	Node* Head;
	int len;
}List_info;
List_info list;

int judge_ins(char *ins)
{
	int result = _none;
	if( 0 == memcmp(ins, INSERT, 6) )
		result = _insert;
	else if( 0 == memcmp(ins, DELETE, 6) )
		result = _delete;
	else if( 0 == memcmp(ins, QUIT, 4) )
		result = _quit;
	return result;
}

Node *insert_node(Node* prev, Node* new, Node* now, int value)
{
	now = (Node *)malloc( sizeof(Node) );
	if(now == NULL)  
	{
		printf("malloc Node now failed!\r\n");
	}
	else
	{
		now->value = value;
		now->next = new;
		if( prev != NULL )
			prev->next = now;
	}
	return now;
}

Node *make_list(Node* head ,Node* prev, Node* new, Node* now, int value)
{
	if(head == NULL)
	{			
		head = insert_node(prev, new, now, value);
	}
	else
	{
		new = head;
		prev = NULL;
		while( new && value > new->value )
		{
			prev = new;
			new = new->next;
		}
				
		if( NULL == prev )
			head = insert_node(prev, new, now, value);
		else
			(void)insert_node(prev, new, now, value);
	}

	return head;
}

void printf_list(Node *head)
{
	Node *p = NULL;
	if( head != NULL )
	{
		p = head;
		while(1)
		{
			if(p == NULL)
			{
				printf("NULL\n");
				break;
			}
			printf("%d -> ", p->value);
			p = p->next;
		}
	}
}

Node *input_ins(Node *head, Node* prev, Node* new, Node* now, char *ins)
{
	int i = 0;
	int length = strlen(ins) - strlen(INSERT);
	char *num = ins + strlen(INSERT);
	int value = 0;
	for(i=0 ; i < length ; i++)
	{
		if((*num) == ' ')
		{
			length --;
			num ++;
		}
		else if( (*num) >= '0' && (*num) <= '9' )
		{
			break;
		}
	}
	//printf("%d\n",length);
	for( i = 0; i < length; i++)
	{
		value = value * 10 + (*num++) - '0';
		//num ++;
	}
	//printf("%d\n",value);
	head = make_list(head , prev,  new,  now, value);

	return head;
}

int main()
{
	int i = 0;
	int parser;
	List_info *p_list = &list;
	int input_num = 0;
	Node *now = NULL, *prev = NULL, *new = NULL;
	char *ins = (char *)malloc( sizeof(char) * INS_LEN );
	char c;
	
	p_list->Head = NULL;
	p_list->len = 0;

	for( i=0; i<3; i++)
	{
		printf("Please input num %d:", i+1);
		scanf("%d", &input_num);
		p_list->Head = make_list( p_list->Head, prev, new, now, input_num);
	}
	printf_list( p_list->Head );
	while ((c = getchar()) != EOF && c != '\n');//不停地使用getchar()获取缓冲中字符，直到获取的c是“\n”或文件结尾符EOF为止

	while(1)
	{
		memset(ins, '\0', INS_LEN);
		printf("Please input ins:");
		//scanf("%s", ins);	//make ' ' into '\0'
		gets(ins);	//save ' ', 
		parser = judge_ins(ins);
		if( parser == _quit ) 
			break;
		switch(parser)
		{
			case _insert:
				p_list->Head = input_ins( p_list->Head, prev, new, now, ins);
				printf_list( p_list->Head);
				break;
			case _delete:
				printf("delete\n");
				break;
			default:
				printf("warning: found not support instruction %d\n" , parser);
				break;
		}
		
	}
	
	free(ins);	
	return 0;
}
