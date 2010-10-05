#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include "protomsg.h"

#ifndef __protomsg_<%= @name %>__
#define __protomsg_<%= @name %>__

#define <%= @name.upcase %>_MESSAGE_TYPE  <%= @type_number %>

<%= header %>

// getters
<%= getters %>
// setters
<%= setters %>
// lengths
<%= lengths %>
// memory
<%= memory %>
// io
<%= io %>

#endif
