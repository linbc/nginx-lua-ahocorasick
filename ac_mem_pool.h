#ifndef _COMM_MEM_POOL_H_
#define _COMM_MEM_POOL_H_

#define __mem_pool_check(pool) {\
		if( !(pool) || \
			!(pool)->data || \
			(pool)->unit <= 0 || \
			(pool)->size < (pool)->unit || \
			!(pool)->head || \
			(pool)->len <= 0) \
			assert(0);}

/*内存池,请注意非线程安全*/
typedef struct _mem_pool_t
{
	int size;				/*内存大小*/
	int unit;				/*单位元素大小*/
	void **data;			/*指向大块内存地址数组*/
	int len;
	void **head;			/*可用列表*/
	void **end;				/*可用列表尾部指针*/
}ac_mem_pool;


/*初始化内存池*/
 int ac_mem_pool_init(ac_mem_pool **pool,int unit,int size);

/*释放内存池*/
 int ac_mem_pool_free(ac_mem_pool *pool);

/*从内存池中分配可用元素*/
 void *ac_mem_pool_alloc(ac_mem_pool *pool);

/*将内存回收到内存池*/
 int ac_mem_pool_release(ac_mem_pool *pool,void *ptr);

/*扩展内存,原有大小直接放大两倍*/
 int __ac_mem_pool_expand(ac_mem_pool *pool);


#endif

