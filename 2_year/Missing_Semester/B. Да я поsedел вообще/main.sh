for line in $(cat input.txt)
do 
    args=""
    elem=$(echo "$line" | sed 's/google/yandex/g') # https://miniyandex.com:8081/?a?b?c/d=123
    if [[ $elem == *"?"* ]]; then
        args="$(echo "$elem" | cut -d? -f2-)" # a?b?c/d=123 
        elem=$(echo "$elem" | cut -d? -f1)  # https://miniyandex.com:8081/
    fi
    proto="$(echo $elem | grep :// | sed -e's,^\(.*://\).*,\1,g')"  # https://
    if [[ $proto ]]; then 
        echo "Scheme: $proto"
    fi
    url=$elem
    if [[ $proto ]]; then
        url=$(echo $elem | sed -e s,$proto,,g) # miniyandex.com:8081/
    fi
    hostport=$(echo $url | cut -d/ -f1) # miniyandex.com:8081
    host="$(echo $hostport | sed -e 's,:.*,,g')"  # miniyandex.com
    echo "Host: $host"
    if [[ $hostport == *":"* ]]; then 
        port="$(echo $hostport | cut -d: -f2 | cut -d? -f1)" # 8081
        echo "Port: $port"
    fi
    if [[ $args ]]; then
        echo "Args:"
        for arg in $(echo $args | tr \& " " ) # example: "a=b&c=d" -> "a=b c=d"
        do
            key=$(echo $arg | cut -d= -f1) # a?b?c/d
            value=$(echo $arg | cut -d= -f2) # 123
            echo "  Key: $key; Value: $value"
        done
    fi
    echo ""
done > output.txt
#гугл это сила стэковерфлой могила, красивый вариант
