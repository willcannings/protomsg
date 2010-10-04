<% variable_attributes.each do |attr| %>#define <%= @name %>_<%= attr.name %>_length(msg) (msg-><%= attr.name %>_length)
<% end %>#define <%= @name %>_length(msg) (msg->header_length + <%= variable_attributes.collect {|attr| "msg->#{attr.name}_length"}.join(" + ") %>)
