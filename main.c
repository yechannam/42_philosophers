/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/16 17:04:20 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	struct timeval	time;
	long long		now;

	gettimeofday(&time, 0);
	now = time.tv_sec * 1000000 + time.tv_usec;
	return (now);
}

void	print_state(t_philo philo, t_info info, char *msg)
{
	long long		now;

	now = ft_gettime();
	pthread_mutex_lock(&(info.print));
	printf("%lld %d %s\n", now - info.start_time, philo.num + 1, msg);
	pthread_mutex_unlock(&(info.print));
}

void	*threading(void *philo)
{
	return (0);
}

int	free_fork(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print);
	free(info->fork);
	return (-1);
}

int	free_philo_fork(t_philo **philo, t_info *info)
{
	free_fork(info);
	free(*philo);
	return (-1);
}

void	thread_init(t_info info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info.philo_num)
	{
		pthread_create(&philo[i].thread, 0, threading, (void *)philo);
		i++;
	}
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(philo[i].thread, 0);
		i++;
	}
}

int	fork_init(t_info *info)
{
	int	i;

	info->fork = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->fork)
		return (1);
	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_init(&info->fork[i], 0);
		i++;
	}
	pthread_mutex_init(&info->print, 0);
	return (0);
}

int	info_init(int argc, char **argv, t_info *info)
{
	info->philo_num = atoi(argv[1]);
	info->time_die = atoi(argv[2]);
	info->time_eat = atoi(argv[3]);
	info->time_sleep = atoi(argv[4]);
	info->start_time = ft_gettime();
	if (argc == 6)
	{
		info->must_eat = atoi(argv[5]);
		if (info->must_eat < 0)
			return (1);
	}
	if (fork_init(info))
		return (1);
	return (0);
}

int	philo_init(t_philo **philo, t_info info)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	if (!*philo)
		return (1);
	i = 0;
	while (i < info.philo_num)
	{
		(*philo)[i].num = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info.philo_num;
		(*philo)[i].last_eat = info.start_time;
		(*philo)[i].count_eat = 0;
		i++;
	}
	return (0);
}

void	leaks_check(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (info_init(argc, argv, &info))
		return (free_fork(&info));
	if (philo_init(&philo, info))
		return (free_philo_fork(&philo, &info));
	
	while (1)
	{
		print_state(philo[1], info, "yes");
		usleep(1000 * 10);
	}
	
	//thread_start(info, philo);
	//free_philo_fork(&philo, &info);
	//atexit(leaks_check);
	return (0);
}
