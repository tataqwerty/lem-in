#include "libft.h"
#include <stdio.h>

void	func_create(t_list ***list, t_list *new, int *size)
{
	t_list	**new_list;
	int		i;

	i = 0;
	new_list = (t_list **)malloc(sizeof(t_list *) * (*size + 1));
	i = 0;
	while (i < *size)
	{
		new_list[i] = (*list)[i];
		i++;
	}
	new_list[i] = new;
	if (*size > 0)
		free(*list);
	*size += 1;
	*list = new_list;	
}

int		main(void)
{
	t_list **link_list;
	int size = 0;
	t_list *new_list;
	t_list *new_list2;
	t_list *new_list3;

	new_list = (t_list *)malloc(sizeof(t_list));
	new_list->next = NULL;
	new_list->content = ft_strdup("Hello");

	func_create(&link_list, new_list, &size);
	
	new_list2 = (t_list *)malloc(sizeof(t_list));
	new_list2->next = NULL;
	new_list2->content = ft_strdup(", World!");
	
	func_create(&link_list, new_list2, &size);

	new_list3 = (t_list *)malloc(sizeof(t_list));
	new_list3->next = NULL;
	new_list3->content = ft_strdup("tralala");

	func_create(&link_list, new_list3, &size);

	int i = 0;
	while (i < size)
	{
		printf("content = %s\n", link_list[i]->content);
		i++;
	}
	while (1)
		;
	return (0);
}