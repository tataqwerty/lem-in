#include "lem-in.h"
#include <stdio.h>

t_room		*init_room(char *name, char priority)
{
	t_room	*new;

	new = (t_room*)malloc(sizeof(t_room));
	new->x = 0;
	new->y = 0;
	new->level = 0;
	new->links_size = 0;
	new->priority = priority;
	new->used = 0;
	new->iq = 0;
	new->visited = 0;
	new->name = ft_strdup(name);
	new->parent = NULL;
	new->next = NULL;
	new->links = NULL;
	new->links_size = 0;
	return (new);
}

void	enqueue(t_queue **queue, t_room *room)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = *queue;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new = (t_queue *)malloc(sizeof(t_queue));
	new->next = NULL;
	new->elem = room;
	new->elem->iq = 1;	
	if (!*queue)
		*queue = new;
	else
		tmp->next = new;
}

void	dequeue(t_queue **queue)
{
	t_queue	*tmp;

	if (!*queue)
		return ;
	tmp = (*queue)->next;
	(*queue)->elem->iq = 0;
	free(*queue);
	*queue = tmp;
}

void	func(t_queue *queue)
{
	t_room	*room2;
	t_room	*room3;

	room2 = init_room("2", 0);
	room3 = init_room("3", 0);
	// enqueue(&queue, room2);
	// enqueue(&queue, room3);
	dequeue(&queue);
	dequeue(&queue);
	dequeue(&queue);
	dequeue(&queue);
	dequeue(&queue);
}

int		main(void)
{
	t_room	*room1;

	room1 = init_room("1", 0);

	t_queue	*queue;

	queue = NULL;
	enqueue(&queue, room1);
	func(queue);
	while (queue)
	{
		printf("name = %s\n", queue->elem->name);
		queue = queue->next;
	}
	return (0);
}