/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:46:35 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/02 15:08:01 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->fork[philo->right]);
	print_state(*philo, "has taken a fork");
	if (philo->info.philo_num > 1)
	{
		pthread_mutex_lock(&data->fork[philo->left]);
		print_state(*philo, "has taken a fork");
		pthread_mutex_lock(&(data->philo[philo->num]));
		print_state(*philo, "is eating");
		philo->last_eat = ft_gettime();
		pthread_mutex_unlock(&(data->philo[philo->num]));
		ft_sleep(philo->info.time_eat);
		philo->count_eat++;
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
	else
		ft_sleep(philo->info.time_die + 1);
	pthread_mutex_unlock(&data->fork[philo->right]);
}

void	odd_fork(t_philo *philo, t_data *data)
{
	usleep(100);
	pthread_mutex_lock(&data->fork[philo->left]);
	print_state(*philo, "has taken a fork");
	if (philo->info.philo_num > 1)
	{
		pthread_mutex_lock(&data->fork[philo->right]);
		print_state(*philo, "has taken a fork");
		print_state(*philo, "is eating");
		pthread_mutex_lock(&(data->philo[philo->num]));
		philo->last_eat = ft_gettime();
		pthread_mutex_unlock(&(data->philo[philo->num]));
		ft_sleep(philo->info.time_eat);
		philo->count_eat++;
		pthread_mutex_unlock(&data->fork[philo->right]);
	}
	else
		ft_sleep(philo->info.time_die + 1);
	pthread_mutex_unlock(&data->fork[philo->left]);
}

void	sleep_think(t_philo *philo)
{
	if (philo->info.philo_num > 1)
	{
		print_state(*philo, "is sleeping");
		ft_sleep(philo->info.time_sleep);
		print_state(*philo, "is thinking");
		usleep(100);
		if (philo->info.philo_num % 2)
			ft_sleep(philo->info.time_eat - philo->info.time_sleep);
	}
}

int	check_enough_eat(t_philo **philo, int *i)
{
	pthread_mutex_lock(&((*philo)->data->flag));
	if ((*philo)->data->end_eat == 0)
	{
		*i = -1;
		return (1);
	}
	pthread_mutex_unlock(&((*philo)->data->flag));
	return (0);
}

int	check_die(t_philo **philo, int *idx)
{
	long long	last;
	int			i;

	i = *idx;
	pthread_mutex_lock(&(*philo)->data->philo[i]);
	last = (*philo)[i].last_eat;
	pthread_mutex_unlock(&((*philo)->data->philo[i]));
	if (ft_gettime() - last >= (*philo)->info.time_die)
	{
		pthread_mutex_lock(&((*philo)->data->flag));
		(*philo)->data->end = 1;
		pthread_mutex_unlock(&((*philo)->data->flag));
		printf("%lld %d %s\n", ft_gettime() - (*philo)->info.start_time, \
		(*philo)[i].num + 1, "died");
		*idx = -1;
		return (1);
	}
	return (0);
}
