module Protomsg
  class Attribute
    VALID_TYPES = %w{int float string raw}
    attr_accessor :name, :type
    
    def initialize(message_type, definition_line)
      definition_line =~ /(\w+)\s+(\w+)/ or raise "Invalid attribute definition: '#{definition_line}'"
      VALID_TYPES.include?($1) or raise "Invalid attribute type: #{$1}"
      @message_type = message_type
      @type = $1
      @name = $2
    end
    
    def getter
      render_template('getters', 'getter')
    end
    
    def setter
      render_template('setters', 'setter')
    end
    
    def header_entry
      render_template('header_entries', 'header_entry')
    end
    
    def finaliser
      render_template('finalisers', 'finaliser')
    end
    
    def variable_length?
      %w{string raw}.include?(@type)
    end
    
    def fixed_length?
      !variable_length?
    end
    
    private
      def render_template(folder, suffix)
        path = File.join(File.dirname(__FILE__), '..', 'templates', folder, "#{@type}_#{suffix}.h")
        ERB.new(File.open(path) {|file| file.read}).result(binding)
      end
  end
end
