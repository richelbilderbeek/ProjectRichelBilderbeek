for x in *.wav; do avconv -i "$x" "`basename "$x" .wav`.ogg"; done

