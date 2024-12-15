#include "minishell.h"

t_env	*my_lstlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	my_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*aux;

	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			aux = my_lstlast(*lst);
			aux->next = new;
		}
	}
}

/*
void	my_lstadd_front(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst && new)
		{
			new->next = *lst;
			*lst = new;
		}
		else if (new)
			*lst = new;
	}
}
*/

t_env	*my_lstnew(char *first_str, char *second_str)
{
	t_env	*list;

	list = (t_env *) malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->key = first_str;
	list->str = second_str;
	list->next = NULL;
	return (list);
}

void	free_env(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->key);
		free(temp->str);
		free(temp);
	}
}