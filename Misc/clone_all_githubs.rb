# From https://github.com/jooray/github-backup/blob/master/github-backup.rb

#!/usr/bin/env ruby
require "yaml"
require "open-uri"
require "shellwords"
# your github username
username = "richelbilderbeek"
backupDirectory = Shellwords.escape(".")

YAML.load(open("https://api.github.com/users/#{username}/repos?per_page=100000")).map{|repository|
  puts "Discovered repository: #{repository['name']}"
  system "git clone #{Shellwords.escape(repository['clone_url'])} #{backupDirectory}/#{Shellwords.escape(repository['name'])}"
}

YAML.load(open("https://api.github.com/users/#{username}/repos?direction=desc&per_page=100000")).map{|repository|
  puts "Discovered repository: #{repository['name']}"
  system "git clone #{Shellwords.escape(repository['clone_url'])} #{backupDirectory}/#{Shellwords.escape(repository['name'])}"
}