#!/bin/bash
# check if the file 'database.sql' exists
if [ ! -f database.sql ]; then
  echo "File 'database.sql' not found!"
  exit 1
else
  echo "Restoring database..."
  ./docker-compose-release.sh exec -T database bin/bash -c 'exec mysql -u$MYSQL_USER -p$MYSQL_PASSWORD $MYSQL_DATABASE' < database.sql
fi
echo "Database restored successfully!"

