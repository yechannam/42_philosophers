/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:46:35 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/25 19:43:01 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_fork(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->fork[philo->right]);
	print_state(*philo, info, "has taken a fork");
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&info->fork[philo->left]);
		print_state(*philo, info, "has taken a fork");
		print_state(*philo, info, "is eating");
		philo->last_eat = ft_gettime();
		ft_sleep(info->time_eat);
		philo->count_eat++;
		if (philo->count_eat >= info->must_eat && philo->eating_end != 1)
		{
			info->finish_eating++;
			philo->eating_end = 1;
		}
		pthread_mutex_unlock(&info->fork[philo->left]);
	}
	pthread_mutex_unlock(&info->fork[philo->right]);
}

void	odd_fork(t_philo *philo, t_info *info)
{
	usleep(200);
	pthread_mutex_lock(&info->fork[philo->left]);
	print_state(*philo, info, "has taken a fork");
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&info->fork[philo->right]);
		print_state(*philo, info, "has taken a fork");
		print_state(*philo, info, "is eating");
		philo->last_eat = ft_gettime();
		ft_sleep(info->time_eat);
		philo->count_eat++;
		if (philo->count_eat >= info->must_eat && philo->eating_end != 1)
		{
			info->finish_eating = info->finish_eating + 1;
			philo->eating_end = 1;
		}
		pthread_mutex_unlock(&info->fork[philo->right]);
	}
	pthread_mutex_unlock(&info->fork[philo->left]);
}
