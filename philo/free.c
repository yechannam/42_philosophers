/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:13:14 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/25 16:20:53 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_fork(t_info *info, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	free(info->fork);
	return (1);
}

int	free_print(t_info *info)
{
	free_fork(info, info->philo_num);
	pthread_mutex_destroy(&info->print);
	return (1);
}

int	free_philo_fork(t_philo **philo, t_info *info)
{
	free_fork(info, info->philo_num);
	free(*philo);
	return (1);
}
