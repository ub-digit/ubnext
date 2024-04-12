FROM node:8.12-alpine AS release
RUN apk add --no-cache git

ARG GIT_REVISION
ARG GIT_REPO_URL

WORKDIR /root/

RUN set -ex \
  && git clone $GIT_REPO_URL release -b $GIT_REVISION --depth 1

# Needed since drupal_add_css skips non existing css files
# (even though file exists in web container and would be loaded)
WORKDIR /root/release/web/sites/default/themes/ubnext
RUN npm install && ./node_modules/grunt-cli/bin/grunt less

FROM docker.ub.gu.se/drupal-php-7.4-fpm:v1

COPY --chown=www-data:www-data --from=release /root/release/web/ /var/www/html/

# vim:set ft=dockerfile:
