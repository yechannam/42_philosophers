/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:06 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/02 12:52:39 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init_start(t_data *data)
{
	if (pthread_mutex_init(&data->print, 0) != 0)
		return (1);
	if (pthread_mutex_init(&data->flag, 0) != 0)
	{
		pthread_mutex_destroy(&data->print);
		return (1);
	}
	return (0);
}

int	fork_init(t_data *data, t_info info)
{
	int	i;

	data->fork = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info.philo_num);
	if (!data->fork)
		return (-1);
	i = 0;
	while (i < info.philo_num)
	{
		if (pthread_mutex_init(&data->fork[i], 0) != 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	data_init(t_data *data, t_info info)
{
	int	i;

	data->philo = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info.philo_num);
	if (!data->philo)
		return (-1);
	i = 0;
	while (i < info.philo_num)
	{
		if (pthread_mutex_init(&data->philo[i], 0) != 0)
			return (i + 1);
		i++;
	}
	data->end = 0;
	data->end_eat = info.philo_num;
	return (0);
}

int	info_init(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (1);
	info->philo_num = ft_atoll(argv[1]);
	info->time_die = ft_atoll(argv[2]);
	info->time_eat = ft_atoll(argv[3]);
	info->time_sleep = ft_atoll(argv[4]);
	info->start_time = ft_gettime();
	if (argc == 6)
	{
		info->must_eat = ft_atoll(argv[5]);
		if (info->must_eat <= 0)
			return (-1);
	}
	else
		info->must_eat = 0;
	if (info->philo_num <= 0 || info->time_die < 0 || info->time_eat < 0 || \
		info->time_sleep < 0 || info->must_eat < 0)
		return (-1);
	return (0);
}

int	philo_init(t_philo **philo, t_info info, t_data *data)
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
		(*philo)[i].finish_eat = 0;
		(*philo)[i].count_eat = 0;
		(*philo)[i].info = info;
		(*philo)[i].data = data;
		i++;
	}
	return (0);
}
