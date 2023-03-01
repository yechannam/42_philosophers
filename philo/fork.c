/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:46:35 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/01 20:04:55 by yecnam           ###   ########.fr       */
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
		print_state(*philo, "is eating");
		pthread_mutex_lock(&(data->philo[philo->num]));
		philo->last_eat = ft_gettime();
		pthread_mutex_unlock(&(data->philo[philo->num]));
		ft_sleep(philo->info.time_eat);
		philo->count_eat++;
		if (philo->count_eat >= philo->info.must_eat)
			philo->finish_eat = 1;
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
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
		if (philo->count_eat >= philo->info.must_eat)
			philo->finish_eat = 1;
		pthread_mutex_unlock(&data->fork[philo->right]);
	}
	pthread_mutex_unlock(&data->fork[philo->left]);
}
