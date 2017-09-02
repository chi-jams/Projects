require 'diffy'

def parse_html(raw_html)

    num_tabs = 0
    raw_html.gsub!(/<(?!!).*?(?=[ >])|>(?!<)([\S ]+?)(?=<)|>?[\w .:\-,]+\{.*\}/) do |content|
        if $1
            content = ">\n" + ("  " * num_tabs) + $1
        elsif !content.include? "<"
            if content[0] == ">"
                content = ">\n" + ("  " * num_tabs) + content[1..content.size]
            else
                content = ("  " * num_tabs) + content
            end
        elsif content.include? "/"
            num_tabs -= 1
            content = "\n" + ("  " * num_tabs) + content
        else
            content = "\n" + ("  " * num_tabs) + content
            num_tabs += 1 unless content.include? "link"
        end

        content
    end

    raw_html
end

css = "<stylesheet>#{Diffy::CSS.gsub!(/\/\*.*\n/, '')}</stylesheet>"
test_case = sprintf(File.read("test_parse.html"), css)

puts parse_html(test_case)