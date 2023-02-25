/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/25 16:40:29 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_ing(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = data;
	info = philo->info;
	while (info->flag != 1)
	{
		if (philo->num % 2 == 0)
			even_fork(philo, info);
		else
			odd_fork(philo, info);
		if (info->philo_num > 1)
		{
			print_state(*philo, info, "is sleeping");
			ft_sleep(info->time_sleep);
			print_state(*philo, info, "is thinking");
		}
		else
			while (info->flag != 1)
				;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;
	int		er;

	if (argc != 5 && argc != 6)
		return (1);
	er = info_init(argc, argv, &info);
	if (er == -1)
		return (1);
	if (er == -2)
		return (free_print(&info));
	if (er > 0)
		return (free_fork(&info, er));
	if (philo_init(&philo, &info))
		return (free_philo_fork(&philo, &info));
	thread_init(&info, philo);
	free_philo_fork(&philo, &info);
	return (0);
}
