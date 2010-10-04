module Protomsg
  class MessageType
    attr_accessor :type_number, :attributes, :name
    def initialize(type_number, name, lines)
      @name         = name
      @type_number  = type_number
      lines = lines.split("\n").collect(&:strip).reject(&:empty?)
      @attributes   = lines.collect {|line| Attribute.new(self, line)}
    end
    
    def variable_attributes
      @variable_attributes ||= @attributes.select(&:variable_length?)
    end
    
    def header
      render_template('header')
    end

    def getters
      render_template('getters')
    end

    def setters
      render_template('setters')
    end

    def lengths
      render_template('lengths')
    end

    def memory
      render_template('memory')
    end

    def io
      render_template('io')
    end
    
    def to_header_file
      render_template('message_type')
    end
    
    private
      def render_template(name)
        path = File.join(File.dirname(__FILE__), '..', 'templates', "#{name}.h")
        ERB.new(File.open(path){|file| file.read}).result(binding)
      end
      
  end
end
