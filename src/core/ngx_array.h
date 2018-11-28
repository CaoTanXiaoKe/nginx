
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    void        *elts;      /* 指向实际的数据存储区域。*/
    ngx_uint_t   nelts;     /* 数组实际元素个数。*/
    size_t       size;      /* 数组的单个元素的大小，单位是字节。*/
    ngx_uint_t   nalloc;    /* 数组的容量。表示该数组在不引发扩容的前提下，
                               可以最多存储的元素的个数。当nelts增长到达
                               nalloc时，如果再增加元素会向 C++ 中的 vector
                               一样扩容，只是扩容后，原来的内存没有被释放。
                            */
    ngx_pool_t  *pool;      /* 该数组用来分配内存的内存池。*/
} ngx_array_t;


ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
void ngx_array_destroy(ngx_array_t *a);
void *ngx_array_push(ngx_array_t *a);
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);


static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
