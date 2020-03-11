#ifndef ALGORITHM_LIST_H
#define ALGORITHM_LIST_H
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _NodeP NodeElmt;
typedef struct _ListP List;

//对角矩阵节点
struct NodeElmt
{
	int index;				//节点索引
	double matrixdata;		//节点数据
	double *pmatrixidata;	//所有节点列数据
	struct NodeElmt* next;	//下一节点索引
};


//对角矩阵节点链表
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



//矩阵链表初始化
void Matrix_Init(List* list)
{
	list->size = 0;
	list->head = NULL;
	list->head = NULL;
}


//矩阵链表添加
/********************************************
	Description:    
	Input :	List 输入的链表指针
			
	Output : 无
	Return : 
	Others : 
********************************************/
int Matrix_Add(List* list, NodeElmt* element)
{
	NodeElmt *new_element;

	//分配空间
	if ((new_element = (NodeElmt *)malloc(sizeof(NodeElmt))) == NULL)
	{
		return -1;
	}

	//插入元素
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


//矩阵链表重排序
void Matrix_Sort(List* list)
{


}


//删除指定节点
 void Matrix_Del(List* list, int index)
{


 }

 //销毁矩阵链表
 void Matrix_Destroy(List* list)
 {

 }

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ALGORITHM_LIST_H */