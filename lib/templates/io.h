#define write_<%= @name %>(msg, sock, error) {\
  error = 0;\
  ssize_t written = writev(sock, (const struct iovec *)msg, <%= variable_attributes.size + 1 %>);\
  if(written != <%= @name %>_length(msg)){\
    error = errno;\
  }\
}

#define read_<%= @name %>(msg, sock, error) {\
  msg = (<%= @name %> *) malloc(sizeof(<%= @name %>));\
  msg->header_length = sizeof(<%= @name %>_header);\
  msg->header = (<%= @name %>_header *)malloc(sizeof(<%= @name %>_header));\
  read_struct(sock, msg->header, sizeof(<%= @name %>_header), error);\
  if(!error) {\
    if(msg->header->_version == PROTO_MESSAGE_VERSION && msg->header->_type == <%= @name.upcase %>_MESSAGE_TYPE) {\
      <% variable_attributes.each do |attr| %>msg-><%= attr.name %>_length = msg->header-><%= attr.name %>_length;\
      msg-><%= attr.name %> = malloc(msg->header-><%= attr.name %>_length);\
      <% end %>readv(sock, (const struct iovec *)msg + 1, <%= variable_attributes.size %>);\
    } else {\
      error = INVALID_PROTOMSG_HEADER;\
    }\
  }\
}
