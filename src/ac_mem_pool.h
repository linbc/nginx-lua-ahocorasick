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

/*�ڴ��,��ע����̰߳�ȫ*/
typedef struct _mem_pool_t
{
	int size;				/*�ڴ��С*/
	int unit;				/*��λԪ�ش�С*/
	void **data;			/*ָ�����ڴ��ַ����*/
	int len;
	void **head;			/*�����б�*/
	void **end;				/*�����б�β��ָ��*/
}ac_mem_pool;


/*��ʼ���ڴ��*/
 int ac_mem_pool_init(ac_mem_pool **pool,int unit,int size);

/*�ͷ��ڴ��*/
 int ac_mem_pool_free(ac_mem_pool *pool);

/*���ڴ���з������Ԫ��*/
 void *ac_mem_pool_alloc(ac_mem_pool *pool);

/*���ڴ���յ��ڴ��*/
 int ac_mem_pool_release(ac_mem_pool *pool,void *ptr);

/*��չ�ڴ�,ԭ�д�Сֱ�ӷŴ�����*/
 int __ac_mem_pool_expand(ac_mem_pool *pool);


#endif

