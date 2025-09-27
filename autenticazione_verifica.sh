#!/bin/bash

read -p "messaggio: " messaggio
read -p "chiave: " chiave
read -p "hash: " hash_atteso

hash_calcolato=$(echo -n "${messaggio}${chiave}" | sha256sum | awk '{print $1}')

echo "hash: $hash_calcolato"
if [ "$hash_calcolato" = "$hash_atteso" ]; then
	echo "ben fatto"
else
	echo "nono"
fi
