#!/bin/bash
HOST=127.0.0.1
PORT=8000

curl -X POST -d 'aÃ§sldkfajsÃ§dlfkajsd
asldfkjasÃ§dlfjkasdfkajsÃ§dfkja
lasdjfaÃ§sldkfajÃ§sdfk
laskdjfÃ§asdkfjaÃ§sdlkfajsÃ§dlf
alsdfjkaÃ§sdfkajsdf
asdf' "http://127.0.0.1:8000/arq1"


for((x=0; x < 5000; x++));
do
   r=$RANDOM
   r=$(( r %= 200 ))
   curl -X PUT -d 'asfasdfasdfqwrqwerqwefasdfsdfasdfqwerqwe
asfasdfafqwerqwerweasdfasdf
asdfasdfasdferqwerqwe
asfasdfaewrqwer

asdfasdfasfasd
asdfasdf$r' "http://127.0.0.1:8000/arq1"
done


curl -X GET "http://127.0.0.1:8000/arq1"
