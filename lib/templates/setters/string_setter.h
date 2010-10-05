#define set_<%= @message_type.name %>_<%= @name %>(msg, val) {\
  msg-><%= @name %> = val;\
  msg-><%= @name %>_length = msg->header-><%= @name %>_length = ((val) ? (strlen(val) + 1) : 0);\
}
