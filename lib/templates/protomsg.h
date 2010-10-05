#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#ifndef __protomsg__
#define __protomsg__

#define PROTO_MESSAGE_VERSION   1
#define INVALID_PROTOMSG_HEADER 1

#define read_struct(sock, structure, size, error) {\
  error = 0;\
  ssize_t _bytes_read = 0, _bytes_total = 0;\
  while(_bytes_total < size) {\
    _bytes_read = read(sock, structure + _bytes_total, size - _bytes_total);\
    if(_bytes_read != -1) {\
      _bytes_total += _bytes_read;\
    } else {\
      error = errno;\
      _bytes_total = size;\
    }\
  }\
}

#define create_server_socket(port, queue, sock, error) {\
  error = 0;\
  sock = socket(AF_INET, SOCK_STREAM, 0);\
  struct sockaddr_in _servaddr;\
  memset(&_servaddr, 0, sizeof(_servaddr));\
  _servaddr.sin_family      = AF_INET;\
  _servaddr.sin_addr.s_addr = htonl(INADDR_ANY);\
  _servaddr.sin_port        = htons(port);\
  error = bind(sock, (const struct sockaddr *)&_servaddr, sizeof(_servaddr));\
  if(error) {\
    error = errno;\
  } else {\
    error = listen(sock, queue);\
    if(error) {\
      error = errno;\
    }\
  }\
}

#define accept_client(sock, client) {\
  client = accept(sock, NULL, NULL);\
}

#define connect_to_server(address, port, sock, error) {\
  error = 0;\
  sock = socket(AF_INET, SOCK_STREAM, 0);\
  struct sockaddr _servaddr;\
  socklen_t _servaddr_length;\
  get_socket_addr_from_hostname(address, _servaddr, _servaddr_length, error);\
  if(!error) {\
    ((struct sockaddr_in *) &_servaddr)->sin_port = htons(port);\
    error = connect(sock, (struct sockaddr *) &_servaddr, sizeof(_servaddr));\
  }\
}

#define get_socket_addr_from_hostname(host, servaddr, length, error) {\
  struct addrinfo _hints, *_result;\
  memset(&_hints, 0, sizeof(_hints));\
  _hints.ai_family   = AF_INET;\
  _hints.ai_socktype = SOCK_STREAM;\
  _hints.ai_protocol = IPPROTO_TCP;\
  error = getaddrinfo(host, NULL, &_hints, &_result);\
  if(!error) {\
    length = _result->ai_addrlen;\
    memcpy(&servaddr, _result->ai_addr, length);\
    freeaddrinfo(_result);\
  }\
}

#endif
