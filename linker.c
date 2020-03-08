#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

#define INS_LEN 20
#define MAX 10
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

Node *insert_node(Node* prev, Node* new, int value)
{
	Node *p = NULL;
	p = (Node *)malloc( sizeof(Node) );
	if(p == NULL)  
	{
		printf("malloc Node now failed!\r\n");
	}
	else
	{
		p->value = value;
		p->next = new;
		if( prev != NULL )
			prev->next = p;
	}
	return p;
}

Node *make_node(Node* head, int value)
{
	Node *prev = NULL, *now = NULL,*new = head;
	if( new == NULL )
	{			
		head = insert_node( prev, new, value);
	}
	else
	{
		while( new && value > new->value )
		{
			prev = new;
			new = new->next;
		}
				
		if( new == head )
			head = insert_node( prev, new, value);
		else
			(void)insert_node( prev, new, value);
	}

	return head;
}

Node *delete_node( Node* head, int value)
{
	Node *p = head, *prev = NULL;
	while ( p && (p->value <= value) )
	{
		if( p->value == value )
		{
			if( p == head )
			{
				head = p->next;
				free(p);
				p = head;
			}
			else
			{
				prev->next = p->next;
				free(p);
				p = prev->next;
			}
		}
		else
		{
			prev = p;
			p = p->next;
		}
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

int list_len(Node *head)
{
	Node *p = head;
	int length = 0;
	while( p != NULL )
	{
		length ++;
		p = p->next;
	}
	return length;
}

Node *input_ins(Node *head, char *ins)
{
	int i = 0;
	int length = strlen(ins) - strlen(INSERT);
	char *num = ins + strlen(INSERT);
	int value = 0;
	int ls_len = list_len( head );

	if( ls_len < MAX )
	{
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
		for( i = 0; i < length; i++)
		{
			value = value * 10 + (*num++) - '0';
			//num ++;
		}

		return make_node( head, value);
	}
	else
	{
		return head;
	}
		
}

Node *delete_ins(Node *head, char *ins)
{
	int i = 0;
	int length = strlen(ins) - strlen(DELETE);
	char *num = ins + strlen(DELETE);
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
	for( i = 0; i < length; i++)
	{
		value = value * 10 + (*num++) - '0';
	}
	
	return delete_node( head, value);
}

int main()
{
	int i = 0;
	int parser;
	List_info *p_list = &list;
	int input_num = 0;
	char *ins = (char *)malloc( sizeof(char) * INS_LEN );
	char c;
	
	p_list->Head = NULL;
	p_list->len = 0;

	for( i=0; i<3; i++)
	{
		printf("Please input num %d:", i+1);
		scanf("%d", &input_num);
		p_list->Head = make_node( p_list->Head, input_num);
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
				p_list->Head = input_ins( p_list->Head, ins);
				break;
			case _delete:
				p_list->Head = delete_ins( p_list->Head, ins);
				break;
			default:
				printf("warning: found not support instruction %d\n" , parser);
				break;
		}
		printf_list( p_list->Head);
	}
	
	free(ins);	
	return 0;
}
