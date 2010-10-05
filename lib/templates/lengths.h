<% variable_attributes.each do |attr| %>#define <%= @name %>_<%= attr.name %>_length(msg) (msg->header-><%= attr.name %>_length)
<% end %>#define <%= @name %>_length(msg) (msg->header_length <%= variable_attributes.size > 0 ? ("+ " + variable_attributes.collect {|attr| "msg->header->#{attr.name}_length"}.join(" + ")) : '' %>)<% if variable_attributes.size > 0 %>
#define <%= @name %>_variable_length(msg) (<%= variable_attributes.collect {|attr| "msg->header->#{attr.name}_length"}.join(" + ")%>)<% end %>
