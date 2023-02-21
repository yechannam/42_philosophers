/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:06 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/21 20:18:55 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finish(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (info->flag != 1)
	{
		if (info->finish_eating == info->philo_num && info->must_eat != -1)
		{
			info->flag = 1;
			printf("full\n");
		}
		i = 0;
		while (i < info->philo_num && info-> flag != 1)
		{
			if (ft_gettime() - philo[i].last_eat > info->time_die)
			{
				printf("%lld - %lld = %lld   start time : %lld\n", ft_gettime(), philo[i].last_eat, ft_gettime() - philo[i].last_eat, info->start_time);
				print_state(philo[i], *info, "died");
				info->flag = 1;
			}
			i++;
		}
	}
}

void	thread_init(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_create(&philo[i].thread, 0, thread_ing, (void *)&philo[i]);
		i++;
	}
	check_finish(info, philo);
	i = 0;
	while (i < info->philo_num)
		pthread_join(philo[i++].thread, 0);
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
	info->flag = 0;
	if (argc == 6)
	{
		info->must_eat = atoi(argv[5]);
		if (info->must_eat < 0)
			return (1);
	}
	else
		info->must_eat = -1;
	if (fork_init(info))
		return (1);
	return (0);
}

int	philo_init(t_philo **philo, t_info *info)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (!*philo)
		return (1);
	i = 0;
	while (i < info->philo_num)
	{
		(*philo)[i].num = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->philo_num;
		(*philo)[i].last_eat = info->start_time;
		(*philo)[i].count_eat = 0;
		(*philo)[i].info = info;
		i++;
	}
	return (0);
}
