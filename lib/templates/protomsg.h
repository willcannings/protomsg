#include <stdio.h>

#ifndef __protomsg__
#define __protomsg__

#define PROTO_MESSAGE_VERSION 1
#define read_struct(sock, structure, size, error) {\
  ssize_t bytes_read = 0, bytes_total = 0;\
  error = 0;\
  while(bytes_total < size) {\
    bytes_read = read(sock, structure + bytes_total, size - bytes_total);\
    if(bytes_read != -1) {\
      bytes_total += bytes_read;\
    } else {\
      error = errno;\
      bytes_total = size;\
    }\
  }\
}

#endif
