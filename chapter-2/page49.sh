#!/bin/sh
set -x
echo "The date is $(date)"
set $(date)
echo "The month is $2"
exit 0
