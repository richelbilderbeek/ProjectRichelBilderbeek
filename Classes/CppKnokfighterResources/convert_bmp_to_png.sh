for x in *.bmp; do convert "$x" "`basename "$x" .bmp`.png"; done

