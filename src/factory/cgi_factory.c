#include <stdlib.h>

#include "cgi.h"
#include "factory/cgi_factory.h"

void* cgi_factory_create(CGI_OBJECT item)
{
	void *object = NULL;
	cgi_http_connection_t *connection = NULL;
	cgi_url_dltrie_t *url_trie = NULL;

	switch(item)
	{
	case HTTP_CONNECTION:
		connection = (cgi_http_connection_t*)malloc(sizeof(cgi_http_connection_t));
		connection->rbuffer = (char*)malloc(sizeof(char) * 
			CGI_HTTP_CONNECTION_READ_BUFFER_SIZE);
		connection->wbuffer = (char*)malloc(sizeof(char) * 
			CGI_HTTP_CONNECTION_WRITE_BUFFER_SIZE);
		connection->rsize = CGI_HTTP_CONNECTION_READ_BUFFER_SIZE;
		connection->wsize = CGI_HTTP_CONNECTION_WRITE_BUFFER_SIZE;
		object = connection;
		break;

	case PARAM_SLIST:
		object = (cgi_pslist_t*)malloc(sizeof(cgi_pslist_t));
		break;

	case URL_DLTRIE:
		url_trie = (cgi_url_dltrie_t*)malloc(sizeof(cgi_url_dltrie_t));
		url_trie->key = (char*)malloc(sizeof(char) * CGI_URL_DLTRIE_KEY_SIZE);
		url_trie->ksize = 0;
		object = url_trie;
		break;

	default:
		break;
	}

	return object;
}

void cgi_factory_destroy(void *object,CGI_OBJECT item)
{
	cgi_http_connection_t *connection = NULL;
	cgi_url_dltrie_t *url_trie = NULL;
	switch(item)
	{
	case HTTP_CONNECTION:
		connection = (cgi_http_connection_t*)object;
		free(connection->rbuffer);
		free(connection->wbuffer);
		break;

	case URL_DLTRIE:
		url_trie = (cgi_url_dltrie_t*)object;
		free(url_trie->key);
		break;

	defualt:
		break;
	}
	free(object);
}
