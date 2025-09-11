1.grep -E -i '\<economica\>.*\<sun\>' last.fake | awk '{print $1}' | sort | uniq 
  sed -E "s/  */:/g" last.fake | awk -F: 'BEGIN { IGNORECASE = 1} $3 ~ /^economica/ && $4 ~ /^sun/ && !v[$1]++ {print $1}' | sort
  sed -E "s/  */:/g" last.fake | awk -F: 'BEGIN { IGNORECASE = 1} $3 ~ /^economica/ && $4 ~ /^sun/ {print $1}' | sort | uniq

2.sed -E "s/  */:/g" last.fake | awk -F: 'BEGIN { IGNORECASE = 1} $7 ~ /^23/ && !v[$1]++ {print $1}' | sort

3.awk -F: '$1 ~ /^m/ && $3 % 7 == 0 {print $5}' passwd.fake

4.awk '$1 == "root" && !v[$6]++ {print $6}' ps.fake | sort

5.grep -E '[8][8][:][x]' passwd.fake | awk -F: '{print $5}'

6.grep -E '[x][:][2][3][0-9][:]' passwd.fake | awk -F: '{print $5}'

7.grep -E '^[t].*pts/9' last.fake | awk '{print $1}' | sort

8.grep -E '^r' ps.fake | awk '{print $1}' | sort | uniq | sed 's/[aeiou]/&&/gi'

9.sed 's/[a-zA-Z0-9 ]//g' passwd.fake | sort | uniq

10.sed 's/[^r]//g' passwd.fake | sort | uniq

11.awk '{ sum += $2 } END { if(NR) print "Suma = " sum, "Media = ", sum/NR }' ps.fake
