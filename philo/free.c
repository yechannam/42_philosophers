/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:13:14 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/01 18:13:25 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_fork(t_data *data, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	return (1);
}

int	free_print(t_data *data, t_info info)
{
	free_fork(data, info.philo_num);
	pthread_mutex_destroy(&data->print);
	return (1);
}

int	free_philo_fork(t_philo **philo, t_info info, t_data *data)
{
	free_print(data, info);
	free(*philo);
	return (1);
}
