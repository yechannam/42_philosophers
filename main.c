/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/15 20:59:23 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_init(t_info *info)
{
	int	i;

	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->fork)
		return (1);
	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_init(&info->fork[i], 0);
		i++;
	}
	return (0);
}

int	free_philo(t_philo **philo)
{
	free(*philo);
	return (-1);
}

int	ft_gettime(void)
{
	struct timeval	time;
	int				now;

	gettimeofday(&time, 0);
	now = time.tv_sec * 1000000 + time.tv_usec;
	return (now);
}

int	info_init(int argc, char **argv, t_info *info)
{
	info->philo_num = atoi(argv[1]);
	info->time_die = atoi(argv[2]);
	info->time_eat = atoi(argv[3]);
	info->time_sleep = atoi(argv[4]);
	info->start_time = ft_getime();
	if (info->philo_num < 0 || info->start_time)
		return (1);
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

	*philo = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_num);
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

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!info_init(argc, argv, &info))
		return (free_fork(&info));
	if (philo_init(&philo, info))
		return (free_philo(&philo));
	return (0);
}
