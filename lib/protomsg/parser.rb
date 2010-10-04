module Protomsg
  def self.parse_file(path)
    File.open(path) do |file|
      # write the standard protomsg header
      FileUtils.cp File.join(File.dirname(__FILE__), '..', 'templates', 'protomsg.h'), 'protomsg.h'
      puts "Created protomsg.h"
      
      # extract each message type definition
      message_types = []
      data = file.read
      data.scan(/(\w+)\s*\{([^\}]+)\}/) do |message_type|
        message_types << MessageType.new(message_types.size + 1, message_type[0], message_type[1])
      end
      
      # write out each message type's header file
      message_types.each do |message_type|
        header_name = "#{message_type.name}_message.h"
        File.open(header_name, 'w') do |file|
          file.write message_type.to_header_file
        end
        puts "Created #{header_name}"
      end
    end
  end
end
