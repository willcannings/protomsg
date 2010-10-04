#define init_<%= @name %>(msg) {\
  msg = (<%= @name %> *) calloc(1, sizeof(<%= @name %>));\
  msg->header = (<%= @name %>_header *) calloc(1, sizeof(<%= @name %>_header));\
  msg->header->_version = PROTO_MESSAGE_VERSION;\
  msg->header->_type = <%= @name.upcase %>_MESSAGE_TYPE;\
  msg->header_length = sizeof(<%= @name %>_header);\
}

#define free_<%= @name %>(msg) {\<% variable_attributes.each do |attr| %>
  <%= attr.finaliser %><% end %>
  free(msg->header);\
  free(msg);\
}
