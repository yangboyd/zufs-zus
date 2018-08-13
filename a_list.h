/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * The toyfs reference file-system implementation via zufs
 *
 * Copyright (c) 2018 NetApp, Inc. All rights reserved.
 *
 * ZUFS-License: BSD-3-Clause. See module.c for LICENSE details.
 *
 * Authors:
 *	Shachar Sharon <sshachar@netapp.com>
 *	Sagi Manole <sagim@netapp.com>
 */
#ifndef _LINUX_ZUFS_A_LIST_H
#define _LINUX_ZUFS_A_LIST_H

#define _GNU_SOURCE
#include <stdlib.h>
//#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
//#include <string.h>
//#include <limits.h>
//#include <errno.h>

struct a_list_head {
	struct a_list_head *prev;
	struct a_list_head *next;
};

static inline void a_list_init(struct a_list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void _link_list(struct a_list_head *list,
			      struct a_list_head *prev,
			      struct a_list_head *next)
{
	next->prev = list;
	list->next = next;
	list->prev = prev;
	prev->next = list;
}

static inline void a_list_add(struct a_list_head *new,
			      struct a_list_head *head)
{
	_link_list(new, head->prev, head);
}

static inline void a_list_del(struct a_list_head *list)
{
	list->next->prev = list->prev;
	list->prev->next = list->next;
}

static inline void a_list_del_init(struct a_list_head *list)
{
	a_list_del(list);
	a_list_init(list);
}

static inline int a_list_empty(const struct a_list_head *head)
{
	return (head->next == head);
}

static inline void a_list_add_tail(struct a_list_head *list,
				   struct a_list_head *head)
{
	_link_list(list, head->prev, head);
}

#ifndef container_of
#define container_of(ptr, type, member) ({			\
	(type *)( (void *)ptr - offsetof(type,member) );})
#endif /* container_of */

#define a_list_first_entry(ptr, type, member)		\
	container_of((ptr)->next, type, member)

#endif /* _LINUX_ZUFS_A_LIST_H */