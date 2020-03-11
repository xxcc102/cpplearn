#ifndef ALGORITHM_LIST_H
#define ALGORITHM_LIST_H
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _NodeP NodeElmt;
typedef struct _ListP List;

//�ԽǾ���ڵ�
struct NodeElmt
{
	int index;				//�ڵ�����
	double matrixdata;		//�ڵ�����
	double *pmatrixidata;	//���нڵ�������
	struct NodeElmt* next;	//��һ�ڵ�����
};


//�ԽǾ���ڵ�����
struct List
{
	int size;
	NodeElmt *head;
	NodeElmt *tail;
};


//typedef int(*ListCompareFunc)(NodeElmt *value1, NodeElmt *value2);
//{
//
//}



//���������ʼ��
void Matrix_Init(List* list)
{
	list->size = 0;
	list->head = NULL;
	list->head = NULL;
}


//�����������
/********************************************
	Description:    
	Input :	List ���������ָ��
			
	Output : ��
	Return : 
	Others : 
********************************************/
int Matrix_Add(List* list, NodeElmt* element)
{
	NodeElmt *new_element;

	//����ռ�
	if ((new_element = (NodeElmt *)malloc(sizeof(NodeElmt))) == NULL)
	{
		return -1;
	}

	//����Ԫ��
	//new_element = element;
	if (list->head == NULL)
	{
		if (list->size == 0)
		{
			list->head = element;
			//list->tail = element;
		}

		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{
		
	}
	
}


//��������������
void Matrix_Sort(List* list)
{


}


//ɾ��ָ���ڵ�
 void Matrix_Del(List* list, int index)
{


 }

 //���پ�������
 void Matrix_Destroy(List* list)
 {

 }

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ALGORITHM_LIST_H */