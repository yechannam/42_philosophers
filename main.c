/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/12 16:45:41 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	info_init(int argc, char **argv, t_info *info)
{
	info->argc = argc;
	info->argv = argv;
	info->philo_num = atoi(argv[1]);
	info->time_die = atoi(argv[2]);
	info->time_eat = atoi(argv[3]);
	info->time_sleep = atoi(argv[4]);
	info->start_time = gettimeofday()
	if (argc == 6)
		info->must_eat = atoi(argv[5]);
}

int	thread_init(pthread_t **philo, int argc, char **argv)
{
	int	i;

	*philo = (pthread_t *)malloc(sizeof(pthread_t) * argc);
	if (!*philo)
		return (1);
	i = 0;
	while (i < argc)
	{
		(*philo)[i];
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	*info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!info_init(argc, argv, &info))
		return (-1);
	if (thread_init(&philo, argc, argv))
		return (-1);
	return (0);
}
