#!/bin/bash
read -p "messaggio con chiave: " input

chiave="${input: -10}"

messaggio="${input:0:${#input}-10}"

hash=$(echo -n $input | sha256sum | awk '{print $1}')

echo "Messaggio: $messaggio"
echo "Chiave: $chiave"
echo "SHA256: $hash"
