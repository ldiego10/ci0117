for i in `dd conv=ucase if=$1 2> /dev/null | sed 's/<\!\-\-/<\!\-\- /g' | sed 's/</\n</g' | sed 's/>/>\n/g' | grep "^<\(\![ \r\n\t]*\(--\)\s*\)\?\/\?\w\s*" | cut -d' ' -f 1 | cut -d'>' -f 1 | cut -d'<' -f 2 | sort -u`; do echo $i `grep -ic "<$i[ >]" $1`; done

