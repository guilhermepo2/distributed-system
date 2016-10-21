#!/bin/bash
HOST=127.0.0.1
PORT=8000

curl --request POST \
       	  --url http://$HOST:$PORT/arq1 \
       	        --data 'açsldkfajsçdlfkajsd\nasldfkjasçdlfjkasdfkajsçdfkja\nlasdjfaçsldkfajçsdfk\nlaskdjfçasdkfjaçsdlkfajsçdlf\nalsdfjkaçsdfkajsdf\nasdf'


for((x=0; x < 100; x++));
do
   r=$RANDOM
   r=$(( r %= 200 ))
   curl --request PUT \
       	  --url http://$HOST:$PORT/arq1 \
       	        --data "asfasdfasdf$r" &
done

sleep 10
echo ------------------------------------------------------

curl --request GET --url http://$HOST:$PORT/arq1
