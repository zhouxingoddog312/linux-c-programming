#!/bin/bash
tr -dc '[:alnum:][:blank:]'</dev/urandom |head -c 1024 >file.in
