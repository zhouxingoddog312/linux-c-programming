#!/bin/bash
tr -dc '[:alnum:][:blank:]'</dev/urandom |head -c 1048579 >file.in
