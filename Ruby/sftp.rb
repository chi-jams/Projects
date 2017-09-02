
require 'net/sftp'

HOST = 'privftp.spectralogic.com'
USER = 'EM-DVT'

class DownloadHandler
  def on_open(downloader, file)
    puts "starting transfer between: #{file.remote} and #{file.local}"
  end

  def on_get(downloader, file, offset, data)
    puts "Progress: #{offset/1000000}MB"
  end

  def on_close(downloader, file)
    puts "finished with #{file.remote}"
  end

  def on_finish(downloader)
    puts "Done!"
  end
end

def ls(sftp)
    sftp.dir.foreach('.') do |entry|
        puts entry.name
    end
end

Net::SFTP.start(HOST, USER) do |sftp|

    ls sftp

    sftp.opendir("/7/ng938nKc")
    ls sftp

    target_file = "/7/ng938nKc/isr4300-universalk9.16.02.02.SPA.bin"

    puts "Local machine cur dir:"
    puts `dir`

    sftp.upload!("./sftp.rb", "/panini.rb")

    puts 'I did it!'

    # This is stupid that you're able to give a -1 value for download, but not
    # for upload. I'm assuming that -1 is unbounded, but this is not necessarily
    # true.

=begin
    sftp.download!(target_file, "beep.bin", :progress => DownloadHandler.new,
                   :read_size => -1, :requests => 32)
=end

end

