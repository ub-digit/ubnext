#!/bin/bash
./docker-compose-release.sh exec database /bin/bash -c 'mysqldump -u$MYSQL_USER -p$MYSQL_PASSWORD $MYSQL_DATABASE'
