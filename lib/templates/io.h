#define write_<%= @name %>(msg, sock, error) {\
  error = 0;\
  ssize_t _written = writev(sock, (const struct iovec *)msg, <%= variable_attributes.size + 1 %>);\
  if(_written != <%= @name %>_length(msg)){\
    error = errno;\
  }\
}

#define read_<%= @name %>(msg, sock, error) {\
  error = 0;\
  if(!msg) {\
    msg = (<%= @name %> *) calloc(1, sizeof(<%= @name %>));\
    msg->header_length = sizeof(<%= @name %>_header);\
    msg->header = (<%= @name %>_header *)malloc(sizeof(<%= @name %>_header));\
  }\
  safe_read(sock, msg->header, sizeof(<%= @name %>_header), error);\
  if(!error) {\
    if(msg->header->_version != PROTO_MESSAGE_VERSION) {\
      error = INVALID_PROTOMSG_VERSION;\
    } else if(msg->header->_type != <%= @name.upcase %>_MESSAGE_TYPE) {\
      error = INVALID_MESSAGE_TYPE;\
    } else {\<% if variable_attributes.size > 0 %>
      if(msg-><%= variable_attributes.first.name %>)\
        free(msg-><%= variable_attributes.first.name %>);\
      msg-><%= variable_attributes.first.name %> = malloc(<%= @name %>_variable_length(msg));\
      <% variable_attributes.each_with_index do |attr, index| %>msg-><%= attr.name %>_length = msg->header-><%= attr.name %>_length;\<% if index > 0 %>
      msg-><%= attr.name %> = msg-><%= variable_attributes.first.name %> + <%= variable_attributes[0..index-1].collect {|attr| "msg->header->#{attr.name}_length" }.join(" + ") %>;\<% end %>
      <% end %>safe_read(sock, msg-><%= variable_attributes.first.name %>, <%= @name %>_variable_length(msg), error);\<% else %>
      ;\<% end %>
    }\
  }\
}
