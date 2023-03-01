/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:06 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/01 20:21:24 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finish(t_philo **philo)
{
	long long last;
	int		i;
	t_data	*data;
	t_info	info;

	info = (*philo)->info;
	data = (*philo)->data;
	while (1)
	{
		i = 0;
		while (++i < info.philo_num)
		{
			pthread_mutex_lock(&(data->philo[i]));
			last = (*philo)[i].last_eat;
			pthread_mutex_unlock(&(data->philo[i]));
			if (ft_gettime() - last > info.time_die)
			{
				pthread_mutex_lock(&(data->flag));
				data->end = 1;
				pthread_mutex_unlock(&(data->flag));
				pthread_mutex_lock(&(data->print));
				printf("%lld %d %s\n", ft_gettime() - info.start_time, \
									(*philo)[i].num + 1, "died");
				pthread_mutex_unlock(&(data->print));
				break ;
			}
		}
		pthread_mutex_lock(&(data->flag));
		if (data->end)
		{
			pthread_mutex_unlock(&(data->flag));
			break ;
		}
		pthread_mutex_unlock(&(data->flag));
	}
}

void	thread_init(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->info.philo_num)
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
	check_finish(&philo);
	i = 0;
	while (i < philo->info.philo_num)
		pthread_join(philo[i++].thread, 0);
}

int	fork_init(t_data *data, t_info info)
{
	int	i;

	data->fork = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info.philo_num);
	if (!data->fork)
		return (1);
	i = 0;
	while (i < info.philo_num)
	{
		if (pthread_mutex_init(&data->fork[i], 0) != 0)
			return (i + 1);
		i++;
	}
	if (pthread_mutex_init(&data->print, 0) != 0)
		return (-2);
	return (0);
}

int	data_init(t_data *data, t_info info)
{
	int	i;

	data->philo = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info.philo_num);
	i = 0;
	while (i < info.philo_num)
	{
		if (pthread_mutex_init(&data->philo[i], 0) != 0)
			return (i + 1);
		i++;
	}
	data->end = 0;
	pthread_mutex_init(&data->flag, 0);
	i = fork_init(data, info);
	return (0);
}

int	info_init(int argc, char **argv, t_info *info)
{
	info->philo_num = ft_atoll(argv[1]);
	info->time_die = ft_atoll(argv[2]);
	info->time_eat = ft_atoll(argv[3]);
	info->time_sleep = ft_atoll(argv[4]);
	info->start_time = ft_gettime();
	if (argc == 6)
		info->must_eat = ft_atoll(argv[5]);
	else
		info->must_eat = 0;
	if (info->philo_num < 0 || info->time_die < 0 || info->time_eat < 0 || \
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
