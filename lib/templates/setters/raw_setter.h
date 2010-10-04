#define set_<%= @message_type.name %>_<%= @name %>(msg, val, length) {\
  msg-><%= @name %> = val;\
  msg-><%= @name %>_length = msg->header-><%= @name %>_length = length;\
}
