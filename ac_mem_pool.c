#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "ac_mem_pool.h"

/*初始化内存池*/
int ac_mem_pool_init(ac_mem_pool **pool,int unit,int size)
{
	int num = 0, i = 0;
	size_t data = 0;
	if(size <= 0 || size < unit)  return -1;
	num = size / unit;
	size = unit * num;
	if(*pool && (*pool)->data) ac_mem_pool_free(*pool);

	*pool = (ac_mem_pool *)malloc(sizeof(ac_mem_pool));

	(*pool)->data = (void **)malloc(sizeof(void *));
	(*pool)->data[0] = malloc(size);
	/*内存分配失败*/
	if(!(*pool)->data[0]) 
	{
		free((*pool)->data);
		free(*pool);
		*pool = NULL;
		return -2;
	}
	memset((*pool)->data[0] ,0 , size);
	(*pool)->unit = unit;
	(*pool)->size = size;
	(*pool)->len = 1;
	/*直接分配num长度的数组，地址是连续的*/
	(*pool)->head = (void **)malloc(sizeof(void *) * num);
	data = (size_t)(*pool)->data[0];
	/*初始化可用列表*/
	for(i = 0; i < num; ++i)
	{
		(*pool)->head[i] = (void *)data;
		data += unit;
	}
	(*pool)->end = &((*pool)->head[num -1]);
	return 0;
}

/*释放内存池*/
int ac_mem_pool_free(ac_mem_pool *pool)
{
	int i = 0;
	__mem_pool_check(pool);
	for(i = 0 ;i < pool->len; ++i)
	{
		free(pool->data[i]);
	}
	free(pool->data);
	free(pool->head);
	free(pool);
	return 0;
}

/*从内存池中分配可用元素*/
void *ac_mem_pool_alloc(ac_mem_pool *pool)
{
	__mem_pool_check(pool);
	if(pool->head > pool->end && __ac_mem_pool_expand(pool)) return NULL;
	return *(pool->end--);
}

/*将内存回收到内存池*/
int ac_mem_pool_release(ac_mem_pool *pool,void *ptr)
{
	int i = 0;
	size_t pAddr = 0;
	__mem_pool_check(pool);
	if(!ptr) return 0;
	pAddr = (size_t)ptr;
	/*查找ptr所属的内存页*/
	for(i = 0; i < pool->len; ++i)
	{
		if(pAddr >= (size_t)pool->data[i] && 
			pAddr < (size_t)pool->data[i] + pool->size)
		{
			break;
		}
	}
	if(i == pool->len) return 1;
	*(++pool->end) = ptr;
	return 0;
}

/*扩展内存,原有大小直接放大两倍*/
int __ac_mem_pool_expand(ac_mem_pool *pool)
{
	int len = 0, num = 0, i = 0, j = 0;
	void **data = NULL;
	size_t _data = 0;
	__mem_pool_check(pool);
	len = pool->len * 2;
	/*追加内存页数组*/
	data = (void **)realloc(pool->data ,sizeof(void *) * len);
	if(!data) return 2;
	pool->data = data;
	num = pool->size / pool->unit;
	/*追加节点列表*/
	data  = (void **)realloc(pool->head, sizeof(void *) * num * len);
	if(!data) return 3;
	if(data != pool->head)
	{
		/*修复end指针*/
		pool->end = pool->end - pool->head + data;
		pool->head = data;
	}

	for(i = pool->len; i < len; ++i)
	{
		/*追加内存页*/
		pool->data[i] = malloc(pool->size);
		if(!pool->data[i]) break;
		memset(pool->data[i], 0, pool->size);
		/*更新可用列表*/
		_data = (size_t) pool->data[i]; 
		for(j = 0; j < num; ++j)
		{
			*(++pool->end) = (void *)_data;
			_data += pool->unit;
		}
	}
	if(i == pool->len) return 4;
	pool->len  = i;
	return 0;
}


