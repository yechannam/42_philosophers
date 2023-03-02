/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:13:14 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/02 12:11:49 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philo_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->flag);
	pthread_mutex_destroy(&data->print);
	return (1);
}

int	free_philo(t_data *data, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->philo);
	free_philo_mutex(data);
	return (1);
}

int	free_fork(t_data *data, int max, t_info info)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	free_philo(data, info.philo_num);
	return (1);
}
