# UBNext Docker

## Lägg till datafiler
Lägg files.tar och database.sql.tar.xz i roten (för detta utcheckade repo)

kör `tar -zxvf database.sql.tar.xz` detta genererar en database.sql fil.

kör `gzip database.sql`

Kolla så att du nu har en fil som heter `database.sql.gz`

## Sätt sökväg till repo för UBNext
`$ export UBNEXT_REPO="/path/to/ubnext/repo"`

För att upprepa detta varje gång man startar nytt shell, (vid bash) lägg i tex .bashrc:
`$ echo 'export UBNEXT_REPO="/path/to/ubnext/repo' >> ~/.bashrc"`

## Kopiera filer
`$ tar -xvf files.tar -C $UBNEXT_REPO/web/sites/default/`

## Kopiera settings-filer
`$ cp *.settings.php "$UBNEXT_REPO/web/sites/default/"`

## Starta docker-containrar
`$ docker-compose up`
