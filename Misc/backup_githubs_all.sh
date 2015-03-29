
# USER=richelbilderbeek

#curl https://api.GitHub.com/users/richelbilderbeek/repos?per_page=10000 | egrep "html_url\": \"https://github.com/richelbilderbeek/"

for r1 in `curl https://api.GitHub.com/users/richelbilderbeek/repos?per_page=10000 | egrep "https://github.com/richelbilderbeek/\w*\","`
do
  #echo "r1: "$r1
  r2=`echo $r1 | egrep "/\w*\","`
  echo "r2: "$r2
done