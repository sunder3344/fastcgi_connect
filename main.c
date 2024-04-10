#include <stdio.h>
#include <stdlib.h>
#include "fcgi_util.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int get() {
    Fcgi_t *c;
    c = (Fcgi_t *)malloc(sizeof(Fcgi_t));
    FCGI_init(c);
    setRequestId(c, 1); /*1 用来表明此消息为请求开始的第一个消息*/
    sockConnect(c, "127.0.0.1", 9000);
    sendBeginRequestRecord(c);

    sendParams(c, "SCRIPT_FILENAME", "/home/sunzhidong/bin/c/1.php");
    sendParams(c, "REQUEST_METHOD", "GET");
    sendParams(c, "CONTENT_LENGTH", "0"); //　0 表示没有　body
    sendParams(c, "CONTENT_TYPE", "text/html");
    sendParams(c, "QUERY_STRING", "name=derek&secondname=sunder");

    sendEndRequestRecord(c);

	char *content = malloc(sizeof(char) * 1);
	char *headstr = malloc(sizeof(char) * 1);
	Fcgi_res_head *head[2];
	bzero(content, 1);
	bzero(headstr, 1);
    renderContent(c, &headstr, &content);
	printf("headstr=%s\n", headstr);
	explode(headstr, "\r\n", head);
	printf("head1.name=%s, value=%s\n", head[0]->name, head[0]->value);
    printf("head2.name=%s, value=%s\n", head[1]->name, head[1]->value);
	printf("read from php, head = %s, content = %s\n", headstr, content);

	//free(head);
	free(content);
    FCGI_close(c);
    return 0;
}

int post() {
    Fcgi_t *c;
    c = (Fcgi_t *)malloc(sizeof(Fcgi_t));
    FCGI_init(c);
    setRequestId(c, 1); /*1 用来表明此消息为请求开始的第一个消息*/
    sockConnect(c, "127.0.0.1", 9000);
    sendBeginRequestRecord(c);

    sendParams(c, "SCRIPT_FILENAME", "/home/sunzhidong/bin/c/1.php");
    sendParams(c, "REQUEST_METHOD", "POST");
    sendParams(c, "CONTENT_LENGTH", "26"); //　0 表示没有body,有则是body的长度
    sendParams(c, "CONTENT_TYPE", "text/html");
    sendParams(c, "QUERY_STRING", "name=derek&secondname=sunder");

    sendEndRequestRecord(c);
	sendBody(c, "abcdEFGhijklmnopQrstuvwxyz");

    char *content = malloc(sizeof(char) * 1);
    char *headstr = malloc(sizeof(char) * 1);
	Fcgi_res_head *head[2];
    bzero(content, 1);
	bzero(headstr, 1);
    renderContent(c, &headstr, &content);
	printf("headstr=%s\n", headstr);
	explode(headstr, "\r\n", head);
	printf("head1.name=%s, value=%s\n", head[0]->name, head[0]->value);
	printf("head2.name=%s, value=%s\n", head[1]->name, head[1]->value);
    printf("read from php, head = %s, content = %s\n", headstr, content);

	//free(head);
    free(content);
    FCGI_close(c);
    return 0;
}

int main() {
	//get();
	post();
}
