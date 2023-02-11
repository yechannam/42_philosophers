/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:05:04 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/11 14:16:09 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*p_func(void *data)
{
	pthread_t tid;

	tid = pthread_self();

	char *thread_name = (char *)data;
	for (int i = 0; i < 3; i++)
	{
		printf("thread name:%s, tid: %x\n", thread_name, (unsigned int)tid);
		usleep(1000 * 1000);
	}
	return (0);
}

void	*p_func2(void *data)
{
	pthread_t tid;

	tid = pthread_self();

	char *thread_name = (char *)data;
	for (int i = 0; i < 3; i++)
	{
		printf("thread name:%s, tid: %x\n", thread_name, (unsigned int)tid);
		usleep(1000 * 1000 * 1000);
	}
	return (0);
}

int	main(void)
{
	pthread_t	pthread;
	int id;
	int status;
	char p1[] = "thr_main";
	char p2[] = "thr_2";

	id = pthread_create(&pthread, 0, p_func, (void*)p2);
	p_func2((void *)p1);
	printf("end\n");
}
