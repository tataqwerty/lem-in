#ifndef LEM_IN_H
# define LEM_IN_H
typedef	struct		s_ant
{
	int				counter;
	char			*room_name;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_alist
{
	void			*link;
	struct s_alist	*next;
}					t_alist;

typedef struct		s_room
{
	char			starter_point : 2;
	char			*name;
	t_alist			*neighbour;
	struct s_room	*next;
}					t_room;

typedef struct
{
	int				ants;
	int				rooms;
	int				lines;
	t_list			*line_list;
	t_ant			*ant;
	t_room			*room;
}					t_str;

#endif