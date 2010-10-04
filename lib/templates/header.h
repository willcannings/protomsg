typedef struct {
  char  _version;
  char  _type;<% @attributes.each do |attr|%>
  <%= attr.header_entry %><% end %>
} <%= @name %>_header;

typedef struct {
  <%= @name %>_header *header;
  size_t  header_length;<% variable_attributes.each do |attr| %>
  void    *<%= attr.name %>;
  size_t  <%= attr.name %>_length;<% end %>
} <%= @name %>;
