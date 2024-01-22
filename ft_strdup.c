#include "minishell.h"

int	is_double_quote(char *str, int start)
{
	int	i;
	int	quote;

	i = start;
	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote > 0)
		return (SUCCESS);
	return (FAIL);
}

int	is_single_quote(char *str, int start, int end)
{
	if (str[start] == '\'' && str[end - 1] == '\'')
		return (SUCCESS);
	return (FAIL);
}

static int	is_str_quoted(char *str, int start, int end)
{
	int	i;

	i = start;
	if (str[i] && ((str[i] != '"' || str[end - 1] != '"') && \
		is_single_quote(str, start, end) == FAIL))
		return (FAIL);
	i++;
	while (i < (end - 1))
	{
		if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

char	*ft_strdup_quote(char *src, int start, int end)
{
	char	*dest;
	int		size_src;
	int		i;
	int		origin;

	size_src = end - start;
	origin = start;
	if (is_single_quote(src, start, end) == SUCCESS || \
		is_str_quoted(src, start, end) == SUCCESS)
		size_src -= 2;
	if (size_src + 1 < 0)
		return (NULL);
	if (ft_strcmp(src, "\0") == SUCCESS)
	{
		dest = malloc(sizeof(char));
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		if (src[start] && (start == end - 1 || start == origin) && \
			(src[start] == '\'' || src[start] == '"'))
			start++;
		else
			dest[i++] = src[start++];
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src, int start, int end)
{
	char	*dest;
	int		size_src;
	int		i;
	int		status;
	char	c;

	status = OUT_QUOTE;
	size_src = end - start;
	c = '"';
	if (is_str_quoted(src, start, end) == SUCCESS)
		return (ft_strdup_quote(src, start, end));
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	if (src[start] == '"' || src[start] == '\'')
	{
		c = src[start];
		if (src[start + 1] == c)
			start += 2;
		else
		{
			status = change_status_or_not(status);
			dest[i++] = src[start++];
		}
	}
	while (start < end)
	{
		if (src[start] == c && status == IN_QUOTE)
		{
			status = change_status_or_not(status);
			if (start + 1 < end && src[start + 1] == ' ')
				break ;
			dest[i++] = src[start++];
		}
		else if ((src[start] == '\'' || src[start] == '"') && \
				status == OUT_QUOTE)
		{
			c = src[start];
			if (src[start + 1] == c)
				start += 2;
			else
			{
				status = change_status_or_not(status);
				dest[i++] = src[start++];
			}
		}
		else
			dest[i++] = src[start++];
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_split(char *src, int start, int end)
{
	char	*dest;
	int		size_src;

	size_src = end - start;
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	return (ft_strcpy(dest, src, start, end));
}

char	*simple_strdup(char *s)
{
	char	*result;
	int		final_len;
	int		i;

	final_len = ft_strlen(s) + 1;
	result = malloc(final_len * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
