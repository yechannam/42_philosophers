#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pthread_mutex_t *m;

	m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&m[0], 0);
	free(m);
}

