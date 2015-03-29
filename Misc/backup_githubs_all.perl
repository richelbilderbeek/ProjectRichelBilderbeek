#!/usr/bin/perl

@lines = `curl https://api.GitHub.com/users/richelbilderbeek/repos?per_page=10000 | egrep "https://github.com/richelbilderbeek/\w*\","`;
foreach(@lines) {
  s/,/ /g;
  print;
}