/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/21 20:21:58 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long long wait_time, t_info *info)
{
	long long	start;
	long long	now;

	start = ft_gettime();
	while (info->flag != 1)
	{
		now = ft_gettime();
		if ((now - start) >= wait_time)
			break ;
		usleep(1);
	}
}

void	even_fork(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->fork[philo->right]);
	print_state(*philo, *info, "has taken a fork");
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&info->fork[philo->left]);
		print_state(*philo, *info, "has taken a fork");
		print_state(*philo, *info, "is eating");
		philo->last_eat = ft_gettime();
		printf("in fork : %lld\n", philo->last_eat);
		ft_sleep(info->time_eat, info);
		philo->last_eat = ft_gettime();
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
	pthread_mutex_lock(&info->fork[philo->left]);
	print_state(*philo, *info, "has taken a fork");
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&info->fork[philo->right]);
		print_state(*philo, *info, "has taken a fork");
		print_state(*philo, *info, "is eating");
		philo->last_eat = ft_gettime();
		ft_sleep(info->time_eat, info);
		philo->last_eat = ft_gettime();
		philo->count_eat++;
		if (philo->count_eat >= info->must_eat && philo->eating_end != 1)
		{
			info->finish_eating++;
			philo->eating_end = 1;
		}
		pthread_mutex_unlock(&info->fork[philo->right]);
	}
	pthread_mutex_unlock(&info->fork[philo->left]);
}

long long	ft_gettime(void)
{
	struct timeval	time;
	long long		now;

	gettimeofday(&time, 0);
	now = time.tv_sec * 1000 + time.tv_usec * 0.0001;
	return (now);
}

void	print_state(t_philo philo, t_info info, char *msg)
{
	long long		now;

	if (info.flag != 1)
	{
		pthread_mutex_lock(&(info.print));
		now = ft_gettime();
		printf("%lld %d %s\n", now - info.start_time, philo.num + 1, msg);
		pthread_mutex_unlock(&(info.print));
	}
}

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
		print_state(*philo, *info, "is sleeping");
		ft_sleep(info->time_sleep, info);
		print_state(*philo, *info, "is thinking");
	}
	return (0);
}

void	leaks_check(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (info_init(argc, argv, &info))
		return (free_fork(&info));
	if (philo_init(&philo, &info))
		return (free_philo_fork(&philo, &info));
	thread_init(&info, philo);
	free_philo_fork(&philo, &info);
	//atexit(leaks_check);
	return (0);
}