#!/bin/bash

# https://www.codewars.com/kata/589027256c133e73fe0000b5
#
# requirements: bash, coreutils, findutils, bc, grep (things you'd find on a
# typical GNUish system)
#
# self-imposed constraints:
# - oneliners
# - no variables
# - no loops
# - avoid subshells (which I did use, because the alternative is
#   redirections, which are super chaotic)

seq $(date --date=2022-11-26 +%s) 86400 $(date --date=2022-12-28 +%s) | xargs -i -n1 date --date=@{} +%u | grep -v 7 | wc -l | xargs -i echo {}*1.15 | bc | cut -f1 -d.

seq $(date --date=2022-12-06 +%s) 86400 $(date --date=2022-12-09 +%s) | xargs -i -n1 date --date=@{} +%u | grep -v 7 | wc -l | xargs -i echo {}*1.15 | bc | cut -f1 -d.

seq $(date --date=2022-12-18 +%s) 86400 $(date --date=2022-12-25 +%s) | xargs -i -n1 date --date=@{} +%u | grep -v 7 | wc -l | xargs -i echo {}*1.15 | bc | cut -f1 -d.
