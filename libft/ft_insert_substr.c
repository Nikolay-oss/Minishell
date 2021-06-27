#include "libft.h"

char	*ft_insert_substr(const char *s, const char *substr, size_t pos)
{
	char	*str;
	size_t	substr_size;
	size_t	s_size;

	if (!s || !substr)
		return (NULL);
	s_size = ft_strlen(s);
	if (pos > s_size)
		return (ft_strdup(s));
	substr_size = ft_strlen(substr);
	str = (char *)ft_calloc(substr_size + s_size + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s, pos);
	ft_memcpy(str + pos, substr, substr_size);
	ft_memcpy(str + pos + substr_size, s + pos, s_size - pos);
	return (str);
}
