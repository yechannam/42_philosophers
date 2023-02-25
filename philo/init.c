/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:06 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/25 19:27:03 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finish(t_info *info, t_philo **philo)
{
	int	i;

	i = 0;
	while (info->flag != 1)
	{
		if (info->finish_eating == info->philo_num && info->must_eat > 0)
		{
			info->flag = 1;
			pthread_mutex_lock(&(info->print));
			printf("All philosophers have eaten enough.\n");
			pthread_mutex_unlock(&(info->print));
		}
		i = 0;
		while (i < info->philo_num && info-> flag != 1)
		{
			if (ft_gettime() - (*philo)[i].last_eat > info->time_die)
			{
				info->flag = 1;
				pthread_mutex_lock(&(info->print));
				printf("%lld %d %s\n", ft_gettime() - info->start_time, \
									(*philo)[i].num + 1, "died");
				pthread_mutex_unlock(&(info->print));
			}
			i++;
		}
	}
}

void	thread_init(t_info *info, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->philo_num)
	{
		if (pthread_create(&philo[i].thread, 0, thread_ing, \
			(void *)&philo[i]) != 0)
		{
			while (j < i)
				pthread_join(philo[j++].thread, 0);
			return ;
		}
		i++;
	}
	check_finish(info, &philo);
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
		if (pthread_mutex_init(&info->fork[i], 0) != 0)
			return (i + 1);
		i++;
	}
	if (pthread_mutex_init(&info->print, 0) != 0)
		return (-2);
	return (0);
}

int	info_init(int argc, char **argv, t_info *info)
{
	int	i;

	info->philo_num = ft_atoll(argv[1]);
	info->time_die = ft_atoll(argv[2]);
	info->time_eat = ft_atoll(argv[3]);
	info->time_sleep = ft_atoll(argv[4]);
	info->start_time = ft_gettime();
	info->flag = 0;
	if (argc == 6)
		info->must_eat = ft_atoll(argv[5]);
	else
		info->must_eat = 0;
	if (info->philo_num < 0 || info->time_die < 0 || info->time_eat < 0 || \
		info->time_sleep < 0 || info->must_eat < 0)
		return (-1);
	i = fork_init(info);
	if (i)
		return (i);
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
