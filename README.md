UBNext
======

## Capistrano setup:
- gem install capistrano
- gem install capistrano-template
- gem install capistrano-npm
- gem install capistrano-composer

## Export databases

- kör cd /var/www/scripts_test 
- kör drush php-script -r /var/www/html/ databases-export.php > seed.sql i apps-docker-containern
- seed.sql sparas i projectets scripts-katalog
