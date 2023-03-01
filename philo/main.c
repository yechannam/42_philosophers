/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/01 20:22:08 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_ing(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (philo->num % 2 == 0)
			even_fork(philo, philo->data);
		else
			odd_fork(philo, philo->data);
		if (philo->info.philo_num > 1)
		{
			print_state(*philo, "is sleeping");
			ft_sleep(philo->info.time_sleep);
			print_state(*philo, "is thinking");
			usleep(100);
			if (philo->info.philo_num % 2)
				ft_sleep(philo->info.time_eat - philo->info.time_sleep);
		}
		else
			ft_sleep(philo->info.time_die);
		pthread_mutex_lock(&(philo->data->flag));
		int i = philo->data->end;
		pthread_mutex_unlock(&(philo->data->flag));
		if (i)
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	t_info	info;
	int		er;

	if (argc != 5 && argc != 6)
		return (1);
	if (info_init(argc, argv, &info))
		return (1);
	er = data_init(&data, info);
	//if (er == -2)
	//	return (free_print(&data, info));
	//if (er > 0)
	//	return (free_fork(&data, er));
	if (philo_init(&philo, info, &data))
		return (free_philo_fork(&philo, info, &data));
	thread_init(philo);
	//free_philo_fork(&philo, info, &data);
	return (0);
}
